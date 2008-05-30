#include "../stdafx.h"

#ifdef IMPERSONATE_USP10
///////   ScriptGetCMap

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETCMAP)(
	HDC                                     hdc,            // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut Address of Cache handle
	__in_ecount(cChars) const WCHAR         *pwcInChars,    // In    Unicode codepoint(s) to look up
	int                                     cChars,         // In    Number of characters
	DWORD                                   dwFlags,        // In    Flags such as SGCM_RTL
	__out_ecount(cChars) WORD               *pwOutGlyphs);  // Out   Array of glyphs, one per input character

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetCMap(
	HDC                                     hdc,            // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut Address of Cache handle
	__in_ecount(cChars) const WCHAR         *pwcInChars,    // In    Unicode codepoint(s) to look up
	int                                     cChars,         // In    Number of characters
	DWORD                                   dwFlags,        // In    Flags such as SGCM_RTL
	__out_ecount(cChars) WORD               *pwOutGlyphs)  // Out   Array of glyphs, one per input character
{
	WRAP_BEGIN(RealScriptGetCMap, LPFNSCRIPTGETCMAP)
	hResult = RealScriptGetCMap(hdc,psc,pwcInChars,cChars,dwFlags,pwOutGlyphs);
	WRAP_END
}
#ifdef __cplusplus
}
#endif
#endif //IMPERSONATE_USP10
