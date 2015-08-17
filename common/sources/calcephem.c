#ifdef    _MSC_VER
#define   _USE_MATH_DEFINES
#endif    /* _MSC_VER */
#include  "calcephem.h"
#include  <string.h>
#include  <time.h>
#include  <math.h>


static double Moon(double T, double *LAMBDA, double *BETA, double *R, double *AGE);
static double sine(double phi);
static double frac(double x);
static void addsol(double, double, double, double, int, int, int, int);
static void term(int, int, int, int, double*, double*);
static void addthe(double, double, double, double, double*, double*);
static void addn(double, int, int, int, int);
static double NewMoon(double ax, double bx, double cx);
/*static void MiniMoon(double T, double *RA, double *DEC);*/
/*static void MoonRise(int year, int month, int day, double LocalHour,
    double *UTRise, double *UTSet);*/
/*static void UTTohhmm(double UT, int *h, int *m);*/
/*static void Interp(double ym, double y0, double yp, double *xe, double *ye,
    double *z1, double *z2, int *nz);*/
/*static double SinH(int year, int month, int day, double UT);*/
static double kepler(double M,double e);
static int DayofYear(int year,int month,int day);
static int DayofWeek(int year,int month,int day,char dowstr[]);
static double jd(int ny,int nm,int nd,double UT);
static double hour24(double hour);
static double angle2pi(double angle);
static double angle360(double angle);
/*static void Radec_to_Cart(double ra,double dec,Vector *r);*/
/*static int LeapYear(int year);*/


/*
 *  Calculates Moon's position according to Brown's Lunar Theory...
 */

#include  <math.h>
#define DegPerRad       57.29577951308232087680
#define RadPerDeg        0.01745329251994329576

/*double angle360();*/

/*void addthe(double, double, double, double, double*, double*);*/
/*void addsol(double, double, double, double, int, int, int, int);*/
/*void addn(double, int, int, int, int);*/
/*void term(int, int, int, int, double*, double*);*/

static const double TwoPi = 6.283185308;
static const double ARC = 206264.81;
/*double sine(), frac();*/
static double  DLAM, DLAMS;
static double  DS;
static double  GAM1C;
static double  SINPI;
static double  N;
static double  CO[14][5], SI[14][5];

double Moon(double T, double *LAMBDA, double *BETA, double *R, double *AGE){

  double T2;
  double S1, S2, S3, S4, S5, S6, S7;
  double DL0, DL, DD, DGAM, DLS, DF;
  double L0, L, LS, F, D;
  double ARG = 0.0, FAC = 0.0;
  int MAX = 0, i, j;
  double S;


  T2 = T*T;
  DLAM = 0.0, DS = 0.0, GAM1C = 0.0; SINPI = 3422.7000;

  /*
   * Long Periodic variations
   */
  S1 = sine( 0.19833 + 0.05611*T );
  S2 = sine( 0.27869 + 0.04508*T );
  S3 = sine( 0.16827 - 0.36903*T );
  S4 = sine( 0.34734 - 5.37261*T );
  S5 = sine( 0.10498 - 5.37899*T );
  S6 = sine( 0.42681 - 0.41855*T );
  S7 = sine( 0.14943 - 5.37511*T );
  DL0 = 0.84*S1 + 0.31*S2 + 14.27*S3 + 7.26*S4 + 0.28*S5 + 0.24*S6;
  DL  = 2.94*S1 + 0.31*S2 + 14.27*S3 + 9.34*S4 + 1.12*S5 + 0.83*S6;
  DLS = -6.40*S1 - 1.89*S6;
  DF = 0.21*S1 + 0.31*S2 + 14.27*S3 - 88.70*S4 - 15.30*S5 + 0.24*S6 - 1.86*S7;
  DD = DL0 - DLS;
  DGAM = -3332e-9 * sine( 0.59734 - 5.37261*T)
      -539e-9 * sine( 0.35498 - 5.37899*T)
      -64e-9 * sine( 0.39943 - 5.37511*T);



  L0  = TwoPi*frac( 0.60643382 + 1336.85522467*T - 0.00000313*T2 ) + DL0/ARC;
  L   = TwoPi*frac( 0.37489701 + 1325.55240982*T + 0.00002565*T2 ) + DL/ARC;
  LS  = TwoPi*frac( 0.99312619 +   99.99735956*T - 0.00000044*T2 ) + DLS/ARC;
  F   = TwoPi*frac( 0.25909118 + 1342.22782980*T - 0.00000892*T2 ) + DF/ARC;
  D   = TwoPi*frac( 0.82736186 + 1236.85308708*T - 0.00000397*T2 ) + DD/ARC;

  for (i=1; i<=4; ++i){
    switch (i){
      case 1:
        ARG = L,  MAX = 4, FAC = 1.000002208;
        break;
      case 2:
        ARG = LS, MAX = 3, FAC = 0.997504612 - 0.002495388*T;
        break;
      case 3:
        ARG = F,  MAX = 4, FAC = 1.000002708 + 139.978*DGAM;
        break;
      case 4:
        ARG = D,  MAX = 6, FAC = 1.0;
        break;
    }

    CO[6+0][i] = 1.0, CO[6+1][i] = cos(ARG)*FAC;
    SI[6+0][i] = 0.0, SI[6+1][i] = sin(ARG)*FAC;
    for (j=2; j<=MAX; ++j) addthe(CO[6+j-1][i], SI[6+j-1][i], CO[6+1][i], SI[6+1][i], &CO[6+j][i], &SI[6+j][i]);
    for (j=1; j<=MAX; ++j) {
      CO[6-j][i] = CO[6+j][i];
      SI[6-j][i] = -SI[6+j][i];
    }


  }



  /*
   *  Solar1
   */
  addsol(   13.902,   14.06,-0.001,   0.2607,0, 0, 0, 4);
  addsol(    0.403,   -4.01,+0.394,   0.0023,0, 0, 0, 3);
  addsol( 2369.912, 2373.36,+0.601,  28.2333,0, 0, 0, 2);
  addsol( -125.154, -112.79,-0.725,  -0.9781,0, 0, 0, 1);
  addsol(    1.979,    6.98,-0.445,   0.0433,1, 0, 0, 4);
  addsol(  191.953,  192.72,+0.029,   3.0861,1, 0, 0, 2);
  addsol(   -8.466,  -13.51,+0.455,  -0.1093,1, 0, 0, 1);
  addsol(22639.500,22609.07,+0.079, 186.5398,1, 0, 0, 0);
  addsol(   18.609,    3.59,-0.094,   0.0118,1, 0, 0,-1);
  addsol(-4586.465,-4578.13,-0.077,  34.3117,1, 0, 0,-2);
  addsol(   +3.215,    5.44,+0.192,  -0.0386,1, 0, 0,-3);
  addsol(  -38.428,  -38.64,+0.001,   0.6008,1, 0, 0,-4);
  addsol(   -0.393,   -1.43,-0.092,   0.0086,1, 0, 0,-6);
  addsol(   -0.289,   -1.59,+0.123,  -0.0053,0, 1, 0, 4);
  addsol(  -24.420,  -25.10,+0.040,  -0.3000,0, 1, 0, 2);
  addsol(   18.023,   17.93,+0.007,   0.1494,0, 1, 0, 1);
  addsol( -668.146, -126.98,-1.302,  -0.3997,0, 1, 0, 0);
  addsol(    0.560,    0.32,-0.001,  -0.0037,0, 1, 0,-1);
  addsol( -165.145, -165.06,+0.054,   1.9178,0, 1, 0,-2);
  addsol(   -1.877,   -6.46,-0.416,   0.0339,0, 1, 0,-4);
  addsol(    0.213,    1.02,-0.074,   0.0054,2, 0, 0, 4);
  addsol(   14.387,   14.78,-0.017,   0.2833,2, 0, 0, 2);
  addsol(   -0.586,   -1.20,+0.054,  -0.0100,2, 0, 0, 1);
  addsol(  769.016,  767.96,+0.107,  10.1657,2, 0, 0, 0);
  addsol(   +1.750,    2.01,-0.018,   0.0155,2, 0, 0,-1);
  addsol( -211.656, -152.53,+5.679,  -0.3039,2, 0, 0,-2);
  addsol(   +1.225,    0.91,-0.030,  -0.0088,2, 0, 0,-3);
  addsol(  -30.773,  -34.07,-0.308,   0.3722,2, 0, 0,-4);
  addsol(   -0.570,   -1.40,-0.074,   0.0109,2, 0, 0,-6);
  addsol(   -2.921,  -11.75,+0.787,  -0.0484,1, 1, 0, 2);
  addsol(   +1.267,    1.52,-0.022,   0.0164,1, 1, 0, 1);
  addsol( -109.673, -115.18,+0.461,  -0.9490,1, 1, 0, 0);
  addsol( -205.962, -182.36,+2.056,  +1.4437,1, 1, 0,-2);
  addsol(    0.233,    0.36, 0.012,  -0.0025,1, 1, 0,-3);
  addsol(   -4.391,   -9.66,-0.471,   0.0673,1, 1, 0,-4);


  /*
   *  Solar2
   */
  addsol(    0.283,    1.53,-0.111,  +0.0060,1,-1, 0,+4);
  addsol(   14.577,   31.70,-1.540,  +0.2302,1,-1, 0, 2);
  addsol(  147.687,  138.76,+0.679,  +1.1528,1,-1, 0, 0);
  addsol(   -1.089,    0.55,+0.021,   0.0   ,1,-1, 0,-1);
  addsol(   28.475,   23.59,-0.443,  -0.2257,1,-1, 0,-2);
  addsol(   -0.276,   -0.38,-0.006,  -0.0036,1,-1, 0,-3);
  addsol(    0.636,    2.27,+0.146,  -0.0102,1,-1, 0,-4);
  addsol(   -0.189,   -1.68,+0.131,  -0.0028,0, 2, 0, 2);
  addsol(   -7.486,   -0.66,-0.037,  -0.0086,0, 2, 0, 0);
  addsol(   -8.096,  -16.35,-0.740,   0.0918,0, 2, 0,-2);
  addsol(   -5.741,   -0.04, 0.0  ,  -0.0009,0, 0, 2, 2);
  addsol(    0.255,    0.0 , 0.0  ,   0.0   ,0, 0, 2, 1);
  addsol( -411.608,   -0.20, 0.0  ,  -0.0124,0, 0, 2, 0);
  addsol(    0.584,    0.84, 0.0  ,  +0.0071,0, 0, 2,-1);
  addsol(  -55.173,  -52.14, 0.0  ,  -0.1052,0, 0, 2,-2);
  addsol(    0.254,    0.25, 0.0  ,  -0.0017,0, 0, 2,-3);
  addsol(   +0.025,   -1.67, 0.0  ,  +0.0031,0, 0, 2,-4);
  addsol(    1.060,    2.96,-0.166,   0.0243,3, 0, 0,+2);
  addsol(   36.124,   50.64,-1.300,   0.6215,3, 0, 0, 0);
  addsol(  -13.193,  -16.40,+0.258,  -0.1187,3, 0, 0,-2);
  addsol(   -1.187,   -0.74,+0.042,   0.0074,3, 0, 0,-4);
  addsol(   -0.293,   -0.31,-0.002,   0.0046,3, 0, 0,-6);
  addsol(   -0.290,   -1.45,+0.116,  -0.0051,2, 1, 0, 2);
  addsol(   -7.649,  -10.56,+0.259,  -0.1038,2, 1, 0, 0);
  addsol(   -8.627,   -7.59,+0.078,  -0.0192,2, 1, 0,-2);
  addsol(   -2.740,   -2.54,+0.022,   0.0324,2, 1, 0,-4);
  addsol(    1.181,    3.32,-0.212,   0.0213,2,-1, 0,+2);
  addsol(    9.703,   11.67,-0.151,   0.1268,2,-1, 0, 0);
  addsol(   -0.352,   -0.37,+0.001,  -0.0028,2,-1, 0,-1);
  addsol(   -2.494,   -1.17,-0.003,  -0.0017,2,-1, 0,-2);
  addsol(    0.360,    0.20,-0.012,  -0.0043,2,-1, 0,-4);
  addsol(   -1.167,   -1.25,+0.008,  -0.0106,1, 2, 0, 0);
  addsol(   -7.412,   -6.12,+0.117,   0.0484,1, 2, 0,-2);
  addsol(   -0.311,   -0.65,-0.032,   0.0044,1, 2, 0,-4);
  addsol(   +0.757,    1.82,-0.105,   0.0112,1,-2, 0, 2);
  addsol(   +2.580,    2.32,+0.027,   0.0196,1,-2, 0, 0);
  addsol(   +2.533,    2.40,-0.014,  -0.0212,1,-2, 0,-2);
  addsol(   -0.344,   -0.57,-0.025,  +0.0036,0, 3, 0,-2);
  addsol(   -0.992,   -0.02, 0.0  ,   0.0   ,1, 0, 2, 2);
  addsol(  -45.099,   -0.02, 0.0  ,  -0.0010,1, 0, 2, 0);
  addsol(   -0.179,   -9.52, 0.0  ,  -0.0833,1, 0, 2,-2);
  addsol(   -0.301,   -0.33, 0.0  ,   0.0014,1, 0, 2,-4);
  addsol(   -6.382,   -3.37, 0.0  ,  -0.0481,1, 0,-2, 2);
  addsol(   39.528,   85.13, 0.0  ,  -0.7136,1, 0,-2, 0);
  addsol(    9.366,    0.71, 0.0  ,  -0.0112,1, 0,-2,-2);
  addsol(    0.202,    0.02, 0.0  ,   0.0   ,1, 0,-2,-4);

  /*
   *  Solar3
   */
  addsol(    0.415,    0.10, 0.0  ,  0.0013,0, 1, 2, 0);
  addsol(   -2.152,   -2.26, 0.0  , -0.0066,0, 1, 2,-2);
  addsol(   -1.440,   -1.30, 0.0  , +0.0014,0, 1,-2, 2);
  addsol(    0.384,   -0.04, 0.0  ,  0.0   ,0, 1,-2,-2);
  addsol(   +1.938,   +3.60,-0.145, +0.0401,4, 0, 0, 0);
  addsol(   -0.952,   -1.58,+0.052, -0.0130,4, 0, 0,-2);
  addsol(   -0.551,   -0.94,+0.032, -0.0097,3, 1, 0, 0);
  addsol(   -0.482,   -0.57,+0.005, -0.0045,3, 1, 0,-2);
  addsol(    0.681,    0.96,-0.026,  0.0115,3,-1, 0, 0);
  addsol(   -0.297,   -0.27, 0.002, -0.0009,2, 2, 0,-2);
  addsol(    0.254,   +0.21,-0.003,  0.0   ,2,-2, 0,-2);
  addsol(   -0.250,   -0.22, 0.004,  0.0014,1, 3, 0,-2);
  addsol(   -3.996,    0.0 , 0.0  , +0.0004,2, 0, 2, 0);
  addsol(    0.557,   -0.75, 0.0  , -0.0090,2, 0, 2,-2);
  addsol(   -0.459,   -0.38, 0.0  , -0.0053,2, 0,-2, 2);
  addsol(   -1.298,    0.74, 0.0  , +0.0004,2, 0,-2, 0);
  addsol(    0.538,    1.14, 0.0  , -0.0141,2, 0,-2,-2);
  addsol(    0.263,    0.02, 0.0  ,  0.0   ,1, 1, 2, 0);
  addsol(    0.426,   +0.07, 0.0  , -0.0006,1, 1,-2,-2);
  addsol(   -0.304,   +0.03, 0.0  , +0.0003,1,-1, 2, 0);
  addsol(   -0.372,   -0.19, 0.0  , -0.0027,1,-1,-2, 2);
  addsol(   +0.418,    0.0 , 0.0  ,  0.0   ,0, 0, 4, 0);
  addsol(   -0.330,   -0.04, 0.0  ,  0.0   ,3, 0, 2, 0);

  N = 0.0;
  addn(-526.069, 0, 0,1,-2); addn(  -3.352, 0, 0,1,-4);
  addn( +44.297,+1, 0,1,-2); addn(  -6.000,+1, 0,1,-4);
  addn( +20.599,-1, 0,1, 0); addn( -30.598,-1, 0,1,-2);
  addn( -24.649,-2, 0,1, 0); addn(  -2.000,-2, 0,1,-2);
  addn( -22.571, 0,+1,1,-2); addn( +10.985, 0,-1,1,-2);

  DLAM += +0.82*sine( 0.7736   -62.5512*T ) + 0.31*sine( 0.0466  -125.1025*T )
          +0.35*sine( 0.5785   -25.1042*T ) + 0.66*sine( 0.4591 +1335.8075*T )
          +0.64*sine( 0.3130   -91.5680*T ) + 1.14*sine( 0.1480 +1331.2898*T )
          +0.21*sine( 0.5918 +1056.5859*T ) + 0.44*sine( 0.5784 +1322.8595*T )
          +0.24*sine( 0.2275    -5.7374*T ) + 0.28*sine( 0.2965    +2.6929*T )
          +0.33*sine( 0.3132    +6.3368*T );









  *LAMBDA = 360.0*frac( (L0+DLAM/ARC)/TwoPi );

  S = F + DS/ARC;
  FAC = 1.000002708 + 139.978*DGAM;
  *BETA = (FAC*(18518.511 + 1.189 + GAM1C)*sin(S) - 6.24*sin(3*S) + N)/3600.0;

  SINPI *= 0.999953253;
  *R = ARC/SINPI;


  DLAMS = 6893.0 * sin(LS) + 72.0 * sin(2.0*LS);

  *AGE = 29.530589*frac((D+(DLAM-DLAMS)/ARC)/TwoPi);
/*
printf("Diff = %f\n", 360.0*frac((D+(DLAM-DLAMS)/ARC)/TwoPi));
*/

  /*
   *  Return the phase.
   */
/*
  return( 0.5*(1.0 - cos(D+(DLAM-DLAMS)/ARC)) );
*/
  return( *AGE/29.530589 );



}


double sine(double phi){

  return( sin(TwoPi*frac(phi)) );

}


double frac(double x){

  x -= (int)x;
  return( (x<0) ? x+1.0 : x );

}



void addsol(double COEFFL, double COEFFS, double COEFFG, double COEFFP, int P, int Q, int R, int S){

  double X, Y;

  term(P, Q, R, S, &X, &Y);
  DLAM += COEFFL*Y;
  DS += COEFFS*Y;
  GAM1C += COEFFG*X;
  SINPI += COEFFP*X;


}



void term(int P, int Q, int R, int S, double *X, double *Y){

  double XX, YY;
  int k, I[5];

  I[1] = P, I[2] = Q, I[3] = R, I[4] = S, XX = 1.0, YY = 0.0;
  for (k=1; k<=4; ++k){
    if (I[k] != 0.0){
      addthe(XX, YY, CO[6+I[k]][k], SI[6+I[k]][k], &XX, &YY);
    }
  }
  *X = XX;
  *Y = YY;

}



void addthe(double C1, double S1, double C2, double S2, double *C, double *S){

  *C = C1*C2 - S1*S2;
  *S = S1*C2 + C1*S2;


}


void addn(double COEFFN, int P, int Q, int R, int S){

  double X, Y;

  term(P, Q, R, S, &X, &Y);
  N += COEFFN*Y;


}



#define Rdefine 0.61803399
#define Cdefine 0.38196601

double NewMoon(double ax, double bx, double cx){

  double f1, f2, x0, x1, x2, x3/*, Moon()*/;
  double L, B, Rad, AGE, tol=1e-7;

  x0 = ax;
  x3 = cx;
  if (fabs(cx-bx) > fabs(bx-ax)){
    x1 = bx;
    x2 = bx + Cdefine*(cx-bx);
  } else {
    x2 = bx;
    x1 = bx - Cdefine*(bx-ax);
  }
  f1 = Moon(x1, &L, &B, &Rad, &AGE);
  f2 = Moon(x2, &L, &B, &Rad, &AGE);
  while (fabs(x3-x0) > tol*(fabs(x1)+fabs(x2))){
    if (f2 < f1){
      x0 = x1;
      x1 = x2;
      x2 = Rdefine*x1+Cdefine*x3;
      f1 = f2;
      f2 = Moon(x2, &L, &B, &Rad, &AGE);
    } else {
      x3 = x2;
      x2 = x1;
      x1 = Rdefine*x2+Cdefine*x0;
      f2 = f1;
      f1 = Moon(x1, &L, &B, &Rad, &AGE);
    }
  }
  if (f1 < f2){
    return(x1);
  } else {
    return(x2);
  }
}




#if 0
/*
 * MINI_MOON: low precision lunar coordinates (approx. 5'/1')
 *            T  : time in Julian centuries since J2000
 *                 ( T=(JD-2451545)/36525 )
 *            RA : right ascension (in h; equinox of date)
 *            DEC: declination (in deg; equinox of date)
 *
 */
void MiniMoon(double T, double *RA, double *DEC){

  double L0,L,LS,F,D,H,S,N,DL,CB,L_MOON,B_MOON,V,W,X,Y,Z,RHO;
  double /*frac(), */cosEPS, sinEPS, P2, ARC;


  cosEPS = 0.91748;
  sinEPS = 0.39778;
  P2 	= 6.283185307;
  ARC = 206264.8062;


  /*
   * mean elements of lunar orbit
   */
  L0 = frac(0.606433+1336.855225*T); /* mean longitude Moon (in rev) */
  L  = P2*frac(0.374897+1325.552410*T); /* mean anomaly of the Moon     */
  LS = P2*frac(0.993133+  99.997361*T); /* mean anomaly of the Sun      */
  D  = P2*frac(0.827361+1236.853086*T); /* diff. longitude Moon-Sun     */
  F  = P2*frac(0.259086+1342.227825*T); /* mean argument of latitude    */
  DL  =  +22640.0*sin(L) - 4586.0*sin(L-2.0*D) + 2370.0*sin(2.0*D) +  769.0*sin(2.0*L)
           -668.0*sin(LS)- 412.0*sin(2.0*F) - 212.0*sin(2.0*L-2.0*D) - 206.0*sin(L+LS-2.0*D)
           +192.0*sin(L+2.0*D) - 165.0*sin(LS-2.0*D) - 125.0*sin(D) - 110.0*sin(L+LS)
           +148.0*sin(L-LS) - 55.0*sin(2.0*F-2.0*D);
  S  =  F + (DL+412.0*sin(2.0*F)+541.0*sin(LS)) / ARC;
  H  =  F-2.0*D;
  N  =  -526.0*sin(H) + 44.0*sin(L+H) - 31.0*sin(-L+H) - 23.0*sin(LS+H)
        + 11.0*sin(-LS+H) -25.0*sin(-2.0*L+F) + 21.0*sin(-L+F);
  L_MOON  =  P2 * frac ( L0 + DL/1296e3 ); /* in rad */
  B_MOON  =  ( 18520.0*sin(S) + N ) / ARC; /* in rad */

  /* equatorial coordinates */
  CB = cos(B_MOON);
  X = CB*cos(L_MOON);
  V = CB*sin(L_MOON);
  W = sin(B_MOON);
  Y = cosEPS*V-sinEPS*W;
  Z = sinEPS*V+cosEPS*W;
  RHO = sqrt(1.0-Z*Z);
  *DEC  =  (360.0/P2)*atan2(Z, RHO);
  *RA   =  ( 48.0/P2)*atan2(Y, X+RHO);
  if (*RA<0.0) *RA += 24.0;



}
#endif


/*#include <stdio.h>*/
/*#include <math.h>*/
/*#include "MoonRise.h"*/
/*#include "Moon.h"*/

/*#define DegPerRad       57.29577951308232087680*/
/*#define RadPerDeg        0.01745329251994329576*/

/*extern static double Glon, SinGlat, CosGlat, TimeZone;*/

#if 0
void MoonRise(int year, int month, int day, double LocalHour, double *UTRise, double *UTSet){

  double UT, ym, y0, yp, SinH0;
  double xe, ye, z1, z2/*, SinH(), hour24()*/;
  int Rise, Set, nz;

  SinH0 = sin( 8.0/60.0 * RadPerDeg );


  UT = 1.0+TimeZone;
  *UTRise = -999.0;
  *UTSet = -999.0;
  Rise = Set = 0;
  ym = SinH(year, month, day, UT-1.0) - SinH0;

  while ( (UT <= 24.0+TimeZone) ) {

  y0 = SinH(year, month, day, UT) - SinH0;
  yp = SinH(year, month, day, UT+1.0) - SinH0;

  Interp(ym, y0, yp, &xe, &ye, &z1, &z2, &nz);

  switch(nz){

    case 0:
      break;
    case 1:
      if (ym < 0.0){
        *UTRise = UT + z1;
        Rise = 1;
      } else {
        *UTSet = UT + z1;
        Set = 1;
      }
      break;
    case 2:
      if (ye < 0.0){
        *UTRise = UT + z2;
        *UTSet = UT + z1;
      } else {
        *UTRise = UT + z1;
        *UTSet = UT + z2;
      }
      Rise = 1;
      Set = 1;
      break;
    }
    ym = yp;
    UT += 2.0;

  }

  if (Rise){
    *UTRise -= TimeZone;
    *UTRise = hour24(*UTRise);
  } else {
    *UTRise = -999.0;
  }

  if (Set){
    *UTSet -= TimeZone;
    *UTSet = hour24(*UTSet);
  } else {
    *UTSet = -999.0;
  }

}


void UTTohhmm(double UT, int *h, int *m){


  if (UT < 0.0) {
    *h = -1.0;
    *m = -1.0;
  } else {
    *h = (int)UT;
    *m = (int)((UT-(double)(*h))*60.0+0.5);
    if (*m == 60) {
      /*
       *  If it was 23:60 this should become 24:00
       *  I prefer this designation to 00:00. So dont reset h to 0 when it goes above 24.
       */
      *h += 1;
      *m = 0;
    }
  }

}






void Interp(double ym, double y0, double yp, double *xe, double *ye, double *z1, double *z2, int *nz){

  double a, b, c, d, dx;

  *nz = 0;
  a = 0.5*(ym+yp)-y0;
  b = 0.5*(yp-ym);
  c = y0;
  *xe = -b/(2.0*a);
  *ye = (a*(*xe) + b) * (*xe) + c;
  d = b*b - 4.0*a*c;

  if (d >= 0){
    dx = 0.5*sqrt(d)/fabs(a);
    *z1 = *xe - dx;
    *z2 = *xe+dx;
    if (fabs(*z1) <= 1.0) *nz += 1;
    if (fabs(*z2) <= 1.0) *nz += 1;
    if (*z1 < -1.0) *z1 = *z2;
  }



}




double SinH(int year, int month, int day, double UT){

  double TU/*, frac(), jd()*/;
  double RA_Moon, DEC_Moon, gmst, lmst, Tau/*, Moon()*/;
  /*  double angle2pi();*/

  TU = (jd(year, month, day, UT) - 2451545.0)/36525.0;

  /* this is more accurate, but wasteful for this -- use low res approx.
  TU2 = TU*TU;
  TU3 = TU2*TU;
  Moon(TU, &LambdaMoon, &BetaMoon, &R, &AGE);
  LambdaMoon *= RadPerDeg;
  BetaMoon *= RadPerDeg;
  epsilon = (23.43929167 - 0.013004166*TU - 1.6666667e-7*TU2 - 5.0277777778e-7*TU3)*RadPerDeg;
  RA_Moon  = angle2pi(atan2(sin(LambdaMoon)*cos(epsilon)-tan(BetaMoon)*sin(epsilon), cos(LambdaMoon)));
  DEC_Moon = asin( sin(BetaMoon)*cos(epsilon) + cos(BetaMoon)*sin(epsilon)*sin(LambdaMoon));
  */

  MiniMoon(TU, &RA_Moon, &DEC_Moon);
  RA_Moon *= 15.0*RadPerDeg;
  DEC_Moon *= RadPerDeg;

  /*
   *  Compute Greenwich Mean Sidereal Time (gmst)
   */
  UT = 24.0*frac( UT/24.0 );
  /* this is for the ephemeris meridian???
  gmst = 6.697374558 + 1.0027379093*UT + (8640184.812866+(0.093104-6.2e-6*TU)*TU)*TU/3600.0;
  */
  gmst = UT + 6.697374558 + (8640184.812866+(0.093104-6.2e-6*TU)*TU)*TU/3600.0;
  lmst = 24.0*frac( (gmst-Glon/15.0) / 24.0 );

  Tau = 15.0*lmst*RadPerDeg - RA_Moon;
  return( SinGlat*sin(DEC_Moon) + CosGlat*cos(DEC_Moon)*cos(Tau) );


}
#endif
/*#include <string.h>*/
/*#include "CalcEphem.h"*/


void CalcEphem(long int date,double UT,CTrans *c)
{
  int    year, month, day;
  double TU, TU2, TU3, T0/*, gmst*/;
  double varep, varpi;
  double eccen, epsilon;
  double days, M, E, nu, lambnew;
  double r0, earth_sun_distance;
  double RA, DEC, RA_Moon, DEC_Moon;
  double TDT, AGE, LambdaMoon, BetaMoon, R;
  /* double jd(), hour24(), angle2pi(), angle360(), kepler(), Moon(), NewMoon();*/
  double Ta, Tb, Tc/*, frac()*/;
  double SinGlat, CosGlat,/* SinGlon, CosGlon,*/ Tau, lmst, x, y, z;
  double SinTau, CosTau, SinDec, CosDec;





  c->UT = UT;
  year = (int)(date/10000);
  month = (int)( (date - year*10000)/100 );
  day = (int)( date - year*10000 - month*100 );
  c->year = year;
  c->month = month;
  c->day = day;

  c->doy = DayofYear(year, month, day);
  c->dow = DayofWeek(year, month, day, c->dowstr);



  /*
   *  Compute Greenwich Mean Sidereal Time (gmst)
   *  The TU here is number of Julian centuries
   *  since 2000 January 1.5
   *  From the 1996 astronomical almanac
   */
  TU = (jd(year, month, day, 0.0) - 2451545.0)/36525.0;
  TU2 = TU*TU;
  TU3 = TU2*TU;
  T0 = (6.0 + 41.0/60.0 + 50.54841/3600.0) + 8640184.812866/3600.0*TU
          + 0.093104/3600.0*TU2 - 6.2e-6/3600.0*TU3;
  T0 = hour24(T0);
  c->gmst = hour24(T0 + UT*1.002737909);


  /* convert to radians for ease later on */
  /* gmst = c->gmst*15.0*M_PI/180.0;*/

  lmst = 24.0*frac( (c->gmst - c->Glon/15.0) / 24.0 );






  /*
   *
   *   Construct Transformation Matrix from GEI to GSE  systems
   *
   *
   *   First compute:
   *          mean ecliptic longitude of sun at epoch TU (varep)
   *          elciptic longitude of perigee at epoch TU (varpi)
   *          eccentricity of orbit at epoch TU (eccen)
   *
   *   The TU here is the number of Julian centuries since
   *   1900 January 0.0 (= 2415020.0)
   */
  TDT = UT + 59.0/3600.0;
  TU = (jd(year, month, day, TDT) - 2415020.0)/36525.0;
  varep = (279.6966778 + 36000.76892*TU + 0.0003025*TU*TU)*RadPerDeg;
  varpi = (281.2208444 + 1.719175*TU + 0.000452778*TU*TU)*RadPerDeg;
  eccen = 0.01675104 - 0.0000418*TU - 0.000000126*TU*TU;
  c->eccentricity = eccen;



  /*
   * Compute the Obliquity of the Ecliptic at epoch TU
   * The TU in this formula is the number of Julian
   * centuries since epoch 2000 January 1.5
   */
  TU  = (jd(year, month, day, TDT) - jd(2000, 1, 1, 12.0))/36525.0;
  epsilon = (23.43929167 - 0.013004166*TU - 1.6666667e-7*TU*TU
              - 5.0277777778e-7*TU*TU*TU)*RadPerDeg;
  c->epsilon = epsilon;


  /*
   * Compute:
   *          Number of Days since epoch 1990.0 (days)
   *          The Mean Anomaly (M)
   *          The True Anomaly (nu)
   *      The Eccentric Anomaly via Keplers equation (E)
   *
   *
   */
  days  = jd(year, month, day, TDT) - jd(year, month, day, TDT);
  M = angle2pi(2.0*M_PI/365.242191*days + varep - varpi);
  E = kepler(M, eccen);
  nu = 2.0*atan( sqrt((1.0+eccen)/(1.0-eccen))*tan(E/2.0) );
  lambnew = angle2pi(nu + varpi);
  c->lambda_sun = lambnew;


  /*
   *  Compute distance from earth to the sun
   */
  r0 = 1.495985e8;  /* in km */
  earth_sun_distance  = r0*(1-eccen*eccen)/(1.0 + eccen*cos(nu))/6371.2;
  c->earth_sun_dist = earth_sun_distance;





  /*
   * Compute Right Ascension and Declination of the Sun
   */
  RA = angle360(atan2(sin(lambnew)*cos(epsilon), cos(lambnew))*180.0/M_PI);
  DEC = asin(sin(epsilon)*sin(lambnew))*180.0/M_PI;
  c->RA_sun = RA;
  c->DEC_sun = DEC;






  /*
   * Compute Moon Phase and AGE Stuff. The AGE that comes out of Moon()
   * is actually the Phase converted to days. Since AGE is actually defined
   * to be time since last NewMoon, we need to figure out what the JD of the
   * last new moon was. Thats done below....
   */
  TU = (jd(year, month, day, TDT) - 2451545.0)/36525.0;
  c->MoonPhase = Moon(TU, &LambdaMoon, &BetaMoon, &R, &AGE);
  LambdaMoon *= RadPerDeg;
  BetaMoon *= RadPerDeg;


  RA_Moon  = angle360(atan2(sin(LambdaMoon)*cos(epsilon)-tan(BetaMoon)*sin(epsilon), cos(LambdaMoon))*DegPerRad);
  DEC_Moon = asin( sin(BetaMoon)*cos(epsilon) + cos(BetaMoon)*sin(epsilon)*sin(LambdaMoon))*DegPerRad;
  c->RA_moon = RA_Moon;
  c->DEC_moon = DEC_Moon;


  /*
   *  Compute Alt/Az coords
   */
  Tau = (15.0*lmst - RA_Moon)*RadPerDeg;
  CosGlat = cos(c->Glat*RadPerDeg); SinGlat = sin(c->Glat*RadPerDeg);
  /* CosGlon = cos(c->Glon*RadPerDeg); SinGlon = sin(c->Glon*RadPerDeg);*/
  CosTau = cos(Tau); SinTau = sin(Tau);
  SinDec = sin(DEC_Moon*RadPerDeg); CosDec = cos(DEC_Moon*RadPerDeg);
  x = CosDec*CosTau*SinGlat - SinDec*CosGlat;
  y = CosDec*SinTau;
  z = CosDec*CosTau*CosGlat + SinDec*SinGlat;
  c->A_moon = DegPerRad*atan2(y, x);
  c->h_moon = DegPerRad*asin(z);
  c->Visible = (c->h_moon < 0.0) ? 0 : 1;



  /*
   * Compute accurate AGE of the Moon
   */
  Tb = TU - AGE/36525.0; /* should be very close to minimum */
  Ta = Tb - 0.4/36525.0;
  Tc = Tb + 0.4/36525.0;
  c->MoonAge = (TU - NewMoon(Ta, Tb, Tc))*36525.0;



  /*
   * Compute Earth-Moon distance
   */
  c->EarthMoonDistance = R;



}





double kepler(double M,double e)
{
  int n=0;
  double E, Eold, eps = 1.0e-8;



  E = M + e*sin(M);
  do{
    Eold = E;
    E = Eold + (M-Eold+e*sin(Eold))
            /(1.0-e*cos(Eold));
    ++n;
  }while((fabs(E-Eold) > eps) && (n < 100));
  return(E);
}




int DayofYear(int year,int month,int day)
/*int year, month, day;*/
{
  /*double jd();*/
  return((int)(jd(year, month, day, 0.0) - jd(year, 1, 0, 0.0)));
}




int DayofWeek(int year,int month,int day,char dowstr[])
/*int year, month, day;*/
/*char dowstr[];*/
{
  double JD, A, Afrac/*, jd()*/;
  int n, iA;

  JD = jd(year, month, day, 0.0);
  A = (JD + 1.5)/7.0;
  iA = (int)A;
  Afrac = A - (double)iA;
  n = (int)(Afrac*7.0 + 0.5);
  switch(n){
    case 0:
      strcpy(dowstr, "Sunday");
      break;
    case 1:
      strcpy(dowstr, "Monday");
      break;
    case 2:
      strcpy(dowstr, "Tuesday");
      break;
    case 3:
      strcpy(dowstr, "Wednesday");
      break;
    case 4:
      strcpy(dowstr, "Thursday");
      break;
    case 5:
      strcpy(dowstr, "Friday");
      break;
    case 6:
      strcpy(dowstr, "Saturday");
      break;
  }
  return(n);
}





/*
 *  Compute the Julian Day number for the given date.
 *  Julian Date is the number of days since noon of Jan 1 4713 B.C.
 */
double jd(int ny,int nm,int nd,double UT)
/*int ny, nm, nd;*/
/*double UT;*/
{
  double A, B, C, D, JD, day;

  day = nd + UT/24.0;


  if ((nm == 1) || (nm == 2)){
    ny = ny - 1;
    nm = nm + 12;
  }

  if (((double)ny+nm/12.0+day/365.25)>=(1582.0+10.0/12.0+15.0/365.25)){
    A = ((int)(ny / 100.0));
    B = 2.0 - A + (int)(A/4.0);
  }
  else{
    B = 0.0;
  }

  if (ny < 0.0){
    C = (int)((365.25*(double)ny) - 0.75);
  }
  else{
    C = (int)(365.25*(double)ny);
  }

  D = (int)(30.6001*(double)(nm+1));


  JD = B + C + D + day + 1720994.5;
  return(JD);

}

double hour24(double hour)
/*double hour;*/
{
  int n;

  if (hour < 0.0){
    n = (int)(hour/24.0) - 1;
    return(hour-n*24.0);
  }
  else if (hour > 24.0){
    n = (int)(hour/24.0);
    return(hour-n*24.0);
  }
  else{
    return(hour);
  }
}

double angle2pi(double angle)
/*double angle;*/
{
  int n;
  double a;
  a = 2.0*M_PI;

  if (angle < 0.0){
    n = (int)(angle/a) - 1;
    return(angle-n*a);
  }
  else if (angle > a){
    n = (int)(angle/a);
    return(angle-n*a);
  }
  else{
    return(angle);
  }
}

double angle360(double angle)
/*double angle;*/
{
  int n;

  if (angle < 0.0){
    n = (int)(angle/360.0) - 1;
    return(angle-n*360.0);
  }
  else if (angle > 360.0){
    n = (int)(angle/360.0);
    return(angle-n*360.0);
  }
  else{
    return(angle);
  }
}

#if 0
void Radec_to_Cart(double ra,double dec,Vector *r)
/*double  ra, dec;*/  /* RA and DEC */
/*Vector *r;*/    /* returns corresponding cartesian unit vector */
{

  /*
   *  Convert ra/dec from degrees to radians
   */
  ra  *= RadPerDeg;
  dec *= RadPerDeg;


  /*
   *  Compute cartesian coordinates (in GEI)
   */
  r->x = cos(dec) * cos(ra);
  r->y = cos(dec) * sin(ra);
  r->z = sin(dec);

}





int LeapYear(int year)
/*int year;*/
{
  if ((year%100 == 0)&&(year%400 != 0)) return(0);
  else if (year%4 == 0) return(1);
  else return(0);
}
#endif

