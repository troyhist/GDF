// =======================================================================
// MEMC macros library ver. 2.0 (C, CPP)
// Troy computing, Inc.
// Copyright (c) 1994-'98
// -----------------------------------------------------------------------
// Macros collection for memory operations.
// Used library: <none>
// -----------------------------------------------------------------------
//     Compiler: Borland C++ 3.1 or higher
//  Application: DOS16, Win32 console
// -----------------------------------------------------------------------
// File: MEMC.H
// -----------------------------------------------------------------------
// Made date: 10/ X.1997
// Last edit: 5/XII.1998
//     Build: 2
// =======================================================================
#include <stdlib.h>
// =======================================================================
#define new(a, b)       (a *)malloc(sizeof(a)*(b))
#define newm(a, b)      (a *)malloc(sizeof(a)*(b))
#define delete(a)       free(a)
#define deletem(a)      free(a)
// -----------------------------------------------------------------------
#ifdef __cplusplus
#undef new
#undef delete
#endif
// =======================================================================
// -----------------------------------------------------------------------
// Description: Searches given byte sequences s2 in buffer s1
//   Parametrs: s1, s2  - addresses of buffers
//              l1, l2  - size of buffers in bytes
//      Return: SUCCESS - ptr to finded sequence or NULL
// -----------------------------------------------------------------------
#define _FUNC_MEMMEM    \
void *memmem(void *s1, void *s2, int l1, int l2)\
        {\
        int i;\
        \
        if (l2>l1 || !l1 || !l2 || !s1 || !s2) return (NULL);\
        \
        for (i=0; i<l1; i++)\
                if (!memcmp((char*)s1+i, s2, l2))\
                        return ((char*)s1+i);\
        \
        return (0);\
        }
// =======================================================================

