#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptGetFontLanguageTags=" USP10DLL ".ScriptGetFontLanguageTags")
#endif
///// ScriptGetFontLanguageTags
//#ifdef __cplusplus
//extern "C" {
//#endif
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTLANGUAGETAGS)(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//
//    __in               int                    cMaxTags,        // In    Length of pLangsys tags array
//    __out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pLangsysTags,    // Out:  list of Langsys tags in the font
//    __out              int                   *pcTags);           // Out:  Number of tags returned
//
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetFontLanguageTags(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//
//    __in               int                    cMaxTags,        // In    Length of pLangsys tags array
//    __out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pLangsysTags,    // Out:  list of Langsys tags in the font
//    __out              int                   *pcTags)          // Out:  Number of tags returned
//{
//	WRAP_BEGIN(ScriptGetFontLanguageTags, LPFNSCRIPTGETFONTLANGUAGETAGS)
//	hResult = ScriptGetFontLanguageTags(hdc,psc,psa,tagScript,cMaxTags,pLangsysTags,pcTags);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
