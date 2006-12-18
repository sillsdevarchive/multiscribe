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
	__out_ecount(1) ABC                         *pABC)     // Out   Composite ABC for the whole run (Optional)
{
	if(!hdc){ //TODO: keep a cache
		return E_PENDING;
	}
	if(IsGraphiteFont(hdc))
	{
		if(!psc)
		{
			WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
			// only to setup the cache correctly:
			hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
			WRAP_END_NO_RETURN
		}

		TextSource * pTextSource = GetTextSource(pwGlyphs, cGlyphs);
		if(!pTextSource){
			//fallback
			WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
			// only to setup the cache correctly:
			hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
			WRAP_END
		}

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, pTextSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators =
		seg.glyphs();

		std::vector<gr::GlyphInfo> rgGlyphInfo;

		for(gr::GlyphIterator it = prGlyphIterators.first;
							  it != prGlyphIterators.second;
							  ++it){
			rgGlyphInfo.push_back(*it);
		}

		if(cGlyphs != static_cast<int>(rgGlyphInfo.size())){
			assert(false);
			//fallback
			WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
			// only to setup the cache correctly:
			hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
			WRAP_END
		}

		for(int i =0; i<cGlyphs; ++i){
			//if(rgGlyphInfo[i].isAttached()){ //TODO figure out what this is supposed to be
			//	piAdvance[i] = static_cast<LONG>(ceil(rgGlyphInfo[i].attachedClusterAdvance()));   // x offset for combining glyph
			//	piAdvance[i] = 0;
			//	pGoffset[i].du = static_cast<int>(ceil(rgGlyphInfo[i].advanceWidth() - rgGlyphInfo[i].attachedClusterAdvance()));
			//	pGoffset[i].du = static_cast<int>(ceil(rgGlyphInfo[i].advanceWidth()));
			//}
			//else {
				piAdvance[i] = static_cast<int>(ceil(rgGlyphInfo[i].advanceWidth()));// should be rounded
				pGoffset[i].du = 0;
			//}
			pGoffset[i].dv = static_cast<LONG>(ceil(rgGlyphInfo[i].yOffset()));  // y offset
		}
		if(pABC){
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
