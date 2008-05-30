#include "../stdafx.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptShapeOpenType=" USP10DLL ".ScriptShapeOpenType")
#endif

#include "../TextSource.h"
LPVOID GetOriginalScriptShapeOpenType();
HRESULT GetGlyphsAndPositions(
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs);     // Out   Count of glyphs generated

/// ScriptShapeOpenType
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

//#ifdef __cplusplus
//extern "C" {
//#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptShapeOpenType(
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
	if(!hdc){ //TODO: keep a cache
		return E_PENDING;
	}
	LPFNSCRIPTSHAPEOPENTYPE ScriptShapeOpenType = (LPFNSCRIPTSHAPEOPENTYPE) GetOriginalScriptShapeOpenType();

	if(IsGraphiteFont(hdc))
	{
	HRESULT hResult;
		if(!*psc)
		{
	  hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
		//	WRAP_BEGIN(ScriptShapeOpenType, LPFNSCRIPTSHAPEOPENTYPE)
		//	// only to setup the cache correctly:
		//	hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
		//	WRAP_END_NO_RETURN
		}

	SCRIPT_VISATTR *psva = new SCRIPT_VISATTR[cMaxGlyphs];
	hResult = GetGlyphsAndPositions(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust,psva,pcGlyphs);

	if(SUCCEEDED(hResult)){
	  for(int i=0; i < *pcGlyphs; ++i){
		pOutGlyphProps[i].sva.fClusterStart = psva[i].fClusterStart;
		pOutGlyphProps[i].sva.fDiacritic = psva[i].fDiacritic;
		pOutGlyphProps[i].sva.fZeroWidth = psva[i].fZeroWidth;
		pOutGlyphProps[i].sva.uJustification = psva[i].uJustification;
	  }
	}
	delete[] psva;
		return hResult;
	}
	else {
//		WRAP_BEGIN(ScriptShapeOpenType, LPFNSCRIPTSHAPEOPENTYPE)
		HRESULT hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
	return hResult;
//		WRAP_END
	}
}
//#ifdef __cplusplus
//}
//#endif
