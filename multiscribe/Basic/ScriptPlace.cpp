#pragma comment(linker, "/export:ScriptPlace=_usp10.ScriptPlace")

#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"
#include "../TextSource.h"

LPVOID GetOriginalScriptPlace();

// ScriptPlace may be called twice for every ScriptShape but with a different device context
// (screen verses printer).
HRESULT GetPositions(TextSource & textSource,
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cGlyphs) const WORD             *pwGlyphs,  // In    Glyph buffer from prior ScriptShape call
	int                                         cGlyphs,    // In    Number of glyphs
	__inout_ecount(1) SCRIPT_ANALYSIS           *psa,       // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_full(cGlyphs) int              *piAdvance, // Out   Advance wdiths
	__out_ecount_full_opt(cGlyphs) GOFFSET      *pGoffset,  // Out   x,y offset for combining glyph
	__out_ecount(1) ABC                         *pABC)      // Out   Composite ABC for the whole run (Optional)
{

	// Create the Graphite font object.
	gr::WinFont font(hdc);

	// Create the segment.
	gr::LayoutEnvironment layout;
	layout.setStartOfLine(false);
	layout.setEndOfLine(false);
	layout.setDumbFallback(true);	// we want it to try its best, no matter what
	gr::RangeSegment seg(&font, &textSource, &layout);

	std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

	float * rgAdvanceWidth = new float[cGlyphs];
	float * rgOrigin = new float[cGlyphs];
	bool * rgIsAttached = new bool[cGlyphs];
	float realXOrigin = 0;

	{
		gr::GlyphIterator it = prGlyphIterators.first;
		for(int i = 0; i != cGlyphs; ++i,++it){
		  rgAdvanceWidth[i] = it->advanceWidth();
		  rgOrigin[i] = it->origin();
		  rgIsAttached[i] = it->isAttached();

		  if(psa->fRTL){
			assert (rgOrigin[i] <= 0);
			rgOrigin[i] *= -1;
			rgOrigin[i] -= rgAdvanceWidth[i];
		  }

		  realXOrigin = min<float>(realXOrigin, rgOrigin[i]);
		}
	}

	float totalAdvance = realXOrigin;

	float * rgAdvance = new float[cGlyphs];
	float * rgXOffset = new float[cGlyphs];
	float * rgTotalAdvance = new float[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  rgTotalAdvance[i] = totalAdvance;

	  if(!psa->fRTL && i != cGlyphs -1 &&
		rgAdvanceWidth[i] > 0 && rgAdvanceWidth[i+1] > 0
		&& rgOrigin[i+1]>=rgOrigin[i]){
		  rgAdvance[i] = rgOrigin[i+1] - rgOrigin[i];
	  }
	  else if(psa->fRTL && rgAdvanceWidth[i]!= 0 &&
		round(rgOrigin[i] - realXOrigin) < round(totalAdvance)){
		rgAdvance[i] = 0;
	  }
	  else {
		rgAdvance[i] = rgAdvanceWidth[i];
	  }

	  float xOffset = rgOrigin[i] - totalAdvance + realXOrigin;
	  if(psa->fRTL && rgAdvance[i] == 0){
		xOffset+=rgAdvanceWidth[i];
	  }
	  rgXOffset[i] = xOffset;

	  totalAdvance += rgAdvance[i];
	  if(rgAdvanceWidth[i] != 0 && rgXOffset[i]>0){
		totalAdvance += rgXOffset[i];
	  }
	}

	// initialize ClusterEndX positions by logicalGlyphIndex
	float * rgClusterEndX = new float[cGlyphs];

	int glyphIndex = 0;
	int logicalGlyphIndex;
	gr::GlyphIterator it;

	if(psa->fRTL && !psa->fLogicalOrder){
	  it = prGlyphIterators.second;
	  logicalGlyphIndex = cGlyphs;
	}
	else {
	  it = prGlyphIterators.first;
	  logicalGlyphIndex = 0;
	}

	for(;;){
	  if(psa->fRTL && !psa->fLogicalOrder){
		if(it == prGlyphIterators.first) {
		  break;
		}
		--it;
		--logicalGlyphIndex;
	  }
	  else {
		if(it == prGlyphIterators.second) {
		  break;
		}
	  }

	  float yOffset = it->yOffset();
	  pGoffset[glyphIndex].dv = static_cast<LONG>((yOffset > 0)?ceil(yOffset):floor(yOffset));  // y offset

	  float xOffset = rgXOffset[logicalGlyphIndex];
	  pGoffset[glyphIndex].du = static_cast<int>(round(xOffset));
	  if(psa->fRTL && !psa->fLogicalOrder){
		pGoffset[glyphIndex].du*=-1;
	  }
	  assert(rgAdvance[logicalGlyphIndex] >=0);
	  piAdvance[glyphIndex] = static_cast<int>(round(rgAdvance[logicalGlyphIndex]));
	  if(!(psa->fRTL && !psa->fLogicalOrder)){
		++it;
		++logicalGlyphIndex;
	  }
	  ++glyphIndex;
	}

	delete[] rgClusterEndX;
	delete[] rgAdvanceWidth;
	delete[] rgOrigin;
	delete[] rgIsAttached;
	delete[] rgAdvance;
	delete[] rgXOffset;
	delete[] rgTotalAdvance;
	if(pABC){
		pABC->abcA = static_cast<int>(floor(realXOrigin));//static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
		pABC->abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
		pABC->abcC = 0; // space to add to trailing edge (may be negative)
	}
	return S_OK;
}

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
				return GetPositions(textSource, hdc, psc, pwGlyphs, cGlyphs, psa, piAdvance, pGoffset, pABC);
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
		LPFNSCRIPTPLACE ScriptPlace = (LPFNSCRIPTPLACE) GetOriginalScriptPlace();
		return ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
	}
}
//#ifdef __cplusplus
//}
//#endif
