#include "../stdafx.h"
#include "../GraphiteScriptStringAnalysis.h"
//#pragma comment(linker, "/export:ScriptStringOut=_usp10.ScriptStringOut")

///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptStringOut
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
	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
	HDC hdc = NULL;
	if(pgssa){
		hdc = pgssa->hdc;
		assert(hdc);
		if(!hdc){
			return E_FAIL;
		}
		COLORREF OriginalTextColor = GetTextColor(hdc);
		COLORREF OriginalBackColor = GetBkColor(hdc);
		int OriginalBackMode = GetBkMode(hdc);

		if (uOptions & ETO_OPAQUE) {
			assert(prc != NULL);
			if(prc){
				FillRect(hdc, prc, CreateSolidBrush(OriginalBackColor));
			}
			if(fDisabled){
			}

		}

		if (uOptions & ETO_CLIPPED){
		}

		pgssa->pTextSource->setColors(0, gr::kclrBlue, gr::kclrTransparent);

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, pgssa->pTextSource, &layout);

		// Draw the segment.
		gr::WinSegmentPainter painter(&seg, hdc);
		painter.setOrigin(static_cast<float>(iX), static_cast<float>(iY));
		painter.paint();

		SetTextColor(hdc, OriginalTextColor);
		SetBkColor(hdc, OriginalBackColor);
		SetBkMode(hdc, OriginalBackMode);
		return S_OK;
	}
	else{
		WRAP_BEGIN(ScriptStringOut, LPFNSCRIPTSTRINGOUT)
		CLEAR_SCRIPT_STRING_ANALYSIS* pcssa = (CLEAR_SCRIPT_STRING_ANALYSIS*) ssa;
		hdc = pcssa->hdc;
		COLORREF OriginalTextColor = SetTextColor(hdc, RGB(255,0,0));

		hResult = ScriptStringOut(ssa, iX,iY, uOptions, prc, iMinSel, iMaxSel, fDisabled);
		SetTextColor(hdc, OriginalTextColor);
		WRAP_END
	}

}
#ifdef __cplusplus
}
#endif
