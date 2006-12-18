#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptIsComplex=_usp10.ScriptIsComplex")

///////////////////////////////////////////////////////////////////////////////////////////////////
///// ScriptIsComplex
//#pragma comment(linker, "/export:ScriptIsComplex=_usp10.ScriptIsComplex")
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTISCOMPLEX)(
	__in_ecount(cInChars) const WCHAR   *pwcInChars,    //In  String to be tested
	int                                 cInChars,       //In  Length in characters
	DWORD                               dwFlags);       //In  Flags (see above)

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptIsComplex(
	__in_ecount(cInChars) const WCHAR   *pwcInChars,    //In  String to be tested
	int                                 cInChars,       //In  Length in characters
	DWORD                               dwFlags)       //In  Flags (see above)
{
	WRAP_BEGIN(ScriptIsComplex, LPFNSCRIPTISCOMPLEX)
	LOG(L"<ScriptIsComplex>");
	LOG(L"<in>");
	LogString(pwcInChars, cInChars);
	LOG(L"</in>");
	hResult = ScriptIsComplex(pwcInChars, cInChars, dwFlags);
	LOG(L"<out>");
	switch(hResult){
		case S_OK:
			LOG(L"<Complex/>");
			hResult = S_FALSE;
			break;
		case S_FALSE:
			LOG(L"<NotComplex/>");
			break;
		default:
			LogHResult(hResult);
	}
	LOG(L"</out>");
	LOG(L"</ScriptIsComplex>");
	WRAP_END
}

#ifdef __cplusplus
}
#endif
