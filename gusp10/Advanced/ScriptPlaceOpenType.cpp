#include "../stdafx.h"
#include "../TextSource.h"
#include <math.h>
//#pragma comment(linker, "/export:ScriptPlaceOpenType=_usp10.ScriptPlaceOpenType")

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


#ifdef __cplusplus
extern "C" {
#endif

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
	if(IsGraphiteFont(hdc))
	{
		if(!psc)
		{
			WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
			// only to setup the cache correctly:
			hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
			WRAP_END_NO_RETURN
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

		std::vector<gr::GlyphInfo> rgGlyphInfo;

		for(gr::GlyphIterator it = prGlyphIterators.first;
							  it != prGlyphIterators.second;
							  ++it){
			rgGlyphInfo.push_back(*it);
		}

		float xCurrent = 0.0;
		int i = 0;
		for(gr::GlyphIterator it = prGlyphIterators.first;
								  it != prGlyphIterators.second;
								  ++it, ++i){
			if(i > cGlyphs){
				break;
			}

			float advanceWidth = it->advanceWidth();
			advanceWidth;
			float origin = it->origin();
			origin;
			float attachedClusterAdvance = it->attachedClusterAdvance();
			attachedClusterAdvance;

			if(it->isAttached()){
				piAdvance[i] = 0;//static_cast<int>(ceil(it->advanceWidth()));

				pGoffset[i].du = static_cast<int>(floor(it->origin() - xCurrent));
				if(it == it->attachedClusterBase()){ // first glyph of attached cluster
					piAdvance[i] = static_cast<LONG>(ceil(it->attachedClusterAdvance()));   // x offset for combining glyph
					xCurrent = it->origin() + it->attachedClusterAdvance();
					pGoffset[i].du = 0;
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
			WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
			// only to setup the cache correctly:
			hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
			WRAP_END
		}

		if(pABC){
		}
		return S_OK;
	}
	else {
		WRAP_BEGIN(ScriptPlaceOpenType, LPFNSCRIPTPLACEOPENTYPE)
		hResult = ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
		WRAP_END
	}
}

#ifdef __cplusplus
}
#endif