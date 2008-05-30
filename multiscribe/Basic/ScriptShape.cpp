#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptShape=" USP10DLL ".ScriptShape")
#endif

#include "../GlyphsToTextSourceMap.h"
#include "../TextSource.h"
#include <utility>
#include <limits>

LPVOID GetOriginalScriptShape();

bool IsNko(const WCHAR* sz, int c){
  for(int i = 0; i != c; ++i){
	if(0x07C0 <= sz[i] && sz[i] <= 0x07ff){
	  return true;
	}
  }
  return false;
}

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
	__out_ecount(1) int                                     *pcGlyphs)      // Out   Count of glyphs generated
{
	TextSource textSource(pwcChars, cChars);
	textSource.setRightToLeft(psa->fRTL);

	// Create the Graphite font object.
	gr::WinFont font(hdc);

	// Create the segment.
	gr::LayoutEnvironment layout;
	layout.setStartOfLine(false);
	layout.setEndOfLine(false);
	layout.setDumbFallback(true);	// we want it to try its best, no matter what
	gr::RangeSegment seg(&font, &textSource, &layout);

	std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

	int cGlyphs = 0;
	for (gr::GlyphIterator it = prGlyphIterators.first;
						  it != prGlyphIterators.second;
						  ++it) {
		++cGlyphs;
	}
	assert(cGlyphs == (prGlyphIterators.second - prGlyphIterators.first));

	// if the output buffer length, cMaxGlyphs, is insufficient.
	if (cGlyphs >  std::max(cMaxGlyphs,0)) {
		return E_OUTOFMEMORY;
	}

	*pcGlyphs = cGlyphs;

	GlyphPositions glyphPositions;
	glyphPositions.advanceWidths.resize(cGlyphs);
	glyphPositions.glyphs.resize(cGlyphs);
	glyphPositions.goffsets.resize(cGlyphs);

	SetLastScriptShapeTextSource(textSource);

	gr::Font & fontNoDc = seg.getFont();
	seg.SwitchFont(&font);

	int * rgFirstGlyphOfCluster = new int [cChars];
	bool * rgIsClusterStart = new bool [cGlyphs]; //in logical order but the start of a rtl cluster is the last glyph of the cluster
	int cCharsX, cgidX;
	seg.getUniscribeClusters(rgFirstGlyphOfCluster, cChars, &cCharsX,
						rgIsClusterStart, *pcGlyphs, &cgidX);

	for ( int i = 0; i < cChars; ++i)
	{
		if (psa->fRTL && !psa->fLogicalOrder)
		{
			pwLogClust[i] = static_cast<WORD>(cGlyphs - 1 - rgFirstGlyphOfCluster[i]);
		}
		else
		{
			pwLogClust[i] = static_cast<WORD>(rgFirstGlyphOfCluster[i]);
		}
	}
	delete[] rgFirstGlyphOfCluster;

	seg.SwitchFont(&fontNoDc);

	float * rgAdvanceWidth = new float[cGlyphs];
	float * rgOrigin = new float[cGlyphs];
	bool * rgIsAttached = new bool[cGlyphs];
	float realXOrigin = 0;
	float segWidth = seg.advanceWidth();

	{
		gr::GlyphIterator it = prGlyphIterators.first;
		for (int i = 0; i != cGlyphs; ++i,++it) {
			rgAdvanceWidth[i] = it->advanceWidth();
			rgOrigin[i] = it->origin();
			rgIsAttached[i] = it->isAttached();

			if (psa->fRTL) {
				// Put all glyphs in left-to-right order.
				rgOrigin[i] -= segWidth;
				assert(rgOrigin[i] <= 0);
				rgOrigin[i] *= -1;
				rgOrigin[i] -= rgAdvanceWidth[i];
			}
			realXOrigin = min<float>(realXOrigin, rgOrigin[i]);
		}
	}

	float advanceSoFar = realXOrigin;

	float * rgAdvance = new float[cGlyphs];
	float * rgXOffset = new float[cGlyphs];
	float * rgTotalAdvance = new float[cGlyphs];
	for (int i = 0; i != cGlyphs; ++i)
	{
		rgTotalAdvance[i] = advanceSoFar;

		if (!psa->fRTL && i != cGlyphs - 1
				&& rgAdvanceWidth[i] > 0 && rgAdvanceWidth[i+1] > 0
				&& rgOrigin[i+1] >= rgOrigin[i])
		{
			rgAdvance[i] = rgOrigin[i+1] - rgOrigin[i];
		}
		else if (psa->fRTL && rgAdvanceWidth[i] != 0
				&& round(rgOrigin[i] - realXOrigin) < round(advanceSoFar))
		{
			rgAdvance[i] = 0;
		}
		else {
			rgAdvance[i] = rgAdvanceWidth[i];
		}

		float xOffset = rgOrigin[i] - advanceSoFar + realXOrigin;
		if (psa->fRTL && rgAdvance[i] == 0)
		{
			xOffset += rgAdvanceWidth[i];
		}
		rgXOffset[i] = xOffset;

		advanceSoFar += rgAdvance[i];
		if (rgAdvanceWidth[i] != 0 && rgXOffset[i] > 0)
		{
			advanceSoFar += rgXOffset[i];
		}
	}

	// initialize ClusterEndX positions by logicalGlyphIndex
	float * rgClusterEndX = new float[cGlyphs];

	int glyphIndex = 0;
	int logicalGlyphIndex;
	gr::GlyphIterator it2; // vc8 needs this, vc7 doesn't want it

	if (psa->fRTL && !psa->fLogicalOrder) {
		it2 = prGlyphIterators.second;
		logicalGlyphIndex = cGlyphs;
	}
	else {
		it2 = prGlyphIterators.first;
		logicalGlyphIndex = 0;
	}

	for ( ; ; ) {
		if (psa->fRTL && !psa->fLogicalOrder) {
			if (it2 == prGlyphIterators.first) {
				break;
			}
			--it2;
			--logicalGlyphIndex;
		}
		else {
			if (it2 == prGlyphIterators.second) {
				break;
			}
		}

		glyphPositions.glyphs[glyphIndex] = pwOutGlyphs[glyphIndex] = it2->glyphID();

		psva[glyphIndex].fClusterStart = rgIsClusterStart[logicalGlyphIndex];
		psva[glyphIndex].fDiacritic = (psva[glyphIndex].fClusterStart) ? false : it2->isAttached();
		psva[glyphIndex].fZeroWidth = false; // TODO: when does this need to be set?
		psva[glyphIndex].uJustification = SCRIPT_JUSTIFY_NONE; //TODO: when does this need to change
		psva[glyphIndex].fShapeReserved=0;
		psva[glyphIndex].fReserved=0;
		float yOffset = it2->yOffset();
		glyphPositions.goffsets[glyphIndex].dv = static_cast<LONG>((yOffset > 0) ? ceil(yOffset) : floor(yOffset));  // y offset

		float xOffset = rgXOffset[logicalGlyphIndex];
		glyphPositions.goffsets[glyphIndex].du = static_cast<int>(round(xOffset));
		if (psa->fRTL && !psa->fLogicalOrder) {
			glyphPositions.goffsets[glyphIndex].du *= -1;
		}
		assert(rgAdvance[logicalGlyphIndex] >=0);
		glyphPositions.advanceWidths[glyphIndex] = static_cast<int>(round(rgAdvance[logicalGlyphIndex]));
		if (!(psa->fRTL && !psa->fLogicalOrder)) {
			++it2;
			++logicalGlyphIndex;
		}
		++glyphIndex;
	}

	delete[] rgIsClusterStart;
	delete[] rgClusterEndX;
	delete[] rgAdvanceWidth;
	delete[] rgOrigin;
	delete[] rgIsAttached;
	delete[] rgAdvance;
	delete[] rgXOffset;
	delete[] rgTotalAdvance;

	// TODO: really the segment should have public properties for
	// members, m_dxsLeftOverhang, m_dxsRightOverhang and m_dxsVisibleWidth
	gr::Rect boundingRect = seg.boundingRect();
	glyphPositions.abc.abcA = static_cast<int>(floor(realXOrigin)); //static_cast<int>(ceil(boundingRect.left)); // space to leading edge (may be negative)
	glyphPositions.abc.abcB = static_cast<UINT>(ceil(seg.advanceWidth())); // drawn portion
	glyphPositions.abc.abcC = 0; // space to add to trailing edge (may be negative)

	SetGlyphPositions(*psc, psa, glyphPositions);

	//TODO: figure out when we should return USP_E_SCRIPT_NOT_IN_FONT to enable font fallback
	return S_OK;
}

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
	if (!hdc) {
		return E_PENDING;
	}
	LPFNSCRIPTSHAPE ScriptShape = (LPFNSCRIPTSHAPE) GetOriginalScriptShape();

	if (IsGraphiteFont(hdc))
	{
		if (!*psc)
		{
			HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,
								pwOutGlyphs,pwLogClust, psva,pcGlyphs);
			if (FAILED(hResult) && hResult != USP_E_SCRIPT_NOT_IN_FONT
					&& !(hResult == E_INVALIDARG && IsNko(pwcChars,cChars)))
			{
				assert(false);
				return hResult;
			}
			FreeGlyphPositionsForSession(*psc);
		}
		return GetGlyphsAndPositions(hdc, psc, pwcChars,cChars,cMaxGlyphs,psa,
								pwOutGlyphs,pwLogClust,psva,pcGlyphs);
	}
	else
	{
		HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,
								pwOutGlyphs,pwLogClust, psva,pcGlyphs);
		return hResult;
	}
}
//#ifdef __cplusplus
//}
//#endif
