#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptBreak=" USP10DLL ".ScriptBreak")
#endif

///////   ScriptBreak
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTBREAK)(
//    __in_ecount(cChars) const WCHAR             *pwcChars,  // In   Logical unicode item
//    int                                         cChars,     // In   Length of unicode item
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,       // In   Result of earlier ScriptItemize call
//    __out_ecount_full(cChars) SCRIPT_LOGATTR    *psla);     // Out  Logical character attributes
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptBreak(
//    __in_ecount(cChars) const WCHAR             *pwcChars,  // In   Logical unicode item
//    int                                         cChars,     // In   Length of unicode item
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,       // In   Result of earlier ScriptItemize call
//    __out_ecount_full(cChars) SCRIPT_LOGATTR    *psla)     // Out  Logical character attributes
//{
//
//	WRAP_BEGIN(ScriptBreak, LPFNSCRIPTBREAK)
//	hResult = ScriptBreak(pwcChars,cChars,psa,psla);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
