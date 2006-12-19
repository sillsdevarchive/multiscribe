//#include "../stdafx.h"
#pragma comment(linker, "/export:ScriptItemizeOpenType=_usp10.ScriptItemizeOpenType")

/// ScriptItemizeOpenType
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTITEMIZEOPENTYPE)(
//    __in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
//    __in                  int                            cInChars,      // In   Codepoint count to itemize
//    __in                  int                            cMaxItems,     // In   Max length of itemization array
//    __in_opt              const SCRIPT_CONTROL          *psControl,     // In   Analysis control (optional)
//    __in_opt              const SCRIPT_STATE            *psState,       // In   Initial bidi algorithm state (optional)
//    __out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
//    __out_ecount_part(cMaxItems, *pcItems) OPENTYPE_TAG *pScriptTags,   // Out  Array of script tags - parallel to items
//    __out                 int                           *pcItems);      // Out  Count of items processed (optional)
//
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptItemizeOpenType(
//    __in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
//    __in                  int                            cInChars,      // In   Codepoint count to itemize
//    __in                  int                            cMaxItems,     // In   Max length of itemization array
//    __in_opt              const SCRIPT_CONTROL          *psControl,     // In   Analysis control (optional)
//    __in_opt              const SCRIPT_STATE            *psState,       // In   Initial bidi algorithm state (optional)
//    __out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
//    __out_ecount_part(cMaxItems, *pcItems) OPENTYPE_TAG *pScriptTags,   // Out  Array of script tags - parallel to items
//    __out                 int                           *pcItems)      // Out  Count of items processed (optional)
//{
//	WRAP_BEGIN(ScriptItemizeOpenType, LPFNSCRIPTITEMIZEOPENTYPE)
//	hResult = ScriptItemizeOpenType(pwcInChars,cInChars,cMaxItems,psControl,psState,pItems,pScriptTags,pcItems);
//	WRAP_END
//
//}
//#ifdef __cplusplus
//}
//#endif
