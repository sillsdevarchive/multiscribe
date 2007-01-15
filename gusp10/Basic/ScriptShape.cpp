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
			if( FAILED(hResult) && hResult != USP_E_SCRIPT_NOT_IN_FONT){
				return hResult;
			}
			FreeGlyphPositionsForSession(*psc);
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

		GlyphPositions glyphPositions;
		glyphPositions.advanceWidths.resize(cGlyphs);
		glyphPositions.glyphs.resize(cGlyphs);
		glyphPositions.goffsets.resize(cGlyphs);

		SetLastScriptShapeTextSource(textSource);

		int * rgFirstGlyphOfCluster = new int [cChars];
		bool * rgIsClusterStart = new bool [cGlyphs];
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

	float xClusterEnd = 0.0;
		int i = 0;
	if(psa->fRTL && !psa->fLogicalOrder){
	  i = cGlyphs-1;
	}
		for(gr::GlyphIterator it = prGlyphIterators.first;
							  it != prGlyphIterators.second;
							  ++it){
			glyphPositions.glyphs[i] = pwOutGlyphs[i] = it->glyphID();

			psva[i].fClusterStart = rgIsClusterStart[i];
			psva[i].fDiacritic = (psva[i].fClusterStart)?false:it->isAttached();
			psva[i].fZeroWidth = false; // TODO: when does this need to be set?
			psva[i].uJustification = SCRIPT_JUSTIFY_NONE; //TODO: when does this need to change

		glyphPositions.goffsets[i].dv = static_cast<LONG>(ceil(it->yOffset()));  // y offset

	  float xOrigin = it->origin();
			float advance = it->advanceWidth();
			if(psa->fRTL){
				assert (xOrigin <= 0);
				xOrigin *= -1;
		xOrigin -= advance;
			}
	  if(i>0){
		glyphPositions.goffsets[i].du = static_cast<int>(floor(xOrigin - xClusterEnd));
	  }
	  else {
		glyphPositions.goffsets[i].du = 0; // sometimes happens that xOrigin is not 0.0 with RTL
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
			glyphPositions.advanceWidths[i] = static_cast<int>(ceil(advance));// should be rounded

	  if(psa->fRTL && !psa->fLogicalOrder){
		--i;
	  }
	  else {
		++i;
	  }
	}

		delete[] rgIsClusterStart;

	int iGlyphPosition;
		for(int i=0; i < cChars; ++i){
	  if(psa->fRTL && !psa->fLogicalOrder){
		iGlyphPosition = cGlyphs - i - 1;
	  }
	  else {
		iGlyphPosition = i;
	  }
			pwLogClust[i] = static_cast<WORD>(rgFirstGlyphOfCluster[iGlyphPosition]);
		}

		delete[] rgFirstGlyphOfCluster;

		//TODO: really the segment should have public properties for
		// members, m_dxsLeftOverhang, m_dxsRightOverhang and m_dxsVisibleWidth
		gr::Rect boundingRect = seg.boundingRect();
		glyphPositions.abc.abcA = static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
		glyphPositions.abc.abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
		glyphPositions.abc.abcC = 0; // space to add to trailing edge (may be negative)

		SetGlyphPositions(*psc, psa, glyphPositions);

		//TODO: figure out when we should return USP_E_SCRIPT_NOT_IN_FONT to enable font fallback
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
