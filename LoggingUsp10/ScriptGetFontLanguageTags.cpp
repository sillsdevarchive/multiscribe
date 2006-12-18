#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetFontLanguageTags=_usp10.ScriptGetFontLanguageTags")

///// ScriptGetFontLanguageTags
#ifdef __cplusplus
extern "C" {
#endif
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTLANGUAGETAGS)(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag

	__in               int                    cMaxTags,        // In    Length of pLangsys tags array
	__out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pLangsysTags,    // Out:  list of Langsys tags in the font
	__out              int                   *pcTags);           // Out:  Number of tags returned


__checkReturn HRESULT WINAPI LoggingScriptGetFontLanguageTags(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag

	__in               int                    cMaxTags,        // In    Length of pLangsys tags array
	__out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pLangsysTags,    // Out:  list of Langsys tags in the font
	__out              int                   *pcTags)          // Out:  Number of tags returned
{
	WRAP_BEGIN(ScriptGetFontLanguageTags, LPFNSCRIPTGETFONTLANGUAGETAGS)
	LOG(L"<ScriptGetFontLanguageTags>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptGetFontLanguageTags(hdc,psc,psa,tagScript,cMaxTags,pLangsysTags,pcTags);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetFontLanguageTags>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
