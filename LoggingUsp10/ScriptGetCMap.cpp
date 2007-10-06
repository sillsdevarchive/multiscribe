#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetCMap=_usp10.ScriptGetCMap")

/////   ScriptGetCMap

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

__checkReturn HRESULT WINAPI LoggingScriptGetCMap(
	HDC                                     hdc,            // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut Address of Cache handle
	__in_ecount(cChars) const WCHAR         *pwcInChars,    // In    Unicode codepoint(s) to look up
	int                                     cChars,         // In    Number of characters
	DWORD                                   dwFlags,        // In    Flags such as SGCM_RTL
	__out_ecount(cChars) WORD               *pwOutGlyphs)  // Out   Array of glyphs, one per input character
{
	WRAP_BEGIN(ScriptGetCMap, LPFNSCRIPTGETCMAP)
	LOG(L"<ScriptGetCMap>");
	LOG(L"<in>");
  LogHdc(hdc);
	LogScriptCache(psc);
	LogString(pwcInChars, cChars);
	if(dwFlags & SGCM_RTL){
		LOG(L"<UseMirroredGlyphs/>");
	}
	LOG(L"</in>");
	hResult = ScriptGetCMap(hdc,psc,pwcInChars,cChars,dwFlags,pwOutGlyphs);
	LOG(L"<out>");
	LOG(L"<Glyphs count='%d'>", cChars);
	for(int i=0; i<cChars; ++i){
		LOG(L"<Glyph hex='%04x'/>", pwOutGlyphs[i]);
	}
	LOG(L"</Glyphs>");

	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetCMap>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
