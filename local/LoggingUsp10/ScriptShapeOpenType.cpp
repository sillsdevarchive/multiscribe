#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptShapeOpenType=_usp10.ScriptShapeOpenType")

///// ScriptShapeOpenType
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSHAPEOPENTYPE) (
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in                       int                     cChars,         // In    Length of unicode run
	__in                       int                     cMaxGlyphs,     // In    Max glyphs to generate

	__out_ecount_full(cChars)  WORD                   *pwLogClust,     // Out   Logical clusters
	__out_ecount_full(cChars)  SCRIPT_CHARPROP        *pCharProps,     // Out   Output buffer for character properties

	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD                   *pwOutGlyphs,    // Out   Output glyph buffer
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_GLYPHPROP       *pOutGlyphProps, // Out   Visual glyph attributes
	__out                                    int                    *pcGlyphs);      // Out   Count of glyphs generated

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptShapeOpenType(
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in                       int                     cChars,         // In    Length of unicode run
	__in                       int                     cMaxGlyphs,     // In    Max glyphs to generate

	__out_ecount_full(cChars)  WORD                   *pwLogClust,     // Out   Logical clusters
	__out_ecount_full(cChars)  SCRIPT_CHARPROP        *pCharProps,     // Out   Output buffer for character properties

	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD                   *pwOutGlyphs,    // Out   Output glyph buffer
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_GLYPHPROP       *pOutGlyphProps, // Out   Visual glyph attributes
	__out                                    int                    *pcGlyphs)      // Out   Count of glyphs generated
{
	WRAP_BEGIN(ScriptShapeOpenType, LPFNSCRIPTSHAPEOPENTYPE)
	LOG(L"<ScriptShapeOpenType>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptShapeOpenType>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
