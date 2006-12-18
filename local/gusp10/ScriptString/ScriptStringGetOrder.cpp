#include "../stdafx.h"
#include "../GraphiteScriptStringAnalysis.h"
//#pragma comment(linker, "/export:ScriptStringGetOrder=_usp10.ScriptStringGetOrder")

/////   ScriptStringGetOrder
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGGETORDER)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	UINT                                    *puOrder);

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringGetOrder(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,
	UINT                                    *puOrder)
{
	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
	if(pgssa){
	}
	else{
	}
	WRAP_BEGIN(ScriptStringGetOrder, LPFNSCRIPTSTRINGGETORDER)
	hResult = ScriptStringGetOrder(ssa, puOrder);
	WRAP_END
}
#ifdef __cplusplus
}
#endif
