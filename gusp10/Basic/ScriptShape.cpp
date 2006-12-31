#pragma comment(linker, "/export:ScriptShape=_usp10.ScriptShape")

#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"
#include "../TextSource.h"
#include <utility>
#include <limits>
LPVOID GetOriginalScriptShape();


///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptShape

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSHAPE) (
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

//#ifdef __cplusplus
//extern "C" {
//#endif
__checkReturn HRESULT WINAPI GraphiteEnabledScriptShape(
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs)     // Out   Count of glyphs generated
{
	if(!hdc){
		return E_PENDING;
	}
	LPFNSCRIPTSHAPE ScriptShape = (LPFNSCRIPTSHAPE) GetOriginalScriptShape();

	if(IsGraphiteFont(hdc))
	{
		if(!*psc)
		{
			HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
	  if( FAILED(hResult)){
		return hResult;
	  }
	  FreeGlyphPositionsForSession(*psc);
		}

	if(psa->fRTL){
	  assert(psa->fLogicalOrder); // no support yet for visual order
	}
		TextSource textSource(pwcChars, cChars);
		textSource.setRightToLeft(psa->fRTL);

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, &textSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators =
			seg.glyphs();

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

		GlyphPositions* pGlyphPositions = CreateGlyphPositions(*psc, psa, cGlyphs);

		int * rgFirstGlyphOfCluster = new int [cChars];
		int * rgLastGlyphOfCluster = new int [cChars];
		bool * rgIsClusterStart = new bool [cGlyphs];
		bool * rgIsClusterEnd = new bool [cGlyphs];
		int cCharsX, cgidX;
		seg.getUniscribeClusters(rgFirstGlyphOfCluster, rgLastGlyphOfCluster, cChars, &cCharsX,
								 rgIsClusterStart, rgIsClusterEnd, cGlyphs, &cgidX);

		float xClusterEnd = 0.0;
		int i = 0;
		for(gr::GlyphIterator it = prGlyphIterators.first;
							  it != prGlyphIterators.second;
							  ++it, ++i){

			pwOutGlyphs[i] = it->glyphID();
	  psva[i].fClusterStart = (psa->fRTL)?rgIsClusterStart[i]: rgIsClusterEnd[i];
		  psva[i].fDiacritic = (psva[i].fClusterStart)?false:it->isAttached();
			psva[i].fZeroWidth = false; // TODO: when does this need to be set?
			psva[i].uJustification = SCRIPT_JUSTIFY_NONE; //TODO: when does this need to change

	  if(it->isAttached()){
		float xOrigin = it->origin();
		if(psa->fRTL){
		  assert (xOrigin <= 0);
		  xOrigin *= -1;
		}

				//The advance width' of a glyph is the movement in the
				//direction of writing from the starting point for rendering
				//that glyph to the starting point for rendering the next glyph.
				//
				//The origin of each subsequent glyph is offset from that of the
				//previous glyph by the advance values of the previous glyph.
				//
				if(it == it->attachedClusterBase()){
		  float advance = it->attachedClusterAdvance();
		  assert(advance > 0);

					//Base glyphs generally have a non-zero advance width
					//and generally have a glyph offset of (0, 0).
					pGlyphPositions->advanceWidths[i] = static_cast<int>(ceil(advance));   // x offset for combining glyph

		  xClusterEnd = xOrigin;
		  if(!psa->fRTL){
			xClusterEnd += advance;
		  }
					pGlyphPositions->goffsets[i].du = 0;
				}
				else {
					//Combining glyphs generally have a zero advance width and
					//generally have an offset that places them correctly in
					//relation to the nearest preceding base glyph.
					pGlyphPositions->advanceWidths[i] = 0;
			  pGlyphPositions->goffsets[i].du = static_cast<int>(floor(xOrigin - xClusterEnd));
				}
			}
			else {
				pGlyphPositions->advanceWidths[i] = static_cast<int>(ceil(it->advanceWidth()));// should be rounded
				pGlyphPositions->goffsets[i].du = 0;
			}
			pGlyphPositions->goffsets[i].dv = static_cast<LONG>(ceil(it->yOffset()));  // y offset
		}

		delete[] rgIsClusterStart;
		delete[] rgIsClusterEnd;

	for(int i=0; i < cChars; ++i){
	  pwLogClust[i] = static_cast<WORD>((psa->fRTL)?rgFirstGlyphOfCluster[i]:rgLastGlyphOfCluster[i]);
	  }

		delete[] rgFirstGlyphOfCluster;
		delete[] rgLastGlyphOfCluster;

		//TODO: really the segment should have public properties for
		// members, m_dxsLeftOverhang, m_dxsRightOverhang and m_dxsVisibleWidth
		gr::Rect boundingRect = seg.boundingRect();
		pGlyphPositions->abc.abcA = static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
		pGlyphPositions->abc.abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
		pGlyphPositions->abc.abcC = 0; // space to add to trailing edge (may be negative)

	psa->eScript = SCRIPT_UNDEFINED; // it seems that the script engine's text out may be trying to do special things especially in the case of arabic
		return S_OK;
	}
	else
	{
		HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
		return hResult;
	}
}
//#ifdef __cplusplus
//}
//#endif
