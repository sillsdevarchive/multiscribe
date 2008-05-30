#include "../stdafx.h"
//#include "../GraphiteScriptStringAnalysis.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptString_pLogAttr=" USP10DLL ".ScriptString_pLogAttr")
#endif

/////   ScriptString_pLogAttr
//
//typedef const SCRIPT_LOGATTR* (CALLBACK* LPFNSCRIPTSTRING_PLOGATTR) (
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//const SCRIPT_LOGATTR* WINAPI GraphiteEnabledScriptString_pLogAttr(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//
//	if(pgssa){
//	}
//	else{
//	}
//
//	WRAP_BEGIN_RETURNING(ScriptString_pLogAttr, LPFNSCRIPTSTRING_PLOGATTR, const SCRIPT_LOGATTR*, result, NULL)
//	result = ScriptString_pLogAttr(ssa);
//	WRAP_END_RETURNING(result, NULL)
//}
//#ifdef __cplusplus
//}
//#endif
