/*
 * MATLAB Compiler: 4.14 (R2010b)
 * Date: Fri May 13 11:15:11 2016
 * Arguments: "-B" "macro_default" "-t" "-W"
 * "libhg:projectedCPR_display_testdll" "-T" "link:lib" "-h" "libmmfile.mlib"
 * "projectedCPR_display_test.m" 
 */

#ifndef __projectedCPR_display_testdll_h
#define __projectedCPR_display_testdll_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_projectedCPR_display_testdll
#define PUBLIC_projectedCPR_display_testdll_C_API __global
#else
#define PUBLIC_projectedCPR_display_testdll_C_API /* No import statement needed. */
#endif

#define LIB_projectedCPR_display_testdll_C_API PUBLIC_projectedCPR_display_testdll_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_projectedCPR_display_testdll
#define PUBLIC_projectedCPR_display_testdll_C_API __declspec(dllexport)
#else
#define PUBLIC_projectedCPR_display_testdll_C_API __declspec(dllimport)
#endif

#define LIB_projectedCPR_display_testdll_C_API PUBLIC_projectedCPR_display_testdll_C_API


#else

#define LIB_projectedCPR_display_testdll_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_projectedCPR_display_testdll_C_API 
#define LIB_projectedCPR_display_testdll_C_API /* No special import/export declaration */
#endif

extern LIB_projectedCPR_display_testdll_C_API 
bool MW_CALL_CONV projectedCPR_display_testdllInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_projectedCPR_display_testdll_C_API 
bool MW_CALL_CONV projectedCPR_display_testdllInitialize(void);

extern LIB_projectedCPR_display_testdll_C_API 
void MW_CALL_CONV projectedCPR_display_testdllTerminate(void);



extern LIB_projectedCPR_display_testdll_C_API 
void MW_CALL_CONV projectedCPR_display_testdllPrintStackTrace(void);

extern LIB_projectedCPR_display_testdll_C_API 
bool MW_CALL_CONV mlxProjectedCPR_display_test(int nlhs, mxArray *plhs[], int nrhs, 
                                               mxArray *prhs[]);

extern LIB_projectedCPR_display_testdll_C_API 
long MW_CALL_CONV projectedCPR_display_testdllGetMcrID();



extern LIB_projectedCPR_display_testdll_C_API bool MW_CALL_CONV mlfProjectedCPR_display_test(mxArray* Volume00, mxArray* reference00);

#ifdef __cplusplus
}
#endif
#endif
