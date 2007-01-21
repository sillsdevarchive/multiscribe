#pragma comment(linker, "/export:ScriptPlace=_usp10.ScriptPlace")


#include <math.h>
#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"
#include "../TextSource.h"

LPVOID GetOriginalScriptPlace();

// ScriptPlace may be called twice for every ScriptShape but with a different device context
// (screen verses printer).

/////   ScriptPlace
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTPLACE)(
	HDC                                         hdc,        // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE        *psc,       // InOut Cache handle
	__in_ecount(cGlyphs) const WORD             *pwGlyphs,  // In    Glyph buffer from prior ScriptShape call
	int                                         cGlyphs,    // In    Number of glyphs
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,      // In    Visual glyph attributes
	__inout_ecount(1) SCRIPT_ANALYSIS           *psa,       // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_full(cGlyphs) int              *piAdvance, // Out   Advance wdiths
	__out_ecount_full_opt(cGlyphs) GOFFSET      *pGoffset,  // Out   x,y offset for combining glyph
	__out_ecount(1) ABC                         *pABC);     // Out   Composite ABC for the whole run (Optional)

//#ifdef __cplusplus
//extern "C" {
//#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptPlace(
	HDC                                         hdc,        // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE        *psc,       // InOut Cache handle
	__in_ecount(cGlyphs) const WORD             *pwGlyphs,  // In    Glyph buffer from prior ScriptShape call
	int                                         cGlyphs,    // In    Number of glyphs
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,      // In    Visual glyph attributes
	__inout_ecount(1) SCRIPT_ANALYSIS           *psa,       // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_full(cGlyphs) int              *piAdvance, // Out   Advance wdiths
	__out_ecount_full_opt(cGlyphs) GOFFSET      *pGoffset,  // Out   x,y offset for combining glyph
	__out_ecount(1) ABC                         *pABC)      // Out   Composite ABC for the whole run (Optional)
{
	if(!hdc && !*psc){
		return E_PENDING;
	}
	LPFNSCRIPTPLACE ScriptPlace = (LPFNSCRIPTPLACE) GetOriginalScriptPlace();
//	if(!*psc)
//	{
//		//WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
//		// only to setup the cache correctly:
//		HRESULT hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
//    if( FAILED(hResult)){
//      return hResult;
//    }
//    FreeGlyphPositionsForSession(*psc);
////	WRAP_END_NO_RETURN
//	}

	GlyphPositions * pGlyphPositions = NULL;
  if(*psc){
	pGlyphPositions = GetGlyphPositions(*psc, psa, pwGlyphs, cGlyphs);
  }
  if(!pGlyphPositions){
	// maybe it couldn't find it because a different hdc/psc was used from the ScriptShape
	// if that's the case lets see if the glyphs we've been given were the same as came out
	// of the last ScriptShape call

	if(cGlyphs == static_cast<int>(GetLastScriptShapeGlyphs().size()) &&
		std::equal(GetLastScriptShapeGlyphs().begin(),
				   GetLastScriptShapeGlyphs().end(),
				   pwGlyphs)){
		if(!hdc){
			return E_PENDING;
		}
	  if(IsGraphiteFont(hdc)){

		  TextSource textSource(GetLastScriptShapeTextSource());

			// Create the Graphite font object.
			gr::WinFont font(hdc);

			// Create the segment.
			gr::LayoutEnvironment layout;	// use all the defaults...
			layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
			gr::RangeSegment seg(&font, &textSource, &layout);

			std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

			float xClusterEnd = 0.0;
			int i = 0;
		gr::GlyphIterator it;
		if(psa->fRTL && !psa->fLogicalOrder){
		  it = prGlyphIterators.second;
		}
		else {
		  it = prGlyphIterators.first;
		}

		for(;;){
		  if(psa->fRTL && !psa->fLogicalOrder){
			if(it == prGlyphIterators.first) {
			  break;
			}
			--it;
		  }
		  else {
			if(it == prGlyphIterators.second) {
			  break;
			}
		  }
				pGoffset[i].dv = static_cast<LONG>(ceil(it->yOffset()));  // y offset

		  float xOrigin = it->origin();
				float advance = it->advanceWidth();
		  if(textSource.getRightToLeft(0) && psa->fLogicalOrder){
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
			  assert(advance >= 0);
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

		  if(!(psa->fRTL && !psa->fLogicalOrder)){
			++it;
		  }
		  ++i;
			}

		  if(pABC){
			  //TODO: really the segment should have public properties for
			  // members, m_dxsLeftOverhang, m_dxsRightOverhang and m_dxsVisibleWidth
			  gr::Rect boundingRect = seg.boundingRect();
				pABC->abcA = static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
				pABC->abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
				pABC->abcC = 0; // space to add to trailing edge (may be negative)
			}

			return S_OK;
	  }
	}
  }

	if(pGlyphPositions)
	{
		for(int i = 0; i < cGlyphs; ++i){
			piAdvance[i] = pGlyphPositions->advanceWidths[i];
			pGoffset[i].du = pGlyphPositions->goffsets[i].du;
			pGoffset[i].dv = pGlyphPositions->goffsets[i].dv;
		}

		if(pABC){
			pABC->abcA = pGlyphPositions->abc.abcA;
			pABC->abcB = pGlyphPositions->abc.abcB;
			pABC->abcC = pGlyphPositions->abc.abcC;
		}
		return S_OK;
	}
	else {
		return ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
	}
}
//#ifdef __cplusplus
//}
//#endif
