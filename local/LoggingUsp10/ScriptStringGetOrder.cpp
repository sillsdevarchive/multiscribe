#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringGetOrder=_usp10.ScriptStringGetOrder")

/////   ScriptStringGetOrder
// Maps character glyph positions in a similar way to GetCharacterPlacement,
// for legacy use only. Does not work well with scripts that generate more
// than one glyph per codepoint.
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGGETORDER)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	UINT                                    *puOrder);

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringGetOrder(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	UINT                                    *puOrder)
{
	WRAP_BEGIN(ScriptStringGetOrder, LPFNSCRIPTSTRINGGETORDER)
	LOG(L"<ScriptStringGetOrder>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	hResult = ScriptStringGetOrder(ssa, puOrder);
	LOG(L"<out>");
	//TODO: puOrder
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptStringGetOrder>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
