#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringFree=_usp10.ScriptStringFree")

/////   ScriptStringFree - free a string analysis
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGFREE)(
	__deref_inout_ecount(1) SCRIPT_STRING_ANALYSIS  *pssa);  //InOut Address of pointer to analysis

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringFree(
	__deref_inout_ecount(1) SCRIPT_STRING_ANALYSIS  *pssa)  //InOut Address of pointer to analysis
{
	WRAP_BEGIN(ScriptStringFree, LPFNSCRIPTSTRINGFREE)
	LOG(L"<ScriptStringFree>");
	LOG(L"<in>");
	LogScriptStringAnalysis(*pssa);
	LOG(L"</in>");
	hResult = ScriptStringFree(pssa);
	LOG(L"</ScriptStringFree>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
