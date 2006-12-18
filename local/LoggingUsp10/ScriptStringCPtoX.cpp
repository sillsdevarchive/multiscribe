#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringCPtoX=_usp10.ScriptStringCPtoX")

/////   ScriptStringCPtoX
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGCPTOX)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,        //In  String analysis
	int                                     icp,        //In  Caret character position
	BOOL                                    fTrailing,  //In  Which edge of icp
	__out_ecount(1) int                     *pX);       //Out Corresponding x offset


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringCPtoX(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,        //In  String analysis
	int                                     icp,        //In  Caret character position
	BOOL                                    fTrailing,  //In  Which edge of icp
	__out_ecount(1) int                     *pX)       //Out Corresponding x offset
{
	WRAP_BEGIN(ScriptStringCPtoX, LPFNSCRIPTSTRINGCPTOX)
	LOG(L"<ScriptStringCPtoX>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"<character position='%d' type='%s'/>", icp, (fTrailing)? L"Trailing" : L"Leading");
	LOG(L"</in>");
	hResult = ScriptStringCPtoX(ssa, icp, fTrailing, pX);
	LOG(L"<out>");
	LOG(L"<x>%d</x>", *pX);
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptStringCPtoX>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
