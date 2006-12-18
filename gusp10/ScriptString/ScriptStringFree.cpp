#include "../stdafx.h"
#include "../GraphiteScriptStringAnalysis.h"
//#pragma comment(linker, "/export:ScriptStringFree=_usp10.ScriptStringFree")

/////   ScriptStringFree - free a string analysis
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGFREE)(
	__deref_inout_ecount(1) SCRIPT_STRING_ANALYSIS  *pssa);  //InOut Address of pointer to analysis

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringFree(
	__deref_inout_ecount(1) SCRIPT_STRING_ANALYSIS  *pssa)  //InOut Address of pointer to analysis
{
	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(*pssa);

	if(pgssa){
		delete pgssa->pTextSource;
		FreeGraphiteScriptStringAnalysis(*pssa);
	}
	else{
	}

	WRAP_BEGIN(ScriptStringFree, LPFNSCRIPTSTRINGFREE)
	hResult = ScriptStringFree(pssa);
	WRAP_END
}
#ifdef __cplusplus
}
#endif