#include "../stdafx.h"

#ifdef IMPERSONATE_USP10

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTPROPERTIES)(
	HDC                                     hdc,    // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,   // InOut Address of Cache handle
	__out_ecount(1) SCRIPT_FONTPROPERTIES   *sfp);  // Out   Receives properties for this font


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetFontProperties(
	HDC                                     hdc,    // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,   // InOut Address of Cache handle
	__out_ecount(1) SCRIPT_FONTPROPERTIES   *sfp)   // Out   Receives properties for this font
{
	WRAP_BEGIN(ScriptGetFontProperties, LPFNSCRIPTGETFONTPROPERTIES)
	hResult = ScriptGetFontProperties(hdc,psc,sfp);
	WRAP_END
}

#ifdef __cplusplus
}
#endif

#endif //IMPERSONATE_USP10

