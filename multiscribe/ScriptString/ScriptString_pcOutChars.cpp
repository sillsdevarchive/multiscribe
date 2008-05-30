#include "../stdafx.h"
//#include "../GraphiteScriptStringAnalysis.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptString_pcOutChars=" USP10DLL ".ScriptString_pcOutChars")
#endif

/////   ScriptString_pcOutChars
//typedef const int* (CALLBACK* LPFNSCRIPTSTRING_PCOUTCHARS)(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//const int* WINAPI GraphiteEnabledScriptString_pcOutChars(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//
//	if(pgssa){
//	}
//	else{
//	}
//	WRAP_BEGIN_RETURNING(ScriptString_pcOutChars, LPFNSCRIPTSTRING_PCOUTCHARS, const int*, result, NULL)
//	result = ScriptString_pcOutChars(ssa);
//	WRAP_END_RETURNING(result, NULL)
//}
//#ifdef __cplusplus
//}
//#endif
