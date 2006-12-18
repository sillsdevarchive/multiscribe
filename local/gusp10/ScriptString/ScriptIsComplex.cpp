#include "../stdafx.h"
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
__checkReturn HRESULT WINAPI GraphiteEnabledScriptIsComplex(
	__in_ecount(cInChars) const WCHAR   *pwcInChars,    //In  String to be tested
	int                                 cInChars,       //In  Length in characters
	DWORD                               dwFlags)       //In  Flags (see above)
{
	WRAP_BEGIN(ScriptIsComplex, LPFNSCRIPTISCOMPLEX)

	hResult = ScriptIsComplex(pwcInChars, cInChars, dwFlags);
	// This is our worst case behavior. Since we don't actually know
	// what font will be used at this point, the best we could do is
	// to see if there are any graphite fonts which contain rules
	// which operate on any of these characters.
	if (hResult == S_FALSE){
		hResult = S_OK; // override so it is complex
	}

	WRAP_END
}
#ifdef __cplusplus
}
#endif
