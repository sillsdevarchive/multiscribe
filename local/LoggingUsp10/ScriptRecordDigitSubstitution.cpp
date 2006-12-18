#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptRecordDigitSubstitution=_usp10.ScriptRecordDigitSubstitution")

/////   ScriptRecordDigitSubstitution
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTRECORDDIGITSUBSTITUTION)(
	LCID                                    Locale,     // In   LOCALE_USER_DEFAULT or desired locale
	__out_ecount(1) SCRIPT_DIGITSUBSTITUTE  *psds);     // Out  Digit substitution settings

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptRecordDigitSubstitution(
	LCID                                    Locale,     // In   LOCALE_USER_DEFAULT or desired locale
	__out_ecount(1) SCRIPT_DIGITSUBSTITUTE  *psds)     // Out  Digit substitution settings
{
	WRAP_BEGIN(ScriptRecordDigitSubstitution, LPFNSCRIPTRECORDDIGITSUBSTITUTION)
	LOG(L"<ScriptRecordDigitSubstitution>");
	LOG(L"<in>");
	LOG(L"<LCID>%d</LCID>", Locale);
	LOG(L"</in>");
	hResult = ScriptRecordDigitSubstitution(Locale, psds);
	LOG(L"<out>");
	LogDigitSubstitution(psds);
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptRecordDigitSubstitution>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
