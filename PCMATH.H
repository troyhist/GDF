// =======================================================================
// PC some mathematics function library ver. 1.0 (C, CPP)
// Troy computing, Inc.
// Copyright (c) 1994-2000
// -----------------------------------------------------------------------
// Some fast mathematics function.
// Used library: unitypes.h
// -----------------------------------------------------------------------
// File: pcmath.h
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: DOS16 console, Win32 GUI
// -----------------------------------------------------------------------
// Made date: 24/ IX.2000
// Last edit: 24/ IX.2000
//     Build: 1
// =======================================================================
#include "unitypes.h"
// =======================================================================
#ifndef _PCMATHH_
#define _PCMATHH_
// =======================================================================
// Structures ... PCMATH
// =======================================================================
// Fractional number 32 bit
// =======================================================================
typedef struct	{
	int16 i;	// Integer part
	int16 f;	// Fractional part
	} fix32;
// =======================================================================
// Function & Procedures ... PCMATH
// =======================================================================
#define rad2deg(_r_)    ((float)(180*(_r_))/M_PI)
#define deg2rad(_d_)    ((float)(M_PI*(_d_))/180)
// -----------------------------------------------------------------------
fix32 _pcfloat2fix(float f);
float _pcfix2float(fix32 f);
// =======================================================================
float _pc_reduce_angle(float a);
// =======================================================================
#define _pccos_rad(_ar_)	_pccos_deg(rad2deg(_ar_))
#define _pcsin_rad(_ar_)	_pcsin_deg(rad2deg(_ar_))
#define _pccosf_rad(_ar_)	_pccosf_deg(rad2deg(_ar_))
#define _pcsinf_rad(_ar_)	_pcsinf_deg(rad2deg(_ar_))
// -----------------------------------------------------------------------
float _pcsin_deg(float angle_deg);
float _pccos_deg(float angle_deg);
fix32 _pcsinf_deg(float angle_deg);
fix32 _pccosf_deg(float angle_deg);
// =======================================================================
#endif
// =======================================================================
