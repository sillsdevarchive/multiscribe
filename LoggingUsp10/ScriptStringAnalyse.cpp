#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptStringAnalyse=_usp10.ScriptStringAnalyse")

//   ScriptStringAnalyse
//
// Analyses plain text. It corresponds to the following functions:
//		ScriptItemize
//		ScriptShape
//		ScriptPlace
//		ScriptBreak
//		ScriptGetCMap
//		ScriptJustify
//		ScriptLayout


// from Wine
typedef struct
{
	int     cGlyphs;
	SCRIPT_VISATTR *psva;
	int     *piAdvance;
	ABC     pABC;
	WORD    *pwLogClust;
	GOFFSET *pGoffset;
	WORD    *pwOutGlyphs;
} SCRIPT_STRING_SCRIPT_BLOCK;

typedef struct {
	HDC     hdc;			// Device context
	int     cItems;
	int     cMaxGlyphs;
	SCRIPT_STRING_SCRIPT_BLOCK *script_blk;
	SCRIPT_ITEM *pItem;
	long    p[10];
} CLEAR_SCRIPT_STRING_ANALYSIS;

///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptStringAnalyse
//#pragma comment(linker, "/export:ScriptStringAnalyse=_usp10.ScriptStringAnalyse")
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGANALYSE)(
	HDC                                             hdc,        //In  Device context (required)
	const void                                      *pString,   //In  String in 8 or 16 bit characters
	int                                             cString,    //In  Length in characters (Must be at least 1)
	int                                             cGlyphs,    //In  Required glyph buffer size (default cString*1.5 + 16)
	int                                             iCharset,   //In  Charset if an ANSI string, -1 for a Unicode string
	DWORD                                           dwFlags,    //In  Analysis required
	int                                             iReqWidth,  //In  Required width for fit and/or clip
	__in_ecount_opt(1) SCRIPT_CONTROL               *psControl, //In  Analysis control (optional)
	__in_ecount_opt(1) SCRIPT_STATE                 *psState,   //In  Analysis initial state (optional)
	__in_ecount_opt(cString) const int              *piDx,      //In  Requested logical dx array
	__in_ecount_opt(1) SCRIPT_TABDEF                *pTabdef,   //In  Tab positions (optional)
	const BYTE                                      *pbInClass, //In  Legacy GetCharacterPlacement character classifications (deprecated)
	__deref_out_ecount(1) SCRIPT_STRING_ANALYSIS    *pssa);     //Out Analysis of string

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptStringAnalyse(
	HDC                                             hdc,        //In  Device context (required)
	const void                                      *pString,   //In  String in 8 or 16 bit characters
	int                                             cString,    //In  Length in characters (Must be at least 1)
	int                                             cGlyphs,    //In  Required glyph buffer size (default cString*1.5 + 16)
	int                                             iCharset,   //In  Charset if an ANSI string, -1 for a Unicode string
	DWORD                                           dwFlags,    //In  Analysis required
	int                                             iReqWidth,  //In  Required width for fit and/or clip
	__in_ecount_opt(1) SCRIPT_CONTROL               *psControl, //In  Analysis control (optional)
	__in_ecount_opt(1) SCRIPT_STATE                 *psState,   //In  Analysis initial state (optional)
	__in_ecount_opt(cString) const int              *piDx,      //In  Requested logical dx array
	__in_ecount_opt(1) SCRIPT_TABDEF                *pTabdef,   //In  Tab positions (optional)
	const BYTE                                      *pbInClass, //In  Legacy GetCharacterPlacement character classifications (deprecated)
	__deref_out_ecount(1) SCRIPT_STRING_ANALYSIS    *pssa)     //Out Analysis of string
{
	WRAP_BEGIN(ScriptStringAnalyse, LPFNSCRIPTSTRINGANALYSE)
	LOG(L"<ScriptStringAnalyse>");
	LOG(L"<in>");
	LOG(L"<hdc>%d</hdc>", hdc);
	if(iCharset == -1){
		LogString(reinterpret_cast<const WCHAR*>(pString), cString);
	}
	else{
		LOG(L"<string size='%d' charset='%d'><![CDATA[%S]]></string>", cString, iCharset, pString);
	}
	LOG(L"<glyphs count='%d'/>", cGlyphs);
	LOG(L"<flags>");
	if(dwFlags & SSA_BREAK){
		LOG(L"<break/>");
	}
	if(dwFlags & SSA_CLIP){
		LOG(L"<clip/>");
	}
	if(dwFlags & SSA_DZWG){
		LOG(L"<dzwg/>");
	}
	if(dwFlags & SSA_FALLBACK){
		LOG(L"<fallback/>");
	}
	if(dwFlags & SSA_FIT){
		LOG(L"<fit/>");
	}
	if(dwFlags & SSA_GLYPHS){
		LOG(L"<glyphs/>");
	}
	if(dwFlags & SSA_GCP){
		LOG(L"<gcp/>");
	}
	if(dwFlags & SSA_HIDEHOTKEY){
		LOG(L"<hidehotkey/>");
	}
	if(dwFlags & SSA_HOTKEY){
		LOG(L"<hotkey/>");
	}
	if(dwFlags & SSA_HOTKEYONLY){
		LOG(L"<hotkeyonly/>");
	}
	if(dwFlags & SSA_LINK){
		LOG(L"<link/>");
	}
	if(dwFlags & SSA_METAFILE){
		LOG(L"<metafile/>");
	}
	if(dwFlags & SSA_PASSWORD){
		LOG(L"<password/>");
	}
	if(dwFlags & SSA_RTL){
		LOG(L"<rtl/>");
	}
	if(dwFlags & SSA_TAB){
		LOG(L"<tab/>");
	}

	LOG(L"</flags>");
	LOG(L"<RequiredWidth>%d</RequiredWidth>", iReqWidth);
	if(psControl){
		LogScriptControl(psControl);
	}
	if(psState){
		LogScriptState(psState);
	}
	if(piDx){
		LOG(L"<offsets>");
		for(int i=0; i<cString; ++i){
			LOG(L"<x>%d</x>", piDx[i]);
		}
		LOG(L"</offsets>");
	}
	LOG(L"</in>");
	hResult = ScriptStringAnalyse(hdc,pString,cString,cGlyphs,iCharset,dwFlags,iReqWidth,psControl,psState,piDx,pTabdef,pbInClass,pssa);
	LOG(L"<out>");
	LogScriptStringAnalysis(*pssa);
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptStringAnalyse>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
