#include "../stdafx.h"

//#include "../GraphiteScriptStringAnalysis.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptStringGetLogicalWidths=" USP10DLL ".ScriptStringGetLogicalWidths")
#endif

/////   ScriptStringGetLogicalWidths
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGGETLOGICALWIDTHS)(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
//    int                                     *piDx);
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringGetLogicalWidths(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
//    int                                     *piDx)
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//
//	if(pgssa){
//	}
//	else{
//	}
//
//	WRAP_BEGIN(ScriptStringGetLogicalWidths, LPFNSCRIPTSTRINGGETLOGICALWIDTHS)
//	hResult = ScriptStringGetLogicalWidths(ssa, piDx);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
