#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptPlaceOpenType=_usp10.ScriptPlaceOpenType")

///// ScriptPlaceOpenType

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTPLACEOPENTYPE)(
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in_ecount(cChars)        WORD                   *pwLogClust,     // In    Logical clusters
	__in_ecount(cChars)        SCRIPT_CHARPROP        *pCharProps,     // In    Output buffer for character properties
	__in                       int                     cChars,         // In    Length of unicode run

	__in_ecount(cGlyphs)       const WORD             *pwGlyphs,       // In    Glyph buffer from prior ScriptShape call
	__in_ecount(cGlyphs)       const SCRIPT_GLYPHPROP *pGlyphProps,    // In    Glyph properties
	__in                       int                     cGlyphs,        // In    Number of glyphs

	__out_ecount_full(cGlyphs) int                    *piAdvance,      // Out   Advance widths
	__out_ecount_full(cGlyphs) GOFFSET                *pGoffset,       // Out   x,y offset for combining glyph
	__out_opt                  ABC                    *pABC);          // Out   Composite ABC for the whole run (Optional)


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptPlaceOpenType(
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in_ecount(cChars)        WORD                   *pwLogClust,     // In    Logical clusters
	__in_ecount(cChars)        SCRIPT_CHARPROP        *pCharProps,     // In    Output buffer for character properties
	__in                       int                     cChars,         // In    Length of unicode run

	__in_ecount(cGlyphs)       const WORD             *pwGlyphs,       // In    Glyph buffer from prior ScriptShape call
	__in_ecount(cGlyphs)       const SCRIPT_GLYPHPROP *pGlyphProps,    // In    Glyph properties
	__in                       int                     cGlyphs,        // In    Number of glyphs

	__out_ecount_full(cGlyphs) int                    *piAdvance,      // Out   Advance widths
	__out_ecount_full(cGlyphs) GOFFSET                *pGoffset,       // Out   x,y offset for combining glyph
	__out_opt                  ABC                    *pABC)          // Out   Composite ABC for the whole run (Optional)
{
	WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
	LOG(L"<ScriptPlaceOpenType>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptPlaceOpenType>");
	WRAP_END
}

#ifdef __cplusplus
}
#endif