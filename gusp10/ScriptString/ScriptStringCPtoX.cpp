#include "../stdafx.h"
#include "../GraphiteScriptStringAnalysis.h"
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

__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringCPtoX(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,        //In  String analysis
	int                                     icp,        //In  Caret character position
	BOOL                                    fTrailing,  //In  Which edge of icp
	__out_ecount(1) int                     *pX)       //Out Corresponding x offset
{
	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);

	if(pgssa){
	}
	else{
	}
	WRAP_BEGIN(ScriptStringCPtoX, LPFNSCRIPTSTRINGCPTOX)
	hResult = ScriptStringCPtoX(ssa, icp, fTrailing, pX);
	*pX = 100;
	WRAP_END
}
#ifdef __cplusplus
}
#endif
