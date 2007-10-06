#pragma comment(linker, "/export:ScriptTextOut=_usp10.ScriptTextOut")

#include "../stdafx.h"
LPVOID GetOriginalScriptTextOut();

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

//#ifdef __cplusplus
//extern "C" {
//#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptTextOut(
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
//	WRAP_BEGIN(ScriptTextOut, LPFNSCRIPTTEXTOUT)

  LPFNSCRIPTTEXTOUT ScriptTextOut = (LPFNSCRIPTTEXTOUT) GetOriginalScriptTextOut();
#if _DEBUG
#define COLORIZED
#endif

#if defined(COLORIZED)
	COLORREF OriginalColor;
#endif

	if(IsGraphiteFont(hdc))
	{
	const_cast<SCRIPT_ANALYSIS *>(psa)->eScript = SCRIPT_UNDEFINED; // it seems that the script engine's text out may be trying to do special things especially in the case of arabic

#if defined(COLORIZED)
		OriginalColor = SetTextColor(hdc, RGB(0,128,0));
#endif
  }
#if defined(COLORIZED)
	else
	{
		OriginalColor = SetTextColor(hdc, RGB(0,255,0));
	}
#endif

HRESULT	hResult = ScriptTextOut(hdc,psc,x,y,fuOptions,lprc,psa,pwcReserved,iReserved,pwGlyphs,cGlyphs,piAdvance,piJustify,pGoffset);

#if defined(COLORIZED)
	SetTextColor(hdc, OriginalColor);
#endif

  return hResult;
//	WRAP_END
}
//#ifdef __cplusplus
//}
//#endif
