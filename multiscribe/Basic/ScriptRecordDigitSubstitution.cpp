#include "../stdafx.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptRecordDigitSubstitution=" USP10DLL ".ScriptRecordDigitSubstitution")
#endif

/////   ScriptRecordDigitSubstitution
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTRECORDDIGITSUBSTITUTION)(
//    LCID                                    Locale,     // In   LOCALE_USER_DEFAULT or desired locale
//    __out_ecount(1) SCRIPT_DIGITSUBSTITUTE  *psds);     // Out  Digit substitution settings
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptRecordDigitSubstitution(
//    LCID                                    Locale,     // In   LOCALE_USER_DEFAULT or desired locale
//    __out_ecount(1) SCRIPT_DIGITSUBSTITUTE  *psds)     // Out  Digit substitution settings
//{
//	WRAP_BEGIN(ScriptRecordDigitSubstitution, LPFNSCRIPTRECORDDIGITSUBSTITUTION)
//	hResult = ScriptRecordDigitSubstitution(Locale, psds);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
