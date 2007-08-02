//#include "../stdafx.h"
#pragma comment(linker, "/export:ScriptGetFontFeatureTags=_usp10.ScriptGetFontFeatureTags")

///// ScriptGetFontFeatureTags
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTFEATURETAGS)(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//    __in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
//
//    __in               int                    cMaxTags,        // In    Length of pLangsys tags array
//    __out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pFeatureTags,   // Out:  list of feature tags in the font
//    __out              int                   *pcTags);           // Out:  Number of tags returned
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetFontFeatureTags(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//    __in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
//
//    __in               int                    cMaxTags,        // In    Length of pLangsys tags array
//    __out_ecount_part(cMaxTags, *pcTags) OPENTYPE_TAG *pFeatureTags,   // Out:  list of feature tags in the font
//    __out              int                   *pcTags           // Out:  Number of tags returned
//)
//{
//	WRAP_BEGIN(ScriptGetFontFeatureTags, LPFNSCRIPTGETFONTFEATURETAGS)
//	hResult = ScriptGetFontFeatureTags(hdc,psc,psa,tagScript,tagLangSys,cMaxTags,pFeatureTags,pcTags);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
