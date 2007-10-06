#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetFontProperties=_usp10.ScriptGetFontProperties")

/////   ScriptGetFontProperties


typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTPROPERTIES)(
	HDC                                     hdc,    // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,   // InOut Address of Cache handle
	__out_ecount(1) SCRIPT_FONTPROPERTIES   *sfp);  // Out   Receives properties for this font


#ifdef __cplusplus
extern "C" {
#endif


__checkReturn HRESULT WINAPI LoggingScriptGetFontProperties(
	HDC                                     hdc,    // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,   // InOut Address of Cache handle
	__out_ecount(1) SCRIPT_FONTPROPERTIES   *sfp)  // Out   Receives properties for this font
{
	WRAP_BEGIN(ScriptGetFontProperties, LPFNSCRIPTGETFONTPROPERTIES)
	LOG(L"<ScriptGetFontProperties>");
	LOG(L"<in>");
  LogHdc(hdc);
	LOG(L"</in>");
	hResult = ScriptGetFontProperties(hdc,psc,sfp);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetFontProperties>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
