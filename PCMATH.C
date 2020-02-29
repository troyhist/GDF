// =======================================================================
// PC some mathematics function library ver. 1.0 (C, CPP)
// Troy computing, Inc.
// Copyright (c) 1994-2000
// -----------------------------------------------------------------------
// Some fast mathematics function.
// Used library: unitypes.h
// -----------------------------------------------------------------------
// File: pcmath.c
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: DOS16 console, Win32 GUI
// -----------------------------------------------------------------------
// Made date: 24/ IX.2000
// Last edit: 24/ IX.2000
//     Build: 1
// =======================================================================
// Precompile definition ... PCMATH
// =======================================================================
#define _PCMATH_USES_MATH       // Uses standart <math.h>
#define _PCMATH_GEN_SINTAB      // Generates sinus & cosinus tables
#define _PCMATH_USE_SINTAB      // Use internal sinus & cosinus tables
// =======================================================================
#ifdef _PCMATH_GEN_SINTAB
#define _PCMATH_USES_MATH
#endif
// =======================================================================
// Includes
// =======================================================================
#ifdef _PCMATH_USES_MATH
#include <math.h>
#else
// -----------------------------------------------------------------------
/* Constants rounded for 21 decimals. */
#define M_E         2.71828182845904523536
#define M_LOG2E     1.44269504088896340736
#define M_LOG10E    0.434294481903251827651
#define M_LN2       0.693147180559945309417
#define M_LN10      2.30258509299404568402
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.785398163397448309616
#define M_1_PI      0.318309886183790671538
#define M_2_PI      0.636619772367581343076
#define M_1_SQRTPI  0.564189583547756286948
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT_2    0.707106781186547524401
#endif
// -----------------------------------------------------------------------
#include "memc.h"
#include "pcmath.h"
// =======================================================================
#ifdef _PCMATH_GEN_SINTAB
//float _pc_sintab[91][100];	// float sinus table
float **_pc_sintab;		// float sinus table
int16 _pc_sintabgen=0;		// generated table flag
#endif
// =======================================================================
// Function & Procedures ... PCMATH
// =======================================================================
fix32 _pcfloat2fix(float f)
{
// -----------------------------------------------------------------------
// Description: Converts 'float' digit to 'fix32' digit
//   Parametrs: f	- 'float' digit
//      Return: 'fix32' digit
// -----------------------------------------------------------------------
fix32 res;
res.i=f;
res.f=((f-res.i)*100);
return(res);
}
// =======================================================================
float _pcfix2float(fix32 f)
{
// -----------------------------------------------------------------------
// Description: Converts 'fix32' digit to 'float' digit
//   Parametrs: f	- 'fix32' digit
//      Return: 'float' digit
// -----------------------------------------------------------------------
float res;
res=f.i+(float)f.f/100.;
return(res);
}
// =======================================================================
#ifdef _PCMATH_GEN_SINTAB
void _pc_gen_sintab(void)
{
// -----------------------------------------------------------------------
// Description: Generates sinus table
//   Parametrs: <none>
//      Return: <none>
// -----------------------------------------------------------------------
int16 i, j;
//*
_pc_sintab=newm(float*, 90);
for (i=0; i<90; i++)
	_pc_sintab[i]=newm(float, 100);//*/
for (i=0; i<91; i++)
	for (j=0; j<100; j++)
		_pc_sintab[i][j]=sin(deg2rad((float)i+(float)j/100.));
_pc_sintabgen=1;
}
#endif
// =======================================================================
float _pc_reduce_angle(float a)
{
// -----------------------------------------------------------------------
// Description: Reduces angle
//   Parametrs: a	- angle in degrees
//      Return: reduced angle in range [0; 360]
// -----------------------------------------------------------------------
/*int16 sign=1;		// signum of 'a'
int16 n=0;		// quantity of rotations
// -----------------------------------------------------------------------
if (a<0) { a=-a; sign=-1; }
if (a >= 360) n=a/360;
a=a-360*n;
a=a*sign;*/
a=a-360*((int16)(a/360));
return(a);
}
// =======================================================================
float _pcsin_deg(float angle_deg)
{
// -----------------------------------------------------------------------
// Description: Calculates sinus of given digit
//   Parametrs: angle_deg	- angle in degrees
//      Return: float sinus
// -----------------------------------------------------------------------
int16 k=1;		// flag of coinsidence
int16 sign=1;		// signum of 'angle_deg'
float resf;		// float result
fix32 a;		// angle
// -----------------------------------------------------------------------
#ifdef _PCMATH_GEN_SINTAB
if (!_pc_sintabgen) _pc_gen_sintab();
#endif
// -----------------------------------------------------------------------
angle_deg=_pc_reduce_angle(angle_deg);
// -----------------------------------------------------------------------
if (angle_deg < 0.) { angle_deg=-angle_deg; sign=-1; }
if (angle_deg >= 180.) { angle_deg-=180; k=-1; }
if (angle_deg >= 90.) { angle_deg=180-angle_deg; }
// -----------------------------------------------------------------------
a=_pcfloat2fix(angle_deg);
// -----------------------------------------------------------------------
resf=_pc_sintab[a.i][a.f];
// -----------------------------------------------------------------------
resf*=(float)(k*sign);
// -----------------------------------------------------------------------
return(resf);
}
// =======================================================================
fix32 _pcsinf_deg(float angle_deg)
{
// -----------------------------------------------------------------------
// Description: Calculates sinus of given digit
//   Parametrs: angle_deg	- angle in degrees
//      Return: fixed sinus
// -----------------------------------------------------------------------
int16 k=1;		// flag of coinsidence
int16 sign=1;		// signum of 'angle_deg'
float resf;		// float result
fix32 a;		// angle
// -----------------------------------------------------------------------
#ifdef _PCMATH_GEN_SINTAB
if (!_pc_sintabgen) _pc_gen_sintab();
#endif
// -----------------------------------------------------------------------
angle_deg=_pc_reduce_angle(angle_deg);
// -----------------------------------------------------------------------
if (angle_deg < 0.) { angle_deg=-angle_deg; sign=-1; }
if (angle_deg >= 180.) { angle_deg-=180; k=-1; }
if (angle_deg >= 90.) { angle_deg=180-angle_deg; }
// -----------------------------------------------------------------------
a=_pcfloat2fix(angle_deg);
// -----------------------------------------------------------------------
resf=_pc_sintab[a.i][a.f];
// -----------------------------------------------------------------------
resf*=(float)(k*sign);
// -----------------------------------------------------------------------
return(_pcfloat2fix(resf));
}
// =======================================================================
float _pccos_deg(float angle_deg)
{
// -----------------------------------------------------------------------
// Description: Calculates cosinus of given digit
//   Parametrs: angle_deg	- angle in degrees
//      Return: float cosinus
// -----------------------------------------------------------------------
return(_pcsin_deg(angle_deg+90));
}
// =======================================================================
fix32 _pccosf_deg(float angle_deg)
{
// -----------------------------------------------------------------------
// Description: Calculates cosinus of given digit
//   Parametrs: angle_deg	- angle in degrees
//      Return: fixed cosinus
// -----------------------------------------------------------------------
return(_pcsinf_deg(angle_deg+90));
}
// =======================================================================
