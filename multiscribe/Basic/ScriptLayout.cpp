#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptLayout=" USP10DLL ".ScriptLayout")
#endif
/////   ScriptLayout
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTLAYOUT) (
//    int                             cRuns,                  // In   Number of runs to process
//    __in_ecount(cRuns) const BYTE   *pbLevel,               // In   Array of run embedding levels
//    __out_ecount_full_opt(cRuns) int    *piVisualToLogical,     // Out  List of run indices in visual order
//    __out_ecount_full_opt(cRuns) int    *piLogicalToVisual);    // Out  List of visual run positions
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptLayout(
//    int                             cRuns,                  // In   Number of runs to process
//    __in_ecount(cRuns) const BYTE   *pbLevel,               // In   Array of run embedding levels
//    __out_ecount_full_opt(cRuns) int    *piVisualToLogical,     // Out  List of run indices in visual order
//    __out_ecount_full_opt(cRuns) int    *piLogicalToVisual)    // Out  List of visual run positions
//{
//	WRAP_BEGIN(ScriptLayout, LPFNSCRIPTLAYOUT)
//	hResult = ScriptLayout(cRuns, pbLevel, piVisualToLogical, piLogicalToVisual);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
