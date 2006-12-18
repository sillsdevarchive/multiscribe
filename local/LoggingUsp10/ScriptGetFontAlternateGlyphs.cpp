#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetFontAlternateGlyphs=_usp10.ScriptGetFontAlternateGlyphs")

/////  ScriptGetFontAlternateGlyphs
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETFONTALTERNATEGLYPHS)(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates

	__in               WORD                   wGlyphId,        // In    Original glyph

	__in               int                    cMaxAlternates,  // In    Length of pAlternateGlyphs tags array
	__out_ecount_part(cMaxAlternates, *pcAlternates) WORD *pAlternateGlyphs, // Out:  list of feature tags in the font
	__out              int                   *pcAlternates);     // Out:  Number of alternates returned

#ifdef __cplusplus
extern "C" {
#endif
__checkReturn HRESULT WINAPI LoggingScriptGetFontAlternateGlyphs(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates

	__in               WORD                   wGlyphId,        // In    Original glyph

	__in               int                    cMaxAlternates,  // In    Length of pAlternateGlyphs tags array
	__out_ecount_part(cMaxAlternates, *pcAlternates) WORD *pAlternateGlyphs, // Out:  list of feature tags in the font
	__out              int                   *pcAlternates)     // Out:  Number of alternates returned
{
	WRAP_BEGIN(ScriptGetFontAlternateGlyphs, LPFNSCRIPTGETFONTALTERNATEGLYPHS)
	LOG(L"<ScriptGetFontAlternateGlyphs>");
	LOG(L"<in>");
	if(hdc != NULL){
		LOG(L"<hdc>%d</hdc>", hdc);
	}
	LOG(L"<ScriptTag>%d</ScriptTag>", tagScript);
	LOG(L"<LangSysTag>%d</LangSysTag>", tagLangSys);
	LOG(L"<FeatureTag>%d</FeatureTag>", tagFeature);
	LOG(L"<GlyphId>%d</GlyphId>", wGlyphId);
	LOG(L"<MaxAlternates>%d</MaxAlternates>", cMaxAlternates);
	LOG(L"</in>");
	hResult = ScriptGetFontAlternateGlyphs(hdc,psc,psa,tagScript,tagLangSys,tagFeature,wGlyphId,cMaxAlternates, pAlternateGlyphs, pcAlternates);
	LOG(L"<out>");
	LOG(L"<Alternates count='%d'>", *pcAlternates);
	for(int i=0; i < *pcAlternates; ++i){
		LOG(L"<AlternateGlyphId>%d</AlternateGlyphId>", pAlternateGlyphs[i]);
	}
	LOG(L"</Alternates>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetFontAlternateGlyphs>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
