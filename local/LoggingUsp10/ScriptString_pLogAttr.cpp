#include "stdafx.h"

/////   ScriptString_pLogAttr

typedef const SCRIPT_LOGATTR* (CALLBACK* LPFNSCRIPTSTRING_PLOGATTR) (
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);


#ifdef __cplusplus
extern "C" {
#endif

const SCRIPT_LOGATTR* WINAPI LoggingScriptString_pLogAttr(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
{
	WRAP_BEGIN_RETURNING(ScriptString_pLogAttr, LPFNSCRIPTSTRING_PLOGATTR, const SCRIPT_LOGATTR*, result, NULL)
	LOG(L"<ScriptString_pLogAttr>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	result = ScriptString_pLogAttr(ssa);
	LOG(L"<out>");
	//TODO: all of the length.
	LogScriptLogAttr(result);
	LOG(L"</out>");
	LOG(L"</ScriptString_pLogAttr>");
	WRAP_END_RETURNING(result, NULL)

}
#ifdef __cplusplus
}
#endif
