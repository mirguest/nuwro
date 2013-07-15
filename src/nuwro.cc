#include <iomanip>
#include <sstream>
#include <vector>
#include "event1.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "qelevent.h"
#include "pdg.h"
#include "chooser.h"
#include "beam.h"
#include "beamHist.h"
#include "target_mixer.h"
#include "stdlib.h"
#include "pauli.h"
#include "dis/singlepion.h"
#include "dis/disevent.h"
#include "dis/resevent2.h"
#include "cohevent2.h"
#include "coh.h"
#include "mecevent.h"
#include "args.h"
#include "kaskada7.h"
#include "sfevent.h"
#include "Analyser1.h"
#include "geomy.h"
#include "ff.h"
#include "hist.h"
#include "nucleusmaker.h"

extern double SPP[2][2][2][3][40];
//extern double sppweight;

params *p1=NULL;
string data_dir;
#include "nuwro.h"

NuWro::~NuWro()
{		
	delete mixer;
	delete detector;
	delete neutrino_beam;
	delete nucleuss;
}

NuWro::NuWro()
{
	mixer = NULL;
	detector = NULL;
	neutrino_beam = NULL;
	nucleuss = NULL;
}

void NuWro :: set (params &par)
{	
	frandom_init(par.random_seed);

	dismode = false;
	
	neutrino_beam = create_beam (par);
	nucleuss = make_nucleus (par);
	
	if(par.target_type == 1)
		mixer = new target_mixer (par);
		
	detector = make_detector (par);
	
	ff_configure (par);
	refresh_dyn (par);
}

void NuWro :: refresh_target (params &par)
{
	delete nucleuss;
	nucleuss = make_nucleus (par);
}

void NuWro :: refresh_dyn (params &par)
{
	bool active[] =
	{
		par.dyn_qel_cc,par.dyn_qel_nc,
		par.dyn_res_cc,par.dyn_res_nc,
		par.dyn_dis_cc,par.dyn_dis_nc,
		par.dyn_coh_cc,par.dyn_coh_nc,
		par.dyn_mec_cc,par.dyn_mec_nc
	};

	procesy.reset(active);
}

geomy* NuWro::make_detector(params &p)
{
	if(p.target_type!=2)
		return NULL;
		
	if(p.geo_file.length())
	{
		try
		{
			if(p.geo_d.norm2()==0)
				return new geomy(p.geo_file,p.geo_name);
			else
				return new geomy(p.geo_file,p.geo_name,p.geo_volume,p.geo_d,p.geo_o);
		}
		catch(...)
		{
			cerr<<"Failed to make detector."<<endl;
			exit(3);
		}
	}
	else
	{	
		cerr<<"Failed to make detector. Parameter geo_file must not be empty if target_type=2."<<endl;
		exit(4);
		return NULL;
	}

}

int NuWro::init (int argc, char **argv)
{
	//  dismode=false;
	dismode=true;
	set_dirs(argv[0]);
	a.read (argc, argv);
	p.read (a.input);
	p.read (a.params, "command line");
	
	p.list (cout);
	p.list (string(a.output)+".par");
	p1=&p;
	progress.open(a.progress);
	frandom_init(p.random_seed);
	if(p.beam_test_only==0 && p.kaskada_redo==0)
		if(p.dyn_dis_nc or p.dyn_res_nc  or p.dyn_dis_cc or p.dyn_res_cc )
	{
		cout<<" Calculating the one pion functions ..."<<endl;
		singlepion (p);
		/*  for (int c = 0; c < 40; c++)
			cout << 1210 + c * 20 << "  MeV -> "
			 << setw(10)<< SPP[0][0][0][0][c] << "  "
			 << setw(10)<< SPP[0][0][0][1][c] << "  "
			 << setw(10)<< SPP[0][0][0][2][c] << "  "
			 << setw(10)<< SPP[0][0][1][0][c] << "  "
			 << setw(10)<< SPP[0][0][1][1][c] << "  "
				 << setw(10)<< SPP[0][0][1][2][c] << endl;
	*/
	}							 
	if(p.kaskada_redo==0)
	{
		cout<<"Creating the beam ..."<<endl;
		neutrino_beam=create_beam(p);
		if(neutrino_beam==NULL)
			{cerr<<"No beam defined."<<endl;exit(5);}

			nucleuss = make_nucleus(p);
		if(p.target_type==1)
			mixer=new target_mixer(p);
		else
			mixer = NULL;
			
		detector=make_detector(p);

	}
	ff_configure(p);
	refresh_dyn(p);	
}

void NuWro::makeevent(event* e, params &p)
{
	static double max_dens=0,max_norm=0;
	particle nu;
	material mat;
	int dyn = e->dyn;
	if(detector)
	{
		do
		{
			nu=neutrino_beam->shoot(dyn>1 && dyn<6 && dismode);
			if(nu.travelled>0 && p.beam_weighted==0)
			{
				if(nu.travelled<frandom()*max_norm)
					continue;
				if(nu.travelled>max_norm)
					max_norm=nu.travelled;
				nu.travelled=0;
			}
			nu.r=vec(nu.r)+p.beam_offset;
			if(nu.r.x==0 && nu.r.y==0 && nu.r.z==0)
				mat=detector->getpoint();
			else
				mat=detector->getpoint(nu.p(),nu.r);
//			cout<<mat.Z<<' '<<mat.N<<' '<<endl;
			if(mat.w_density>max_dens)
				max_dens=mat.w_density;
//		    cout<< mat.w_density<< ' '<<max_dens<<"<-max dens"<<endl;
		} while(not (mat.Z+mat.N>0 && mat.w_density>=frandom()*max_dens));
		///change nucleus
		p.nucleus_p=mat.Z;
		p.nucleus_n=mat.N;
//		p.nucleus_E_b=mat.e_bin;
//		p.nucleus_kf=mat.p_fermi;
		p.nucleus_E_b=0;  // Use library value for E_b
		p.nucleus_kf=0;   // Use library value for E_b
//		cout<<mat.Z<<' '<<mat.N<<' '<<endl;
		if(mat.Z==0&&mat.N==0)
			throw "Empty isotope 00";
	}
	else
	{
		nu=neutrino_beam->shoot(dyn>1 && dyn<6 && dismode);
		nu.r=vec(nu.r)+p.beam_offset;
	}
	if(detector or mixer) // nucleuss not reusable
	{
		delete nucleuss;
		nucleuss= make_nucleus(p);
		//cout<<"make_nucleus "<<nucleuss->p<<" "<<nucleuss->n<<endl;
	}
	e->in.push_back (nu);		 // insert neutrino
	if(dyn<6)
	{
								 // insert target nucleon
		e->in.push_back (nucleuss->get_nucleon());
		e->in[0].r=e->in[1].r;
		assert(e->in[1]*e->in[1]>0);
	}
	e->r=mat.r;
	// cout<< "mat.r="<< mat.r<<endl;

	e->weight=0;
	if(nu.travelled>0)
		e->norm=nu.travelled;
	// else e->norm remains 1;

	e->flag.cc  = dyn%2  == 0;
	e->flag.nc  = dyn%2  == 1;

	e->flag.qel = dyn/2  == 0;
	e->flag.res = dyn/2  == 1;
	e->flag.dis = dyn/2  == 2;
	e->flag.coh = dyn/2  == 3;
	e->flag.mec = dyn/2  == 4;

	if(p.beam_test_only)
	{
		e->weight=1;
		e->out.push_back(e->in[0]);
		return;
	}
	double factor=1.0;
								 
	if(p.cc_smoothing and e->flag.cc and dyn==0) //only in qel_cc
	{
		if(e->in[0].pdg>0)
		{
			factor=nucleuss->frac_neutron();
			e->in[1].set_neutron();
		}
		else
		{
			factor=nucleuss->frac_proton();
			e->in[1].set_proton();
		}
	}
	e->par =p;

	switch (dyn)
	{
		case 0:
			if (p.dyn_qel_cc) // qel cc
			{
				if(p.sf_method>0 and has_sf(*nucleuss, p.sf_method))
					sfevent2cc (p, *e, *nucleuss);
				else
					qelevent1 (p, *e, *nucleuss, false);
			}
			break;				 
		case 1:
			if (p.dyn_qel_nc) // qel nc
				if(p.sf_method>0 and has_sf(*nucleuss, p.sf_method))
					sfevent2nc (p, *e, *nucleuss);
			else
				qelevent1 (p, *e, *nucleuss, true);
			break;				 
		case 2:
			if (p.dyn_res_cc) // res cc
			{
				resevent2 (p, *e, true);
				if (p.pauli_blocking)
					mypauli_spp (*e, *nucleuss);
			}
			break;				
		case 3:
			if (p.dyn_res_nc) // res nc
			{
				resevent2 (p, *e, false);
				if (p.pauli_blocking)
					mypauli_spp (*e, *nucleuss);
			}
			break;
		case 4:
			if (p.dyn_dis_cc) // dis cc
			{
				disevent (p, *e, true);
				if (p.pauli_blocking)
					mypauli_spp (*e, *nucleuss);
			}
			break;				
		case 5:
			if (p.dyn_dis_nc) //dis nc
			{
				disevent (p, *e, false);
				if (p.pauli_blocking)
					mypauli_spp (*e, *nucleuss);
			}
			break;
		case 6:                  
			if (p.dyn_coh_cc) // coh cc
			{
				if(p.coh_new) cohevent_cj (p, *e, *nucleuss, true);
				else          cohevent2   (p, *e, *nucleuss, true);
			}
			break;
		case 7:                  
			if (p.dyn_coh_nc) // coh nc
			{
				if(p.coh_new) cohevent_cj (p, *e, *nucleuss, false);
				else          cohevent2   (p, *e, *nucleuss, false);
			}
			break;
		case 8:
			if (p.dyn_mec_cc) // mec cc
			if(nu.pdg>0)      // only neutrinos allowed
			{	
				if(nucleuss->A()<=1)
					break;
				switch(p.mec_kind)
				{
					case 1:mecevent_tem (p, *e, *nucleuss, true);break;
					case 2:mecevent2 (p, *e, *nucleuss, true);break;
					case 3:mecevent_Nieves (p, *e, *nucleuss, true);break;
//					case 4:mecevent (p, *e, *nucleuss, true);break;//old tem implementation
					default:mecevent_tem (p, *e, *nucleuss, true);break; 
				}
				for(int i=0;i<e->out.size();i++)
					e->out[i].set_momentum(e->out[i].p().fromZto(e->in[0].p()));
			}
			break;
		case 9: 
			if (p.dyn_mec_nc) //mec nc
			if(nu.pdg>0)      // only neutrinos allowed
			{   
				if(nucleuss->A()<=1)
					break;
				switch(p.mec_kind)
				{
					//case 1: mecevent(p, *e, *nucleuss, false);break;
					//case 2: mecevent2 (p, *e, *nucleuss, false);break; there is only TEM for NC
					default: mecevent_tem (p, *e, *nucleuss, false);break; 
				}
				for(int i=0;i<e->out.size();i++)
					e->out[i].set_momentum(e->out[i].p().fromZto(e->in[0].p()));
			}
			break;
	}
	e->weight*=factor;

	if (e->weight == 0)
	{
		e->out.clear ();
								 //po co to wpisywanie ???
		e->out.push_back (e->in[0]);
		e->out.push_back (e->in[1]);
	}
	//      e->check();
}								 // end of makeevent


void NuWro::finishevent(event* e, params &p)
{
	for(int i=0;i<1/* e->in.size()*/;i++)
	{
		e->in[i].endproc=e->dyn;
		registration(e->all,e->in[i]);
	}
	for(int i=0;i<e->out.size();i++)
	{
		e->out[i].mother=0;
		registration(e->all,e->out[i]);
	}
	if(p.beam_test_only)
		return;
	for(int j=0;j<e->out.size();j++)
		e->out[j].r=e->in[1].r;

	for(int j=0;j<e->in.size();j++)
	{
		particle p=e->in[j];
		p.endproc=e->dyn;
		registration(e->all,p);
	}

	//e->pr=nucleuss->Zr(); 	// 1. po co to?
	//e->nr=nucleuss->Nr(); 	// 2. powoduje break, segmentation fault

								 // copy particle from out to post if coherent interaction
	
	if ( p.kaskada_on and !e->flag.coh )
	{
		kaskada k(p, *e);
		k.kaskadaevent();		 // runs only if p.kaskada_on is true
	}
	
	if(e->post.size()==0)   // copy out to post if no fsi
	{
		for (int j = 0; j<e->out.size(); j++)
		{
			particle p = e->out[j];
			p.endproc = e->dyn;
			registration(e->all,p);
			e->post.push_back(p);
		}
	}
}								 //end of finishevent


void NuWro::raport(double i,double n,const char* text,int precision, int k, bool toFile)
{
	static int prev=-1;
	int proc=precision*i/n;
	if(proc!=prev)
	{
		prev=proc;
		cerr.precision(3);
		if(toFile)
		{
			progress.seekp(ios_base::beg);
			progress << proc*100.0/precision<<" "<<text<<'\r'<<flush;
			progress.flush();
		}
		else
		{
			if(k>=0)
				cerr<<"Dyn["<<k<<"] ";
			cerr<<showpoint<<proc*100.0/precision<<text<<'\r'<<flush;
		}
		cerr.precision();

		//	   printf("%f3.1 %s\r", proc/10.0,text);
	}
}								 //end of report


//////////////////////////////////////////////////////////////
//              Test events
//////////////////////////////////////////////////////////////
void NuWro::test_events(params & p)
{

	if(p.number_of_test_events>0  && p.beam_test_only==0)
	{
		hist hq2((char*)"q2",0,2*GeV2,100);
		hist hq0((char*)"q0",0,(p.beam_type==0 ? atof(p.beam_energy.c_str())*MeV : 2*GeV),100);
		hist hqv((char*)"qv",0,(p.beam_type==0 ? atof(p.beam_energy.c_str())*MeV : 2*GeV),100);
		hist hT((char*)"T",0,2*GeV,100);
		TFile *te;
		TTree *t1;
		event *e;
		if(p.save_test_events)
		{	
			dismode=false;
			te=new TFile((string("weighted.")+a.output).c_str(),"recreate");						
			t1 = new TTree ("treeout", "Tree of events");
			e = new event ();
			t1->Branch ("e", "event", &e);
			delete e;
		}

		refresh_dyn(p);
		
		int saved=0;
		for (int i = 0; i < p.number_of_test_events; i++)
		{
			e = new event ();

			e->dyn = procesy.choose (); // choose dynamics
			if(mixer)
				mixer->prepare(p);
			makeevent(e,p);
			double bias=1;
			if(dismode && e->dyn>1 && e->dyn<6)
				bias=e->in[0].t;
			procesy.add (e->dyn, e->weight, bias);
			e->weight/=procesy.ratio(e->dyn); // make avg(weight)= total cross section
			if(e->weight>0)
			{
				hq2.insert_value(-e->q2(),e->weight*cm2);
				hq0.insert_value(e->q0(),e->weight*cm2);
				hqv.insert_value(e->qv(),e->weight*cm2);
				hT.insert_value(e->in[0].E(),e->weight*cm2);
			}
			else
			{
				hq2.insert_value(0,0);
				hq0.insert_value(0,0);
				hqv.insert_value(0,0);
				hT.insert_value(0,0);
			}
			switch(p.save_test_events)
			{
				case 0: 
					break;
				case 1: 
					finishevent(e, p);
					t1->Fill ();
					break;
				case 2:
					if(e->weight>0)
					{
						saved++;
						e->weight=e->weight*saved/(i+1);
						finishevent(e, p);
						t1->Fill ();						
					}
					break;
				default:
					cerr<<"Parameter save_test_events="<<p.save_test_events;
					cerr <<" out of range. Should be ,1, or 2)"<<endl;
					exit(12);
			}
			delete e;
			raport(i+1,p.number_of_test_events," % of test events ready...",1000,-1,bool(a.progress));
		}						 // end of nuwro loop
		if(p.save_test_events)
		{
			te->Write ();
			te->Close ();
		}

		cout<<endl;
		procesy.report();
		procesy.set_weights_to_avg ();
		string prefix;
//		if(strlen(a.output)>5 && string(".root")==a.output[strlen(a.output)-5])
			prefix="";
//		else 
//			prefix=a.output;
		hq2.plot(prefix+"q2.txt",GeV2,1e-38*cm2/GeV2);
		hq0.plot(prefix+"q0.txt",GeV,1e-38*cm2/GeV);
		hqv.plot(prefix+"qv.txt",GeV,1e-38*cm2/GeV);
		hT.plot(prefix+"T.txt",GeV,1e-38*cm2/GeV);
		ofstream totals ((prefix+"totals.txt").c_str(),ios::app);
		totals<<p.beam_energy;
		for(int i=0;i<procesy.size();i++)
			totals << ' '<<procesy.avg(i);
		totals<<endl;
	}
}


void NuWro::user_events(params &p)
{
	if(p.number_of_test_events<1 or p.user_events==0)
		return;
	params p1=p;
	Analyser * A=make_analyser(p);
	if(!A) 
		return;
	for(A->start(); !A->end(); A->step())
	{
		refresh_dyn(p);
		for (int i = 0; i < p.number_of_test_events; i++)
		{
			event *e = new event ();
								 
			e->dyn = procesy.choose ();///< choose dynamics
			
			A->prepare_event(*e);
			if(mixer)
				mixer->prepare(p);

			makeevent(e,p);

			A->process_event(*e);

			double bias=1;
			if(dismode && e->dyn>1 && e->dyn<6)
				bias=e->in[0].t;

			procesy.add (e->dyn, e->weight, bias);

			delete e;
			
			raport(i+1,p.number_of_test_events," % of analyser events ready...",1000,-1,bool(a.progress));
			p=p1;
	}	// end of nuwro loop

		A->partial_report();
		procesy.report();
	
	}	// end of analyser loop
	A->final_report();
	delete A;
}


void NuWro::real_events(params& p)
{
	dismode=true;
	if(p.number_of_events<1)
		return;
	
	/// calculate desired number of events for each dynamics
	procesy.calculate_counts(p.number_of_events);
	{							 /// Write cross sections and counts to screen and file
		ofstream f((string(a.output)+".txt").c_str());
		procesy.short_report(cout);
		procesy.short_report(f);
	}

	event *e = new event;

	string output=a.output;
	int l=output.length();
	if(l<5 || string(".root")!=output.c_str()+l-5)
		output=output+".root";
	TFile *ff = new TFile (output.c_str(), "recreate");
	TTree *tf = new TTree ("treeout", "Tree of events");
	tf->Branch ("e", "event", &e);
	delete e;
	TH1 * xsections= new TH1D("xsections","xsections",8,0,7);
	for(int i=0;i<procesy.size();i++)
	{
		xsections->SetBinContent(i+1,procesy.avg(i));
		xsections->SetBinError(i+1,procesy.sigma(i));
	}

	/////////////////////////////////////////////////////////////
	// The main loop in NPROC -- generate file with unweighted events
	//////////////////////////////////////////////////////////////

	char filename[230];
	if(p.kaskada_redo==0)
		for (int k = 0; k < procesy.size(); k++)
			if(procesy.desired(k)>0)
			{
				sprintf(filename,"%s.%d.part",a.output,k);
				TFile *f1 = new TFile (filename, "recreate");
				TTree *t1 = new TTree ("treeout", "Tree of events");

				e = new event ();
				t1->Branch ("e", "event", &e);
				delete e;

				while(procesy.ready(k)<procesy.desired(k))
				{
					e = new event ();
					e->dyn = k;

					if(mixer)
						mixer->prepare(p);
					makeevent(e,p);
					double bias=1;
					if(!p.beam_test_only && dismode & k>1 && k<6)
						bias=e->in[0].t;
					if (procesy.accept(e->dyn,e->weight,bias))
					{
						finishevent(e, p);
						e->weight=procesy.total();
						t1->Fill ();
					}
					delete e;

					raport(procesy.ready(k),procesy.desired(k)," % of events ready...",1000,k,bool(a.progress));
				}
				f1->Write ();

		// elimination of spurious events for dynamics k
		// by copying only last desired[k] events to outfile
				if(p.mixed_order==0)
				{
					cout<<endl;
					int nn = t1->GetEntries ();
					int start = nn-procesy.desired(k);
					for (int jj = start; jj < nn; jj++)
					{
						e = new event();
						t1->GetEntry (jj);
						tf->Fill ();
						delete e;
						raport(jj-start+1,nn-start," % events copied...",100,k,bool(a.progress));
					}
					cout<<endl;
				}
				else
					cout<<endl;

				f1->Close ();
				delete f1;
				if(p.mixed_order==0)
					unlink(filename);
			};
	//////////////////////////////////////////////////////////////////////////////////////
	//                    end of the main loop in NPROC
	//////////////////////////////////////////////////////////////////////////////////////
	if(p.mixed_order)
	{
		TFile *f[procesy.size()];
		TTree *t[procesy.size()];
		int n[procesy.size()],u[procesy.size()];
		int ile=0;
		e=new event();
		for (int k = 0; k < procesy.size(); k++)
			if((u[k]=procesy.desired(k))>0)
		{
			sprintf(filename,"%s.%d.part",a.output,k);
			f[k] = new TFile (filename);
			t[k] = (TTree*) f[k]->Get("treeout");
			if(t[k]==NULL)
			{
				cerr<< "tree \"treeout\" not found in file \""<<filename<<"\""<<endl;
				exit(6);
			}

			t[k]->SetBranchAddress("e", &e);
			n[k]=t[k]->GetEntries();
			ile+=u[k];
		}
		int nn=ile;
		while(ile>0)
		{
			int i=0;
			int x=frandom()*ile;
			while(x>=u[i])
				x-=u[i++];
			t[i]->GetEntry(n[i]-u[i]);
			tf->Fill();
			ile--;
			u[i]--;
			raport(nn-ile,nn," % events copied...",100,i,bool(a.progress));
		}
		delete e;
		for (int k = 0; k < procesy.size(); k++)
			if(procesy.desired(k))
		{
			f[k]->Close();
			delete f[k];
			sprintf(filename,"%s.%d.part",a.output,k);
			unlink (filename);
		}
	}
	ff->Write ();
	ff->Close ();
	progress.close();
	delete ff;
	procesy.report();

	cout << "Output file: \"" << output << "\"" << endl;

}


void NuWro::kaskada_redo(string input,string output)
{
	event *e=new event;

	TFile *fi = new TFile (input.c_str());
	TTree* ti = (TTree*) fi->Get("treeout");
	if(ti==NULL)
	{
		cerr<< "tree \"treeout\" not found in file \""<<input<<"\""<<endl;
		exit(7);
	}
	ti->SetBranchAddress("e", &e);

	TFile *ff= new TFile(output.c_str(),"recreate");
	TTree *tf = new TTree("treeout","Tree of events");
	tf->Branch("e","event",&e);

	int nn = ti->GetEntries ();
	for (int i = 0; i < nn; i++)
	{
		//		e = new event();
		ti->GetEntry (i);
		e->clear_fsi();
		finishevent(e,p);
		tf->Fill ();
		//		delete e;
		//if(i%1000==0)
		//cout<<i/1000<<"/"<<nn/1000<<"\r"<<endl;
		raport(i+1,nn," % events processed...",100,e->dyn,bool(a.progress));
	}
	cout<<endl;
	fi->Close ();
	delete fi;

	ff->Write();
	ff->Close();
	delete e;
	delete ff;
	cout<<"Output: \""<<output<<"\""<<endl;
}


#include "UserAction.h"

int NuWro::main (int argc, char **argv)
{
	try
	{
		init(argc,argv);
		if(p.kaskada_redo==1)
			kaskada_redo(a.output,string(a.output)+".fsi.root");
		else
		{
			if(not p.beam_test_only)
			{
				if(p.user_events>0)
					user_events(p);
				else
				{
					test_events(p);
					real_events(p);
				}
			}
		}
		genrand_write_state();
	}
	catch(string s)
	{
		cout<<s<<endl;
	}
	catch(char const* s)
	{
		cout<<s<<endl;
	}
	catch(...)
	{
		cout<<"Nuwro failed"<<endl;
	}
}
