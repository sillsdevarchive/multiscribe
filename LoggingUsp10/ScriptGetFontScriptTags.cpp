#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetFontScriptTags=_usp10.ScriptGetFontScriptTags")

///// ScriptGetFontScriptList
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTSCRIPTTAGS)(
	__in_opt           HDC                              hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE                    *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS                 *psa,             // In    Result of ScriptItemize (can be NULL)
	__in               int                              cMaxTags,        // In    Length of pScriptTags array
	__out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG  *pScriptTags,     // Out:  list of script tags in the font
	__out              int                             *pcTags);           // Out:  Number of tags returned


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptGetFontScriptTags(
	__in_opt           HDC                              hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE                    *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS                 *psa,             // In    Result of ScriptItemize (can be NULL)
	__in               int                              cMaxTags,        // In    Length of pScriptTags array
	__out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG  *pScriptTags,     // Out:  list of script tags in the font
	__out              int                             *pcTags)           // Out:  Number of tags returned
{
	WRAP_BEGIN(ScriptGetFontScriptTags, LPFNSCRIPTGETFONTSCRIPTTAGS)
	LOG(L"<ScriptGetFontScriptTags>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptGetFontScriptTags(hdc,psc,psa,cMaxTags,pScriptTags,pcTags);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetFontScriptTags>");
	WRAP_END

}

#ifdef __cplusplus
}
#endif
