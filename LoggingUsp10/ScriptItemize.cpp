#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptItemize=_usp10.ScriptItemize")


////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptItemize
//#pragma comment(linker, "/export:ScriptItemize=_usp10.ScriptItemize")

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTITEMIZE) (
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	int                                                 cInChars,       // In   Codepoint count to itemize
	int                                                 cMaxItems,      // In   Max length of itemization array
	__in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
	__in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount(1) int                                 *pcItems);      // Out  Count of items processed (optional)

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptItemize(
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	int                                                 cInChars,       // In   Codepoint count to itemize
	int                                                 cMaxItems,      // In   Max length of itemization array
	__in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
	__in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount(1) int                                 *pcItems)      // Out  Count of items processed (optional)
{
	WRAP_BEGIN(ScriptItemize, LPFNSCRIPTITEMIZE)
	LOG(L"<ScriptItemize>");
	LOG(L"<in>");
	LogString(pwcInChars, cInChars);
	LOG(L"<MaxItems>%d</MaxItems>", cMaxItems);
	if(psControl){
		LogScriptControl(psControl);
	}
	if(psState){
		LogScriptState(psState);
	}
	LOG(L"</in>");

	WCHAR* s = new WCHAR[cInChars];
  if(pwcInChars != NULL){
	for(int i = 0; i < cInChars; ++i){
	  WCHAR w = pwcInChars[i];
	  if(0x07C0 <= w && w <= 0x07ff) { //N'Ko
		  w = L'س'; // fool it into thinking we're arabic!
	  }
	  s[i] = w;
	}
  }


	hResult = ScriptItemize(s/*pwcInChars*/, cInChars, cMaxItems, psControl, psState, pItems, pcItems);
  delete[] s;

  LOG(L"<out>");
	for(int i= 0; i<*pcItems; ++i){
		LogScriptItem(&pItems[i]);
	}
	LogHResult(hResult);
	LOG(L"</out>");

	LOG(L"</ScriptItemize>");
	WRAP_END
}

#ifdef __cplusplus
}
#endif
