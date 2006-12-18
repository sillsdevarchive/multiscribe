#include "stdafx.h"
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

__checkReturn HRESULT WINAPI LoggingScriptStringOut(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            //In  Analysis with glyphs
	int                                     iX,             //In
	int                                     iY,             //In
	UINT                                    uOptions,       //In  ExtTextOut options
	__in_ecount_opt(1) const RECT           *prc,           //In  Clipping rectangle (iff ETO_CLIPPED)
	int                                     iMinSel,        //In  Logical selection. Set iMinSel>=iMaxSel for no selection
	int                                     iMaxSel,        //In
	BOOL                                    fDisabled)     //In  If disabled, only the background is highlighted.
{
	WRAP_BEGIN(ScriptStringOut, LPFNSCRIPTSTRINGOUT)
	LOG(L"<ScriptStringOut>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"<Position x='%d' y='%d'/>", iX, iY);
	LogExtTextOutOptions(uOptions);
	if(uOptions & ETO_CLIPPED){
		LOG(L"<ClippingRectangle left='%d' top='%d' right='%d' bottom='%d'/>", prc->left, prc->top, prc->right, prc->bottom);
	}
	if(iMinSel < iMaxSel){
		LOG(L"<LogicalSelection begin='%d' end='%d'/>", iMinSel, iMaxSel);
	}
	if(fDisabled){
		LOG(L"<Disabled/>");
	}
	LOG(L"</in>");
	hResult = ScriptStringOut(ssa, iX,iY, uOptions, prc, iMinSel, iMaxSel, fDisabled);
	LOG(L"</ScriptStringOut>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
