#include "../stdafx.h"

//#include "../GraphiteScriptStringAnalysis.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptStringValidate=" USP10DLL ".ScriptStringValidate")
#endif

/////   ScriptStringValidate
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGVALIDATE)(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringValidate(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//	if(pgssa){
//	}
//	else{
//	}
//	WRAP_BEGIN(ScriptStringValidate, LPFNSCRIPTSTRINGVALIDATE)
//	hResult = ScriptStringValidate(ssa);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
