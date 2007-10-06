#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptTextOut=_usp10.ScriptTextOut")

///////////////////////////////////////////////////////////////////////////////////////////////////
///// ScriptTextOut
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTTEXTOUT) (
	const HDC                               hdc,            // In     OS handle to device context (required)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut  Cache handle
	int                                     x,              // In     x,y position for first glyph
	int                                     y,              // In
	UINT                                    fuOptions,      // In     ExtTextOut options
	__in_ecount_opt(1) const RECT           *lprc,          // In     optional clipping/opaquing rectangle
	__in_ecount(1) const SCRIPT_ANALYSIS    *psa,           // In     Result of ScriptItemize
	__reserved const WCHAR                  *pwcReserved,   // In     Reserved (requires NULL)
	__reserved int                          iReserved,      // In     Reserved (requires 0)
	__in_ecount(cGlyphs) const WORD         *pwGlyphs,      // In     Glyph buffer from prior ScriptShape call
	int                                     cGlyphs,        // In     Number of glyphs
	__in_ecount(cGlyphs) const int          *piAdvance,     // In     Advance widths from ScriptPlace
	__in_ecount_opt(cGlyphs) const int      *piJustify,     // In     Justified advance widths (optional)
	__in_ecount(cGlyphs) const GOFFSET      *pGoffset);     // In     x,y offset for combining glyph

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptTextOut(
	const HDC                               hdc,            // In     OS handle to device context (required)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut  Cache handle
	int                                     x,              // In     x,y position for first glyph
	int                                     y,              // In
	UINT                                    fuOptions,      // In     ExtTextOut options
	__in_ecount_opt(1) const RECT           *lprc,          // In     optional clipping/opaquing rectangle
	__in_ecount(1) const SCRIPT_ANALYSIS    *psa,           // In     Result of ScriptItemize
	__reserved const WCHAR                  *pwcReserved,   // In     Reserved (requires NULL)
	__reserved int                          iReserved,      // In     Reserved (requires 0)
	__in_ecount(cGlyphs) const WORD         *pwGlyphs,      // In     Glyph buffer from prior ScriptShape call
	int                                     cGlyphs,        // In     Number of glyphs
	__in_ecount(cGlyphs) const int          *piAdvance,     // In     Advance widths from ScriptPlace
	__in_ecount_opt(cGlyphs) const int      *piJustify,     // In     Justified advance widths (optional)
	__in_ecount(cGlyphs) const GOFFSET      *pGoffset)     // In     x,y offset for combining glyph
{
	WRAP_BEGIN(ScriptTextOut, LPFNSCRIPTTEXTOUT)
	LOG(L"<ScriptTextOut>");
	LOG(L"<in>");
  LogHdc(hdc);
	LogScriptCache(psc);
	LOG(L"<Position x='%d' y='%d'/>", x, y);
	LogExtTextOutOptions(fuOptions);
	if(lprc){
		LOG(L"<Rectangle left='%d' top='%d' right='%d' bottom='%d'/>", lprc->left, lprc->top, lprc->right, lprc->bottom);
	}
	LogScriptAnalysis(psa);
	if(pwcReserved){
		LOG(L"<ReservedString/>");
	}
	if(iReserved){
		LOG(L"<Reserved>%d</Reserved>", iReserved);
	}
	LOG(L"<Glyphs count='%d'>", cGlyphs);
	for(int i=0; i<cGlyphs; ++i){
		if(piJustify){
			LOG(L"<Glyph hex='%04x' advance='%d' justify='%d' xOffset='%d' yOffset='%d'/>", pwGlyphs[i], piAdvance[i], piJustify[i], pGoffset[i].du, pGoffset[i].dv);
		}
		else{
			LOG(L"<Glyph hex='%04x' advance='%d' xOffset='%d' yOffset='%d'/>", pwGlyphs[i], piAdvance[i], pGoffset[i].du, pGoffset[i].dv);
		}
	}
	LOG(L"</Glyphs>");


	LOG(L"</in>");
	hResult = ScriptTextOut(hdc,psc,x,y,fuOptions,lprc,psa,pwcReserved,iReserved,pwGlyphs,cGlyphs,piAdvance,piJustify,pGoffset);
	LOG(L"</ScriptTextOut>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
