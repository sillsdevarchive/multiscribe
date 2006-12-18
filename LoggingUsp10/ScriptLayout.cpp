#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptLayout=_usp10.ScriptLayout")

/////   ScriptLayout

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTLAYOUT) (
	int                             cRuns,                  // In   Number of runs to process
	__in_ecount(cRuns) const BYTE   *pbLevel,               // In   Array of run embedding levels
	__out_ecount_full_opt(cRuns) int    *piVisualToLogical,     // Out  List of run indices in visual order
	__out_ecount_full_opt(cRuns) int    *piLogicalToVisual);    // Out  List of visual run positions

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptLayout(
	int                             cRuns,                  // In   Number of runs to process
	__in_ecount(cRuns) const BYTE   *pbLevel,               // In   Array of run embedding levels
	__out_ecount_full_opt(cRuns) int    *piVisualToLogical,     // Out  List of run indices in visual order
	__out_ecount_full_opt(cRuns) int    *piLogicalToVisual)    // Out  List of visual run positions
{
	WRAP_BEGIN(ScriptLayout, LPFNSCRIPTLAYOUT)
	LOG(L"<ScriptLayout>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptLayout(cRuns, pbLevel, piVisualToLogical, piLogicalToVisual);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptLayout>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
