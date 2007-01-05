#pragma comment(linker, "/export:ScriptShapeOpenType=_usp10.ScriptShapeOpenType")

#include "../stdafx.h"
#include "../TextSource.h"
LPVOID GetOriginalScriptShapeOpenType();

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
		if(!*psc)
		{
	  HRESULT hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
	  hResult;
		//	WRAP_BEGIN(ScriptShapeOpenType, LPFNSCRIPTSHAPEOPENTYPE)
		//	// only to setup the cache correctly:
		//	hResult = ScriptShapeOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,cChars,cMaxGlyphs,pwLogClust,pCharProps,pwOutGlyphs,pOutGlyphProps,pcGlyphs);
		//	WRAP_END_NO_RETURN
		}

		 TextSource textSource(pwcChars, cChars);
		 textSource.setRightToLeft(psa->fRTL);

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, &textSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

		int cGlyphs = 0;

		for(gr::GlyphIterator it = prGlyphIterators.first;
										it != prGlyphIterators.second;
										++it){
			++cGlyphs;
		}

		// if the output buffer length, cMaxGlyphs, is insufficient.
		if(cGlyphs >  std::max(cMaxGlyphs,0)){
			return E_OUTOFMEMORY;
		}

		*pcGlyphs = cGlyphs;

		int * rgFirstGlyphOfCluster = new int [cChars];
		bool * rgIsClusterStart = new bool [*pcGlyphs];
		int cCharsX, cgidX;
	if(psa->fRTL){
	  seg.getUniscribeClusters(NULL, rgFirstGlyphOfCluster,
											   cChars, &cCharsX,
											   NULL, rgIsClusterStart, *pcGlyphs, &cgidX);
	}
	else{
	  seg.getUniscribeClusters(rgFirstGlyphOfCluster, NULL,
											   cChars, &cCharsX,
											   rgIsClusterStart, NULL, *pcGlyphs, &cgidX);
	}

	int i = 0;
		for(gr::GlyphIterator it = prGlyphIterators.first;
									  it != prGlyphIterators.second;
						  ++it, ++i){
		pwOutGlyphs[i] = it->glyphID();
		  pOutGlyphProps[i].sva.fClusterStart = rgIsClusterStart[i];
		  pOutGlyphProps[i].sva.fDiacritic = (pOutGlyphProps[i].sva.fClusterStart)?false:it->isAttached();
		  pOutGlyphProps[i].sva.fZeroWidth = false; // TODO: when does this need to be set?
		  pOutGlyphProps[i].sva.uJustification = SCRIPT_JUSTIFY_NONE; //TODO: when does this need to change
		}

		delete[] rgIsClusterStart;
		for(int i=0; i < cChars; ++i){
	  pwLogClust[i] = static_cast<WORD>(rgFirstGlyphOfCluster[i]);
		}

		delete[] rgFirstGlyphOfCluster;
		return S_OK;
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
