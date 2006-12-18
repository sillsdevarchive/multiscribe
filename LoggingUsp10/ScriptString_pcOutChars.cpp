#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptString_pcOutChars=_usp10.ScriptString_pcOutChars")

/////   ScriptString_pcOutChars
typedef const int* (CALLBACK* LPFNSCRIPTSTRING_PCOUTCHARS)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);

#ifdef __cplusplus
extern "C" {
#endif

const int* WINAPI LoggingScriptString_pcOutChars(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
{
	WRAP_BEGIN_RETURNING(ScriptString_pcOutChars, LPFNSCRIPTSTRING_PCOUTCHARS, const int*, result, NULL)
	LOG(L"<ScriptString_pcOutChars>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	result = ScriptString_pcOutChars(ssa);
	LOG(L"<out>");
	LOG(L"<StringAfterClipping length='%d'/>", *result);
	LOG(L"</out>");
	LOG(L"</ScriptString_pcOutChars>");
	WRAP_END_RETURNING(result, NULL)
}
#ifdef __cplusplus
}
#endif
