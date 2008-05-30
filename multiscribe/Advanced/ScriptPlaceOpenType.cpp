#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptPlaceOpenType=" USP10DLL ".ScriptPlaceOpenType")
#endif

#include "../GlyphsToTextSourceMap.h"
#include "../TextSource.h"

LPVOID GetOriginalScriptPlaceOpenType();

HRESULT GetPositions(
	TextSource & textSource,
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cGlyphs) const WORD             *pwGlyphs,  // In    Glyph buffer from prior ScriptShape call
	int                                         cGlyphs,    // In    Number of glyphs
	__inout_ecount(1) SCRIPT_ANALYSIS           *psa,       // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_full(cGlyphs) int              *piAdvance, // Out   Advance wdiths
	__out_ecount_full_opt(cGlyphs) GOFFSET      *pGoffset,  // Out   x,y offset for combining glyph
	__out_ecount(1) ABC                         *pABC);      // Out   Composite ABC for the whole run (Optional)

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
	if(!hdc && !*psc){
		return E_PENDING;
	}

	GlyphPositions * pGlyphPositions = NULL;
	if(*psc){
		pGlyphPositions = GetGlyphPositions(*psc, psa, pwGlyphs, cGlyphs);
	}
	if(!pGlyphPositions){
		if(!hdc){
			return E_PENDING;
		}
		if(IsGraphiteFont(hdc)){
			TextSource textSource(pwcChars, cChars);
			textSource.setRightToLeft(psa->fRTL);
			return GetPositions(textSource, hdc, psc, pwGlyphs, cGlyphs, psa, piAdvance, pGoffset, pABC);
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
		LPFNSCRIPTPLACEOPENTYPE ScriptPlaceOpenType = (LPFNSCRIPTPLACEOPENTYPE) GetOriginalScriptPlaceOpenType();
		return ScriptPlaceOpenType(hdc,psc,psa,tagScript,tagLangSys,rcRangeChars,rpRangeProperties,cRanges,pwcChars,pwLogClust,pCharProps,cChars,pwGlyphs,pGlyphProps,cGlyphs,piAdvance,pGoffset,pABC);
	}
}

//#ifdef __cplusplus
//}
//#endif