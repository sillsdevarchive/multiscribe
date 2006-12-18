#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptApplyDigitSubstitution=_usp10.ScriptApplyDigitSubstitution")

// ScriptApplyDigitSubstitution
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTAPPLYDIGITSUBSTITUTION)(
	__in_ecount(1) const SCRIPT_DIGITSUBSTITUTE *psds,  // In   Digit substitution settings
	__out_ecount(1) SCRIPT_CONTROL              *psc,   // Out  Script control structure
	__out_ecount(1) SCRIPT_STATE                *pss);  // Out  Script state structure



#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptApplyDigitSubstitution(
	__in_ecount(1) const SCRIPT_DIGITSUBSTITUTE *psds,  // In   Digit substitution settings
	__out_ecount(1) SCRIPT_CONTROL              *psc,   // Out  Script control structure
	__out_ecount(1) SCRIPT_STATE                *pss)  // Out  Script state structure
{
	WRAP_BEGIN(ScriptApplyDigitSubstitution, LPFNSCRIPTAPPLYDIGITSUBSTITUTION)
	LOG(L"<ScriptApplyDigitSubstitution>");
	LOG(L"<in>");
	LogDigitSubstitution(psds);
	LOG(L"</in>");
	hResult = ScriptApplyDigitSubstitution(psds, psc, pss);
	LOG(L"<out>");
	LogScriptControl(psc);
	LogScriptState(pss);
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptApplyDigitSubstitution>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
