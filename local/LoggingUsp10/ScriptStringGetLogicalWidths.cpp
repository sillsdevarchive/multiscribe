#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringGetLogicalWidths=_usp10.ScriptStringGetLogicalWidths")

/////   ScriptStringGetLogicalWidths
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGGETLOGICALWIDTHS)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	int                                     *piDx);



#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringGetLogicalWidths(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	int                                     *piDx)
{
	WRAP_BEGIN(ScriptStringGetLogicalWidths, LPFNSCRIPTSTRINGGETLOGICALWIDTHS)
	LOG(L"<ScriptStringGetLogicalWidths>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	hResult = ScriptStringGetLogicalWidths(ssa, piDx);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptStringGetLogicalWidths>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
