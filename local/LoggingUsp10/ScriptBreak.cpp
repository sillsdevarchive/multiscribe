#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptBreak=_usp10.ScriptBreak")
/////   ScriptBreak


typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTBREAK)(
	__in_ecount(cChars) const WCHAR             *pwcChars,  // In   Logical unicode item
	int                                         cChars,     // In   Length of unicode item
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,       // In   Result of earlier ScriptItemize call
	__out_ecount_full(cChars) SCRIPT_LOGATTR    *psla);     // Out  Logical character attributes


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptBreak(
	__in_ecount(cChars) const WCHAR             *pwcChars,  // In   Logical unicode item
	int                                         cChars,     // In   Length of unicode item
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,       // In   Result of earlier ScriptItemize call
	__out_ecount_full(cChars) SCRIPT_LOGATTR    *psla)     // Out  Logical character attributes
{
	WRAP_BEGIN(ScriptBreak, LPFNSCRIPTBREAK)
	LOG(L"<ScriptBreak>");
	LOG(L"<in>");
	LogString(pwcChars, cChars);
	LogScriptAnalysis(psa);
	LOG(L"</in>");
	hResult = ScriptBreak(pwcChars,cChars,psa,psla);
	LOG(L"<out>");
	LOG(L"<LogicalCharacterAttributes>");
	for(int i=0; i<cChars; ++i){
		LogScriptLogAttr(psla);
	}
	LOG(L"</LogicalCharacterAttributes>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptBreak>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
