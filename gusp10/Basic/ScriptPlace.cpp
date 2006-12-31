#pragma comment(linker, "/export:ScriptPlace=_usp10.ScriptPlace")


#include <math.h>
#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"

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
	if(!*psc)
	{
		//WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
		// only to setup the cache correctly:
		HRESULT hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
	if( FAILED(hResult)){
	  return hResult;
	}
	FreeGlyphPositionsForSession(*psc);
//	WRAP_END_NO_RETURN
	}

	GlyphPositions * pGlyphPositions = GetGlyphPositions(*psc, psa);
  if(pGlyphPositions && pGlyphPositions->advanceWidths.size() != static_cast<size_t>(cGlyphs)){
	  __asm { int 3} // debug break
  }

	if(pGlyphPositions &&  pGlyphPositions->advanceWidths.size() == static_cast<size_t>(cGlyphs))
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
