#pragma comment(linker, "/export:ScriptItemize=_usp10.ScriptItemize")

#ifdef INTERCEPT_SCRIPTITEMIZE

#include "../stdafx.h"
//int GetGraphiteScriptId();
const SCRIPT_PROPERTIES * GetScriptPropertiesOfEngine(int i);
LPVOID GetOriginalScriptItemize();

static WORD eScriptArabic = (WORD)-1;


//////////////////////////////////////////////////////////////////////////////////////
///   ScriptItemize

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTITEMIZE) (
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	int                                                 cInChars,       // In   Codepoint count to itemize
	int                                                 cMaxItems,      // In   Max length of itemization array
	__in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
	__in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount(1) int                                 *pcItems);      // Out  Count of items processed (optional)

//#ifdef __cplusplus
//extern "C" {
//#endif


__checkReturn HRESULT WINAPI GraphiteEnabledScriptItemize(
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	int                                                 cInChars,       // In   Codepoint count to itemize
	int                                                 cMaxItems,      // In   Max length of itemization array
	__in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
	__in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount(1) int                                 *pcItems)      // Out  Count of items processed (optional)
{
	//WRAP_BEGIN(ScriptItemize, LPFNSCRIPTITEMIZE)
  LPFNSCRIPTITEMIZE ScriptItemize = (LPFNSCRIPTITEMIZE) GetOriginalScriptItemize();
  const WCHAR* s = pwcInChars;

  //WCHAR* s = new WCHAR[cInChars];
  //if(pwcInChars != NULL){
  //  for(int i = 0; i < cInChars; ++i){
  //    WCHAR w = pwcInChars[i];
  //    if(0x07C0 <= w && w <= 0x07ff) { //N'Ko
  //        w = L'س'; // fool it into thinking we're arabic!
  //    }
  //    s[i] = w;
  //  }
  //}

	HRESULT hResult = ScriptItemize(s, cInChars, cMaxItems, psControl, psState, pItems, pcItems);
 // delete[] s;
	//need to make sure SCRIPT_ITEM.SCRIPT_ANALYSIS.eScript initialized to
	// be a complex script if we are going to get called.
	//for(int i=0; i < *pcItems; ++i){
	//	SCRIPT_PROPERTIES * sp = GetScriptPropertiesOfEngine(pItems[i].a.eScript);
	//	if (sp->langid != SCRIPT_UNDEFINED &&
	//		!sp->fComplex){
	//		pItems[i].a.eScript = GetGraphiteScriptId();
	//	}
	//}
	//WRAP_END
	//}

  //bool fNko=false;
  //for(int i = 0; i < *pcItems; ++i){
  //  WCHAR startChar = pwcInChars[pItems[i].iCharPos];
  //  if(0x07C0 <= startChar && startChar <= 0x07ff) { //N'Ko
  //    if(eScriptArabic == -1){
  //      SCRIPT_ITEM rgItems[2];
  //      int cItemsProcessed=0;
  //      wchar_t arabic = L'س';
  //      HRESULT hResult = ScriptItemize(&arabic, 1, 2, NULL, NULL, (SCRIPT_ITEM*)&rgItems, &cItemsProcessed);
  //      if(hResult==S_OK){
  //        eScriptArabic = rgItems[0].a.eScript;
  //      }
  //    }
  //    pItems[i].a.fRTL = true;
  //    pItems[i].a.fLayoutRTL = true;
  //    pItems[i].a.s.uBidiLevel = 1;
  //    fNko = true;
  //    if(eScriptArabic != -1){
  //     // pItems[i].a.eScript = eScriptArabic; // fool it into thinking we're arabic!
  //    }
  //  }
//       const SCRIPT_PROPERTIES * sp = GetScriptPropertiesOfEngine(pItems[i].a.eScript);
//assert(sp);
 //}
 // if(fNko){
 //   *pcItems = 1;
 // }
  return hResult;
}

//#ifdef __cplusplus
//}
//#endif


#endif