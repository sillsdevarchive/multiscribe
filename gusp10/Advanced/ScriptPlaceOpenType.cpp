#pragma comment(linker, "/export:ScriptPlaceOpenType=_usp10.ScriptPlaceOpenType")

#include "../stdafx.h"
#include "../TextSource.h"
#include <math.h>

LPVOID GetOriginalScriptPlaceOpenType();

/// ScriptPlaceOpenType

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


//#ifdef __cplusplus
//extern "C" {
//#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptPlaceOpenType(
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
	if(!hdc){ //TODO: keep a cache
		return E_PENDING;
	}
	LPFNSCRIPTPLACEOPENTYPE ScriptPlaceOpenType = (LPFNSCRIPTPLACEOPENTYPE) GetOriginalScriptPlaceOpenType();

	if(IsGraphiteFont(hdc))
	{
		//if(!psc)
		//{
		//	WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
		//	// only to setup the cache correctly:
		//	hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
		//	WRAP_END_NO_RETURN
		//}

		TextSource textSource(pwcChars, cChars);
		textSource.setRightToLeft(psa->fRTL);

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, &textSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

		float xClusterEnd = 0.0;
		int i = 0;
		for(gr::GlyphIterator it = prGlyphIterators.first;
										  it != prGlyphIterators.second;
										  ++it, ++i){
			if(i > cGlyphs){
				break;
			}

			pGoffset[i].dv = static_cast<LONG>(ceil(it->yOffset()));  // y offset

	  float xOrigin = it->origin();
			float advance = it->advanceWidth();
	  if(psa->fRTL){
		assert (xOrigin <= 0);
		xOrigin *= -1;
		xOrigin -= advance;
	  }
	  if(i>0){
			  pGoffset[i].du = static_cast<int>(floor(xOrigin - xClusterEnd)); // allow for kerning
	  }
	  else {
		pGoffset[i].du = 0; // sometimes happens that xOrigin is not 0.0 with RTL
	  }

			if(it->isAttached()){
				//The advance width' of a glyph is the movement in the
				//direction of writing from the starting point for rendering
				//that glyph to the starting point for rendering the next glyph.
				//
				//The origin of each subsequent glyph is offset from that of the
				//previous glyph by the advance values of the previous glyph.
				//
				if(it == it->attachedClusterBase()){
					//Base glyphs generally have a non-zero advance width
					//and generally have a glyph offset of (0, 0).
		  advance = it->attachedClusterAdvance();
		  assert(advance >=0);
					xClusterEnd += advance;
				}
				else {
					//Combining glyphs generally have a zero advance width and
					//generally have an offset that places them correctly in
					//relation to the nearest preceding base glyph.
					advance = 0;
				}
			}
			else {
				xClusterEnd = xOrigin + advance;
			}
		piAdvance[i] = static_cast<int>(ceil(advance));// should be rounded
		}
		if(i != cGlyphs){
			assert(false);
			//fallback
//			WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
			HRESULT hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
	  return hResult;
//			WRAP_END
		}

		if(pABC){ //TODO
			// really the segment should have public properties for
			// members, m_dxsLeftOverhang, m_dxsRightOverhang and m_dxsVisibleWidth
			gr::Rect boundingRect = seg.boundingRect();
			pABC->abcA = static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
			pABC->abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
			pABC->abcC = 0; // space to add to trailing edge (may be negative)
		}
		return S_OK;
	}
	else {
//		WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
		HRESULT hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
	return hResult;
//		WRAP_END
	}
}

//#ifdef __cplusplus
//}
//#endif