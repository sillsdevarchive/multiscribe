#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringXtoCP=_usp10.ScriptStringXtoCP")

/////   ScriptStringXtoCP
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGXTOCP)(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            // In
	int                                     iX,             // In
	__out_ecount(1) int                     *piCh,          // Out
	__out_ecount(1) int                     *piTrailing);   // Out


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringXtoCP(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            // In
	int                                     iX,             // In
	__out_ecount(1) int                     *piCh,          // Out
	__out_ecount(1) int                     *piTrailing)   // Out
{
	WRAP_BEGIN(ScriptStringXtoCP, LPFNSCRIPTSTRINGXTOCP)
	LOG(L"<ScriptStringXtoCP>");
	LOG(L"<in>");
	LogScriptStringAnalysis(ssa);
	LOG(L"<x>%d</x>", iX);
	LOG(L"</in>");
	hResult = ScriptStringXtoCP(ssa, iX, piCh, piTrailing);
	LOG(L"<out>");
	LOG(L"<character position='%d' type='%s'/>", *piCh, (*piTrailing)? L"Trailing" : L"Leading");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptStringXtoCP>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
