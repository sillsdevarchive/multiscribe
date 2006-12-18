#include "stdafx.h"

/////   ScriptStringValidate
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGVALIDATE)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringValidate(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
{
	WRAP_BEGIN(ScriptStringValidate, LPFNSCRIPTSTRINGVALIDATE)
	LOG(L"<ScriptStringValidate>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"</in>");
	hResult = ScriptStringValidate(ssa);
	LOG(L"<out>");
	switch(hResult){
		case S_OK:
			LOG(L"<valid/>");
			break;
		case S_FALSE:
			LOG(L"<invalid/>");
			break;
		default:
			LogHResult(hResult);
	}
	LOG(L"</out>");
	LOG(L"<ScriptStringValidate>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
