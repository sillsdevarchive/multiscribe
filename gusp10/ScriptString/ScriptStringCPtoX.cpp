//#include "../stdafx.h"
//#include "../GraphiteScriptStringAnalysis.h"
//#include <math.h>

#pragma comment(linker, "/export:ScriptStringCPtoX=_usp10.ScriptStringCPtoX")

/////   ScriptStringCPtoX
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGCPTOX)(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,        //In  String analysis
//    int                                     icp,        //In  Caret character position
//    BOOL                                    fTrailing,  //In  Which edge of icp
//    __out_ecount(1) int                     *pX);       //Out Corresponding x offset
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringCPtoX(
//    __in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,        //In  String analysis
//    int                                     icp,        //In  Caret character position
//    BOOL                                    fTrailing,  //In  Which edge of icp
//    __out_ecount(1) int                     *pX)       //Out Corresponding x offset
//{
//	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
//
//	if(pgssa){
//		// hack to force the segment to compute the dimensions and avoid an assertion in painter.positionsOfIP
//		pgssa->pSegment->advanceWidth();
//		gr::WinSegmentPainter painter(pgssa->pSegment, pgssa->hdc);
//		gr::Rect PrimaryInsertionPoint;
//		gr::Rect SecondaryInsertionPoint;
//		painter.positionsOfIP(icp, fTrailing, false, &PrimaryInsertionPoint, &SecondaryInsertionPoint);
//		// looks like I want the mid point of the IP rectangle.
//		*pX = static_cast<int>(ceil((PrimaryInsertionPoint.left + PrimaryInsertionPoint.right) / 2));
//		return S_OK;
//	}
//	else{
//		WRAP_BEGIN(ScriptStringCPtoX, LPFNSCRIPTSTRINGCPTOX)
//		hResult = ScriptStringCPtoX(ssa, icp, fTrailing, pX);
//		WRAP_END
//	}
//}
//#ifdef __cplusplus
//}
//#endif
