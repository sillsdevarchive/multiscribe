#include "stdafx.h"
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

__checkReturn HRESULT WINAPI LoggingScriptPlace(
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
	WRAP_BEGIN(ScriptPlace, LPFNSCRIPTPLACE)
	LOG(L"<ScriptPlace>");
	if(hdc){
		LOG(L"<hdc>%d</hdc>", hdc);
	}
	LogScriptCache(psc);
	LOG(L"<Glyphs count='%d'>", cGlyphs);
	for(int i=0; i<cGlyphs;++i){
		LOG(L"<Glyph hex='%04x'>", pwGlyphs[i]);
		LogScriptVisualAttributes(&psva[i]);
		LOG(L"</Glyph>");
	}
	LOG(L"</Glyphs>");
	LogScriptAnalysis(psa);
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptPlace(hdc, psc, pwGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, pABC);
	LOG(L"<out>");
	LogScriptAnalysis(psa);
	LOG(L"<Glyphs count='%d'>", cGlyphs);
	for(int i=0; i<cGlyphs;++i){
		LOG(L"<Glyph hex='%04x' advance='%d' xOffset='%d' yOffset='%d'/>", pwGlyphs[i], piAdvance[i], pGoffset[i].du, pGoffset[i].dv);
	}
	LOG(L"</Glyphs>");
	if(pABC)
	{
		LogABC(pABC);
	}
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptPlace>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
