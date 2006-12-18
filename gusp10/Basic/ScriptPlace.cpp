#include <math.h>
#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"

//#pragma comment(linker, "/export:ScriptPlace=_usp10.ScriptPlace")

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

#ifdef __cplusplus
extern "C" {
#endif

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
	if(!hdc){ //TODO: keep a cache
		return E_PENDING;
	}
	if(IsGraphiteFont(hdc))
	{
		//if(!psc)
		//{
		//	WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
		//	// only to setup the cache correctly:
		//	hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
		//	WRAP_END_NO_RETURN
		//}

		TextSource * pTextSource = GetTextSource(pwGlyphs, cGlyphs);
		if(!pTextSource){
			//fallback
			WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
			hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
			WRAP_END
		}

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, pTextSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators = seg.glyphs();

		float xClusterEnd = 0.0;
		int i = 0;
		for(gr::GlyphIterator it = prGlyphIterators.first;
								  it != prGlyphIterators.second;
								  ++it, ++i){
			if(i > cGlyphs){
				break;
			}

			gr::GlyphIterator itNext = it + 1;

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
					piAdvance[i] = static_cast<int>(ceil(it->attachedClusterAdvance()));   // x offset for combining glyph
					xClusterEnd = it->origin() + it->attachedClusterAdvance();
					pGoffset[i].du = 0;
				}
				else {
					//Combining glyphs generally have a zero advance width and
					//generally have an offset that places them correctly in
					//relation to the nearest preceding base glyph.
					piAdvance[i] = 0;
					pGoffset[i].du = static_cast<int>(floor(it->origin() - xClusterEnd));
				}
			}
			else {
				piAdvance[i] = static_cast<int>(ceil(it->advanceWidth()));// should be rounded
				pGoffset[i].du = 0;
			}
			pGoffset[i].dv = static_cast<LONG>(ceil(it->yOffset()));  // y offset
		}
		if(i != cGlyphs){
			assert(false);
			//fallback
			WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
			hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
			WRAP_END
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
		WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
		hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
		WRAP_END
	}
}
#ifdef __cplusplus
}
#endif
