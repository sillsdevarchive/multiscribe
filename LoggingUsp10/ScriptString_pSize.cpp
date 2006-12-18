#include "stdafx.h"

/////   ScriptStringSize
typedef const SIZE* (CALLBACK* LPFNSCRIPTSTRING_PSIZE) (
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);

#ifdef __cplusplus
extern "C" {
#endif

const SIZE* WINAPI LoggingScriptString_pSize(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
{
	WRAP_BEGIN_RETURNING(ScriptString_pSize, LPFNSCRIPTSTRING_PSIZE, const SIZE*, result, NULL)
	LOG(L"<ScriptString_pSize>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	result = ScriptString_pSize(ssa);
	LOG(L"<out>");
	LOG(L"<size>%d</size", *result);
	LOG(L"</out>");
	LOG(L"</ScriptString_pSize>");
	WRAP_END_RETURNING(result, NULL)
}
#ifdef __cplusplus
}
#endif
