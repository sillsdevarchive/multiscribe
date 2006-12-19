//#include "../stdafx.h"
//int GetGraphiteScriptId();
//SCRIPT_PROPERTIES * GetScriptPropertiesOfEngine(int i);

#pragma comment(linker, "/export:ScriptItemize=_usp10.ScriptItemize")

////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptItemize
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTITEMIZE) (
//    __in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
//    int                                                 cInChars,       // In   Codepoint count to itemize
//    int                                                 cMaxItems,      // In   Max length of itemization array
//    __in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
//    __in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
//    __out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
//    __out_ecount(1) int                                 *pcItems);      // Out  Count of items processed (optional)
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptItemize(
//    __in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
//    int                                                 cInChars,       // In   Codepoint count to itemize
//    int                                                 cMaxItems,      // In   Max length of itemization array
//    __in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
//    __in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
//    __out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
//    __out_ecount(1) int                                 *pcItems)      // Out  Count of items processed (optional)
//{
//	WRAP_BEGIN(ScriptItemize, LPFNSCRIPTITEMIZE)
//	hResult = ScriptItemize(pwcInChars, cInChars, cMaxItems, psControl, psState, pItems, pcItems);
//	//need to make sure SCRIPT_ITEM.SCRIPT_ANALYSIS.eScript initialized to
//	// be a complex script if we are going to get called.
//	//for(int i=0; i < *pcItems; ++i){
//	//	SCRIPT_PROPERTIES * sp = GetScriptPropertiesOfEngine(pItems[i].a.eScript);
//	//	if (sp->langid != SCRIPT_UNDEFINED &&
//	//		!sp->fComplex){
//	//		pItems[i].a.eScript = GetGraphiteScriptId();
//	//	}
//	//}
//	WRAP_END
//}
//
//#ifdef __cplusplus
//}
//#endif
