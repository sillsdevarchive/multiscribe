#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptGetFontAlternateGlyphs=" USP10DLL ".ScriptGetFontAlternateGlyphs")
#endif
/////  ScriptGetFontAlternateGlyphs
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTALTERNATEGLYPHS)(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//    __in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
//    __in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
//
//    __in               WORD                   wGlyphId,        // In    Original glyph
//
//    __in               int                    cMaxAlternates,  // In    Length of pAlternateGlyphs tags array
//    __out_ecount_part(cMaxAlternates, *pcAlternates) WORD *pAlternateGlyphs, // Out:  list of feature tags in the font
//    __out              int                   *pcAlternates);     // Out:  Number of alternates returned
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetFontAlternateGlyphs(
//    __in_opt           HDC                    hdc,             // In    Optional (see under caching)
//    __inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
//    __in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
//    __in               OPENTYPE_TAG           tagScript,       // In    Font script tag
//    __in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
//    __in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
//
//    __in               WORD                   wGlyphId,        // In    Original glyph
//
//    __in               int                    cMaxAlternates,  // In    Length of pAlternateGlyphs tags array
//    __out_ecount_part(cMaxAlternates, *pcAlternates) WORD *pAlternateGlyphs, // Out:  list of feature tags in the font
//    __out              int                   *pcAlternates)     // Out:  Number of alternates returned
//{
//	WRAP_BEGIN(ScriptGetFontAlternateGlyphs, LPFNSCRIPTGETFONTALTERNATEGLYPHS)
//	hResult = ScriptGetFontAlternateGlyphs(hdc,psc,psa,tagScript,tagLangSys,tagFeature,wGlyphId,cMaxAlternates, pAlternateGlyphs, pcAlternates);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
