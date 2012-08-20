#include "elements.h"


const double BD=-1;      // no data
const double NE=-1; 	 // does non existing
const double SMALL=1e-4; // less that 0.001


/* Z|Symbol|  Name      | Group | Period | Weight u () | Density g/cm3 | Melt K | Boil K| Heat J / g K | Neg |	Abundance mg / kg| */
element el[]=
{
	{  0, "NO" , "Nothing"      ,  0, 0,                     0,  0.0000    ,    0     ,    0   ,  0    , 0   , 0     },
	{  1, "H"  , "Hydrogen"     ,  0, 1,   1.007947/*2 3 4 9*/,  0.00008988,   14.175 ,   20.28, 14.304, 2.20, 1400  },
	{  2, "He" , "Helium"       , 18, 1,   4.0026022/*2 4*/   ,  0.0001785 ,    0.956 ,    4.22,  5.193, BD  , 0.008 },
	{  3, "Li" , "Lithium"      ,  1, 2,   6.9412/*2 3 4 5 9*/,  0.534     ,  453.85  , 1615   ,  3.582, 0.98, 20    },
	{  4, "Be" , "Beryllium"    ,  2, 2,   9.0121823          ,  1.85      , 1560.15  , 2742   ,  1.825, 1.57, 2.8   },
	{  5, "B"  , "Boron"        , 13, 2,  10.8117/*2 3 4 9*/  ,  2.34      , 2573.15  , 4200   ,  1.026, 2.04, 10    },
	{  6, "C"  , "Carbon"       , 14, 2,  12.01078/*2 4 9*/   ,  2.267     , 3915     , 3915   ,  0.709, 2.55, 200   },/*sublimates at 3915 K*/
	{  7, "N"  , "Nitrogen"     , 15, 2,  14.00672/*2 4 9*/   ,  0.0012506 ,   63.29  ,   77.36,  1.04 , 3.04, 19    },
	{  8, "O"  , "Oxygen"       , 16, 2,  15.99943/*2 4 9*/   ,  0.001429  ,   50.5   ,   90.20,  0.918, 3.44, 461000},
	{  9, "F"  , "Fluorine"     , 17, 2,  18.99840325         ,  0.001696  ,   53.63  ,   85.03,  0.824, 3.98, 585   },
	{ 10, "Ne" , "Neon"         , 18, 2,  20.17976/*2 3*/     ,  0.0008999 ,   24.703 ,   27.07,  1.03 , BD  , 0.005 },
	{ 11, "Na" , "Sodium"       ,  1, 3,  22.989769282        ,  0.971     ,  371.15  , 1156   ,  1.228, 0.93, 23600 },
	{ 12, "Mg" , "Magnesium"    ,  2, 3,  24.30506            ,  1.738     ,  923.15  , 1363   ,  1.023, 1.31, 23300 },
	{ 13, "Al" , "Aluminium"    , 13, 3,  26.98153868         ,  2.698     ,  933.4   , 2792   ,  0.897, 1.61, 82300 },
	{ 14, "Si" , "Silicon"      , 14, 3,  28.08553/*4 9*/     ,  2.3296    , 1683.15  , 3538   ,  0.705, 1.9 , 282000},
	{ 15, "P"  , "Phosphorus"   , 15, 3,  30.9737622          ,  1.82      ,  317.25  ,  553   ,  0.769, 2.19, 1050  },
	{ 16, "S"  , "Sulfur"       , 16, 3,  32.0655/*2 4 9*/    ,  2.067     ,  388.51  ,  717.8 ,  0.71 , 2.58, 350   },
	{ 17, "Cl" , "Chlorine"     , 17, 3,  35.4532/*2 3 4 9*/  ,  0.003214  ,  172.31  ,  239.11,  0.479, 3.16, 145   },
	{ 18, "Ar" , "Argon"        , 18, 3,  39.9481/*2 4*/      ,  0.0017837 ,   83.96  ,   87.30,  0.52 , BD  , 3.5   },
	{ 19, "K"  , "Potassium"    ,  1, 4,  39.09831            ,  0.862     ,  336.5   , 1032   ,  0.757, 0.82, 20900 },
	{ 20, "Ca" , "Calcium"      ,  2, 4,  40.0784/*2*/        ,  1.54      , 1112.15  , 1757   ,  0.647, 1   , 41500 },
	{ 21, "Sc" , "Scandium"     ,  3, 4,  44.9559126          ,  2.989     , 1812.15  , 3109   ,  0.568, 1.36, 22    },
	{ 22, "Ti" , "Titanium"     ,  4, 4,  47.8671             ,  4.54      , 1933.15  , 3560   ,  0.523, 1.54, 5650  },
	{ 23, "V"  , "Vanadium"     ,  5, 4,  50.94151            ,  6.11      , 2175.15  , 3680   ,  0.489, 1.63, 120   },
	{ 24, "Cr" , "Chromium"     ,  6, 4,  51.99616            ,  7.15      , 2130.15  , 2944   ,  0.449, 1.66, 102   },
	{ 25, "Mn" , "Manganese"    ,  7, 4,  54.9380455          ,  7.44      , 1519.15  , 2334   ,  0.479, 1.55, 950   },
	{ 26, "Fe" , "Iron"         ,  8, 4,  55.8452             ,  7.874     , 1808.15  , 3134   ,  0.449, 1.83, 56300 },
	{ 27, "Co" , "Cobalt"       ,  9, 4,  58.9331955          ,  8.86      , 1768.15  , 3200   ,  0.421, 1.88, 25    },
	{ 28, "Ni" , "Nickel"       , 10, 4,  58.69344            ,  8.912     , 1726.15  , 3186   ,  0.444, 1.91, 84    },
	{ 29, "Cu" , "Copper"       , 11, 4,  63.5463/*4*/        ,  8.96      , 1357.75  , 2835   ,  0.385, 1.9 , 60    },
	{ 30, "Zn" , "Zinc"         , 12, 4,  65.382              ,  7.134     ,  692.88  , 1180   ,  0.388, 1.65, 70    },
	{ 31, "Ga" , "Gallium"      , 13, 4,  69.7231             ,  5.907     ,  302.91  , 2477   ,  0.371, 1.81, 19    },
	{ 32, "Ge" , "Germanium"    , 14, 4,  72.631              ,  5.323     , 1211.45  , 3106   ,  0.32 , 2.01, 1.5   },
	{ 33, "As" , "Arsenic"      , 15, 4,  74.921602           ,  5.776     , 1090.157 ,  887   ,  0.329, 2.18, 1.8   },
	{ 34, "Se" , "Selenium"     , 16, 4,  78.963/*4*/         ,  4.809     , 494.15   ,  958   ,  0.321, 2.55, 0.05  },
	{ 35, "Br" , "Bromine"      , 17, 4,  79.9041             ,  3.122     , 266.05   ,  332.0 ,  0.474, 2.96, 2.4   },
	{ 36, "Kr" , "Krypton"      , 18, 4,  83.7982/*2 3*/      ,  0.003733  , 115.93   ,  119.93,  0.248, 3   , SMALL },
	{ 37, "Rb" , "Rubidium"     ,  1, 5,  85.46783/*2*/       ,  1.532     , 312.79   ,  961   ,  0.363, 0.82, 90    },
	{ 38, "Sr" , "Strontium"    ,  2, 5,  87.621/*2 4*/       ,  2.64      , 1042.15  , 1655   ,  0.301, 0.95, 370   },
	{ 39, "Y"  , "Yttrium"      ,  3, 5,  88.905852           ,  4.469     , 1799.15  , 3609   ,  0.298, 1.22, 33    },
	{ 40, "Zr" , "Zirconium"    ,  4, 5,  91.2242/*2*/        ,  6.506     , 2125.15  , 4682   ,  0.278, 1.33, 165   },
	{ 41, "Nb" , "Niobium"      ,  5, 5,  92.906382           ,  8.57      , 2741.15  , 5017   ,  0.265, 1.6 , 20    },
	{ 42, "Mo" , "Molybdenum"   ,  6, 5,  95.962/*2*/         , 10.22      , 2890.15  , 4912   ,  0.251, 2.16, 1.2   },
	{ 43, "Tc" , "Technetium"   ,  7, 5, /*98*/NE             , 11.5       , 2473.15  , 5150   ,  BD   , 1.9 , SMALL },
	{ 44, "Ru" , "Ruthenium"    ,  8, 5, 101.072/*2*/         , 12.37      , 2523.15  , 4423   ,  0.238, 2.2 , 0.001 },
	{ 45, "Rh" , "Rhodium"      ,  9, 5, 102.905502           , 12.41      , 2239.15  , 3968   ,  0.243, 2.28, 0.001 },
	{ 46, "Pd" , "Palladium"    , 10, 5, 106.421/*2*/         , 12.02      , 1825.15  , 3236   ,  0.244, 2.2 , 0.015 },
	{ 47, "Ag" , "Silver"       , 11, 5, 107.86822/*2*/       , 10.501     , 1234.15  , 2435   ,  0.235, 1.93, 0.075 },
	{ 48, "Cd" , "Cadmium"      , 12, 5, 112.4118/*2*/        ,  8.69      ,  594.33  , 1040   ,  0.232, 1.69, 0.159 },
	{ 49, "In" , "Indium"       , 13, 5, 114.8183             ,  7.31      ,  429.91  , 2345   ,  0.233, 1.78, 0.25  },
	{ 50, "Sn" , "Tin"          , 14, 5, 118.7107/*2*/        ,  7.287     ,  505.21  , 2875   ,  0.228, 1.96, 2.3   },
	{ 51, "Sb" , "Antimony"     , 15, 5, 121.7601/*2*/        ,  6.685     ,  904.05  , 1860   ,  0.207, 2.05, 0.2   },
	{ 52, "Te" , "Tellurium"    , 16, 5, 127.603/*2*/         ,  6.232     ,  722.8   , 1261   ,  0.202, 2.1 , 0.001 },
	{ 53, "I"  , "Iodine"       , 17, 5, 126.904473           ,  4.93      ,  386.65  ,  457.4 ,  0.214, 2.66, 0.45  },
	{ 54, "Xe" , "Xenon"        , 18, 5, 131.2936/*2 3*/      ,  0.005887  ,  161.45  ,  165.03,  0.158, 2.6 , SMALL },
	{ 55, "Cs" , "Caesium"      ,  1, 6, 132.90545192         ,  1.873     ,  301.7   ,  944   ,  0.242, 0.79, 3     },
	{ 56, "Ba" , "Barium"       ,  2, 6, 137.3277             ,  3.594     , 1002.15  , 2170   ,  0.204, 0.89, 425   },
	{ 57, "La" , "Lanthanum"    ,  0, 6, 138.905477/*2*/      ,  6.145     , 1193.15  , 3737   ,  0.195, 1.1 , 39    },
	{ 58, "Ce" , "Cerium"       ,  0, 6, 140.1161/*2*/        ,  6.77      , 1071.15  , 3716   ,  0.192, 1.12, 66.5  },
	{ 59, "Pr" , "Praseodymium" ,  0, 6, 140.907652           ,  6.773     , 1204.15  , 3793   ,  0.193, 1.13, 9.2   },
	{ 60, "Nd" , "Neodymium"    ,  0, 6, 144.2423/*2*/        ,  7.007     , 1289.15  , 3347   ,  0.19 , 1.14, 41.5  },
	{ 61, "Pm" , "Promethium"   ,  0, 6, /*145*/NE            ,  7.26      , 1204.15  , 3273   ,  BD   , BD  , SMALL },
	{ 62, "Sm" , "Samarium"     ,  0, 6, 150.362/*2*/         ,  7.52      , 1345.15  , 2067   ,  0.197, 1.17, 7.05  },
	{ 63, "Eu" , "Europium"     ,  0, 6, 151.9641/*2*/        ,  5.243     , 1095.15  , 1802   ,  0.182, 1.2 , 2     },
	{ 64, "Gd" , "Gadolinium"   ,  0, 6, 157.253/*2*/         ,  7.895     , 1585.15  , 3546   ,  0.236, 1.2 , 6.2   },
	{ 65, "Tb" , "Terbium"      ,  0, 6, 158.925352           ,  8.229     , 1630.15  , 3503   ,  0.182, 1.2 , 1.2   },
	{ 66, "Dy" , "Dysprosium"   ,  0, 6, 162.5001/*2*/        ,  8.55      , 1680.15  , 2840   ,  0.17 , 1.22, 5.2   },
	{ 67, "Ho" , "Holmium"      ,  0, 6, 164.930322           ,  8.795     , 1743.15  , 2993   ,  0.165, 1.23, 1.3   },
	{ 68, "Er" , "Erbium"       ,  0, 6, 167.2593/*2*/        ,  9.066     , 1795.15  , 3503   ,  0.168, 1.24, 3.5   },
	{ 69, "Tm" , "Thulium"      ,  0, 6, 168.934212           ,  9.321     , 1818.15  , 2223   ,  0.16 , 1.25, 0.52  },
	{ 70, "Yb" , "Ytterbium"    ,  0, 6, 173.0545/*2*/        ,  6.965     , 1097.15  , 1469   ,  0.155, 1.1 , 3.2   },
	{ 71, "Lu" , "Lutetium"     ,  3, 6, 174.96681/*2*/       ,  9.84      , 1936.15  , 3675   ,  0.154, 1.27, 0.8   },
	{ 72, "Hf" , "Hafnium"      ,  4, 6, 178.492              , 13.31      , 2500.15  , 4876   ,  0.144, 1.3 , 3     },
	{ 73, "Ta" , "Tantalum"     ,  5, 6, 180.947882           , 16.654     , 3269.15  , 5731   ,  0.14 , 1.5 , 2     },
	{ 74, "W"  , "Tungsten"     ,  6, 6, 183.841              , 19.25      , 3680.15  , 5828   ,  0.132, 2.36, 1.3   },
	{ 75, "Re" , "Rhenium"      ,  7, 6, 186.2071             , 21.02      , 3453.15  , 5869   ,  0.137, 1.9 , SMALL },
	{ 76, "Os" , "Osmium"       ,  8, 6, 190.233/*2*/         , 22.61      , 3300.15  , 5285   ,  0.13 , 2.2 , 0.002 },
	{ 77, "Ir" , "Iridium"      ,  9, 6, 192.2173             , 22.56      , 2716.15  , 4701   ,  0.131, 2.2 , 0.001 },
	{ 78, "Pt" , "Platinum"     , 10, 6, 195.0849             , 21.46      , 2045.15  , 4098   ,  0.133, 2.28, 0.005 },
	{ 79, "Au" , "Gold"         , 11, 6, 196.9665694          , 19.282     , 1337.73  , 3129   ,  0.129, 2.54, 0.004 },
	{ 80, "Hg" , "Mercury"      , 12, 6, 200.592              , 13.5336    ,  234.43  ,  630   ,  0.14 , 2   , 0.085 },
	{ 81, "Tl" , "Thallium"     , 13, 6, 204.38332/*9*/       , 11.85      ,  577.15  , 1746   ,  0.129, 1.62, 0.85  },
	{ 82, "Pb" , "Lead"         , 14, 6, 207.21/*2 4*/        , 11.342     ,  600.75  , 2022   ,  0.129, 2.33, 14    },
	{ 83, "Bi" , "Bismuth"      , 15, 6, 208.980401/*1*/      ,  9.807     ,  544.67  , 1837   ,  0.122, 2.02, 0.009 },
	{ 84, "Po" , "Polonium"     , 16, 6, /*209*/NE            ,  9.32      ,  527.15  , 1235   ,  BD   , 2   , SMALL },
	{ 85, "At" , "Astatine"     , 17, 6, /*210*/NE            ,  7         ,  575.15  ,  610   ,  BD   , 2.2 , SMALL },
	{ 86, "Rn" , "Radon"        , 18, 6, /*222*/NE            ,  0.00973   ,  202.15  ,  211.3 ,  0.094, BD  , SMALL },
	{ 87, "Fr" , "Francium"     ,  1, 7, /*223*/NE            ,  1.87      ,  300.15  ,  950   ,  BD   , 0.7 , SMALL },
	{ 88, "Ra" , "Radium"       ,  2, 7, /*226*/NE            ,  5.5       ,  973.15  , 2010   ,  BD   , 0.9 , SMALL },
	{ 89, "Ac" , "Actinium"     ,  0, 7, /*227*/NE            , 10.07      , 1323.15  , 3471   ,  0.12 , 1.1 , SMALL },
	{ 90, "Th" , "Thorium"      ,  0, 7, 232.038062/*1 2*/    , 11.72      , 2028.15  , 5061   ,  0.113, 1.3 , 9.6   },
	{ 91, "Pa" , "Protactinium" ,  0, 7, 231.035882/*1*/      , 15.37      , 1873.15  , 4300   ,  BD   , 1.5 , SMALL },
	{ 92, "U"  , "Uranium"      ,  0, 7, 238.028913/*1*/      , 18.95      , 1405.15  , 4404   ,  0.116, 1.38, 2.7   },
	{ 93, "Np" , "Neptunium"    ,  0, 7, /*237*/NE            , 20.45      ,  913.15  , 4273   ,  BD   , 1.36, SMALL },
	{ 94, "Pu" , "Plutonium"    ,  0, 7, /*244*/NE            , 19.84      ,  913.15  , 3501   ,  BD   , 1.28, SMALL },
	{ 95, "Am" , "Americium"    ,  0, 7, /*243*/NE            , 13.69      , 1267.15  , 2880   ,  BD   , 1.3 , SMALL },
	{ 96, "Cm" , "Curium"       ,  0, 7, /*247*/NE            , 13.51      , 1340.15  , 3383   ,  BD   , 1.3 , SMALL },
	{ 97, "Bk" , "Berkelium"    ,  0, 7, /*247*/NE            , 14.79      , 1259.15  ,  983   ,  BD   , 1.3 , SMALL },
	{ 98, "Cf" , "Californium"  ,  0, 7, /*251*/NE            , 15.1       , 1925.15  , 1173   ,  BD   , 1.3 , SMALL },
	{ 99, "Es" , "Einsteinium"  ,  0, 7, /*252*/NE            , 13.5       , 1133.15  , BD     ,  BD   , 1.3 , 0/*8*/},
	{100, "Fm" , "Fermium"      ,  0, 7, /*257*/NE            ,   BD       , 1800     , BD     ,  BD   , 1.3 , 0/*8*/},
	{101, "Md" , "Mendelevium"  ,  0, 7, /*258*/NE            ,   BD       , 1100     , BD     ,  BD   , 1.3 , 0/*8*/},
	{102, "No" , "Nobelium"     ,  0, 7, /*259*/NE            ,   BD       , 1100     , BD     ,  BD   , 1.3 , 0/*8*/},
	{103, "Lr" , "Lawrencium"   ,  3, 7, /*262*/NE            ,   BD       , 1900     , BD     ,  BD   , 1.3 , 0/*8*/},
	{104, "Rf" , "Rutherfordium",  4, 7, /*267*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{105, "Db" , "Dubnium"      ,  5, 7, /*268*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{106, "Sg" , "Seaborgium"   ,  6, 7, /*269*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{107, "Bh" , "Bohrium"      ,  7, 7, /*270*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{108, "Hs" , "Hassium"      ,  8, 7, /*269*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{109, "Mt" , "Meitnerium"   ,  9, 7, /*278*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{110, "Ds" , "Darmstadtium" , 10, 7, /*281*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{111, "Rg" , "Roentgenium"  , 11, 7, /*281*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{112, "Cn" , "Copernicium"  , 12, 7, /*285*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{113, "Uut", "Ununtrium"    , 13, 7, /*286*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{114, "Fl" , "Flerovium"    , 14, 7, /*289*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{115, "Uup", "Ununpentium"  , 15, 7, /*288*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{116, "Lv" , "Livermorium"  , 16, 7, /*293*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{117, "Uus", "Ununseptium"  , 17, 7, /*294*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
	{118, "Uuo", "Ununoctium"   , 18, 7, /*294*/NE            ,   BD       ,   BD     , BD     ,  BD   , BD  , 0/*8*/},
};


