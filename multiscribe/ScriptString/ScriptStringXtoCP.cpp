#include "../stdafx.h"

//#include "../GraphiteScriptStringAnalysis.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptStringXtoCP=" USP10DLL ".ScriptStringXtoCP")
#endif

/////   ScriptStringXtoCP
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGXTOCP)(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            // In
//    int                                     iX,             // In
//    __out_ecount(1) int                     *piCh,          // Out
//    __out_ecount(1) int                     *piTrailing);   // Out
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringXtoCP(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            // In
//    int                                     iX,             // In
//    __out_ecount(1) int                     *piCh,          // Out
//    __out_ecount(1) int                     *piTrailing)   // Out
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//	if(pgssa){
//		gr::WinSegmentPainter painter(pgssa->pSegment, pgssa->hdc);
//		POINT point;
//		point.x = iX;
//		point.y = 0;
//		bool fTrailing;
//		painter.pointToChar(point, piCh, &fTrailing);
//		*piTrailing = fTrailing;
//		return S_OK;
//	}
//	else{
//		WRAP_BEGIN(ScriptStringXtoCP, LPFNSCRIPTSTRINGXTOCP)
//		hResult = ScriptStringXtoCP(ssa, iX, piCh, piTrailing);
//		WRAP_END
//	}
//}
//#ifdef __cplusplus
//}
//#endif
