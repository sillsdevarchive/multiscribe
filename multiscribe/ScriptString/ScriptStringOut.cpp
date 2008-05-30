#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptStringOut=" USP10DLL ".ScriptStringOut")
#endif

#ifdef COLORIZE_SCRIPTSTRINGOUT

//#include "../GraphiteScriptStringAnalysis.h"

LPVOID GetOriginalScriptStringOut();

/////////////////////////////////////////////////////////////////////////////////////////////////
///   ScriptStringOut
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGOUT)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            //In  Analysis with glyphs
	int                                     iX,             //In
	int                                     iY,             //In
	UINT                                    uOptions,       //In  ExtTextOut options
	__in_ecount_opt(1) const RECT           *prc,           //In  Clipping rectangle (iff ETO_CLIPPED)
	int                                     iMinSel,        //In  Logical selection. Set iMinSel>=iMaxSel for no selection
	int                                     iMaxSel,        //In
	BOOL                                    fDisabled);     //In  If disabled, only the background is highlighted.

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringOut(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            //In  Analysis with glyphs
	int                                     iX,             //In
	int                                     iY,             //In
	UINT                                    uOptions,       //In  ExtTextOut options
	__in_ecount_opt(1) const RECT           *prc,           //In  Clipping rectangle (iff ETO_CLIPPED)
	int                                     iMinSel,        //In  Logical selection. Set iMinSel>=iMaxSel for no selection
	int                                     iMaxSel,        //In
	BOOL                                    fDisabled)      //In  If disabled, only the background is highlighted.
{
	//GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
	HDC hdc = NULL;
	//if(pgssa){
	//	hdc = pgssa->hdc;
	//	assert(hdc);
	//	if(!hdc){
	//		return E_FAIL;
	//	}
	//	COLORREF OriginalTextColor = GetTextColor(hdc);
	//	COLORREF OriginalBackColor = GetBkColor(hdc);
	//	int OriginalBackMode = GetBkMode(hdc);

	//	if (uOptions & ETO_OPAQUE) {
	//		assert(prc != NULL);
	//		if(prc){
	//			FillRect(hdc, prc, CreateSolidBrush(OriginalBackColor));
	//		}
	//	}

	//	if (uOptions & ETO_CLIPPED){
	//	}

	//	COLORREF textColor;
	//	if(iMinSel < iMaxSel){ //TODO
	//		textColor = (fDisabled)? OriginalTextColor: COLOR_HIGHLIGHTTEXT;
	//	}

	//	pgssa->textSource.setColors(0, gr::kclrBlue, gr::kclrTransparent);

	//	// Draw the segment.
	//	gr::WinSegmentPainter painter(pgssa->pSegment, hdc);
	//	painter.setOrigin(static_cast<float>(iX), static_cast<float>(iY));
	//	painter.paint();
	//	if(iMinSel < iMaxSel){
	//		painter.drawSelectionRange(iMinSel,
	//								   iMaxSel,
	//								   static_cast<float>(iY),
	//								   pgssa->pFont->height()+iY,
	//								   true);
	//	}

	//	SetTextColor(hdc, OriginalTextColor);
	//	SetBkColor(hdc, OriginalBackColor);
	//	SetBkMode(hdc, OriginalBackMode);
	//	return S_OK;
	//}
	//else{
		LPFNSCRIPTSTRINGOUT ScriptStringOut = (LPFNSCRIPTSTRINGOUT) GetOriginalScriptStringOut();

		HDC* phdc = (HDC*) ssa;
		hdc = *phdc;
		COLORREF OriginalTextColor = SetTextColor(hdc, RGB(IsGraphiteFont(hdc)?128:255,0,0));

		hResult = ScriptStringOut(ssa, iX,iY, uOptions, prc, iMinSel, iMaxSel, fDisabled);
		SetTextColor(hdc, OriginalTextColor);
	//}

}
#ifdef __cplusplus
}
#endif
#endif COLORIZED