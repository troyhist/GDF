// =======================================================================
// Graphics Drawer Files function library ver. 1.0 (C, CPP)
// Troy computing, Inc.
// Copyright (c) 1994-2000
// -----------------------------------------------------------------------
// GDF Vector graphics support library.
// Used library: unitypes.h, memc.h
// -----------------------------------------------------------------------
// File: pcgdf.h
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1
//  Application: DOS16 console, Win32 GUI
// -----------------------------------------------------------------------
// Made date: 07/ IX.2000
// Last edit: 10/ IX.2000
//     Build: 1
// =======================================================================
#include "unitypes.h"		// int16
// =======================================================================
#ifndef _PCGDGH
#define _PCGDGH
// =======================================================================
// GDF commands
// =======================================================================
#define gdfCC		0
#define gdfPTR		1	// HDF
#define gdfPIX		2
#define gdfLNT		3	// HDF
#define gdfLNR		4	// HDF
#define gdfLN		5
#define gdfLNC		6
#define gdfPOLY		7	// HDF
#define gdfPOLYFL	8	// HDF
#define gdfELL		9	// HDF
#define gdfELLFL	10	// HDF
// -----------------------------------------------------------------------
// Figures
// -----------------------------------------------------------------------
#define gdfRECT		16
#define gdfRECTFL	17
#define gdfTRI		18
#define gdfTRIFL	19
#define gdfCIRC		20
#define gdfCIRCFL	21
#define gdfELLA		22
#define gdfELLAFL	23
// =======================================================================
// Structures ... PCGDF
// =======================================================================
typedef struct
	{
	char initGDF[6];	// "GDF00i"
	int16 pWD, pHG;		// picture width, height
	int16 dirs;		// quantity of directives
	int32 descr;		// ptr to description in file of NULL
	int32 lod;		// length of data in bytes
	} headerGDF;
// =======================================================================
// Functions ... PCGDF
// =======================================================================
void gdf_init(void);
void gdf_test(void);
void gdf_put (int px, int py, int16 angle, float k, int16* obj);
// =======================================================================
#endif
// =======================================================================
