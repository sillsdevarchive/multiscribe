//#include "../stdafx.h"
//#include "../GraphiteScriptStringAnalysis.h"
#pragma comment(linker, "/export:ScriptStringAnalyse=_usp10.ScriptStringAnalyse")

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

///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptStringAnalyse
//#pragma comment(linker, "/export:ScriptStringAnalyse=_usp10.ScriptStringAnalyse")
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSTRINGANALYSE)(
//    HDC                                             hdc,        //In  Device context (required)
//    const void                                      *pString,   //In  String in 8 or 16 bit characters
//    int                                             cString,    //In  Length in characters (Must be at least 1)
//    int                                             cGlyphs,    //In  Required glyph buffer size (default cString*1.5 + 16)
//    int                                             iCharset,   //In  Charset if an ANSI string, -1 for a Unicode string
//    DWORD                                           dwFlags,    //In  Analysis required
//    int                                             iReqWidth,  //In  Required width for fit and/or clip
//    __in_ecount_opt(1) SCRIPT_CONTROL               *psControl, //In  Analysis control (optional)
//    __in_ecount_opt(1) SCRIPT_STATE                 *psState,   //In  Analysis initial state (optional)
//    __in_ecount_opt(cString) const int              *piDx,      //In  Requested logical dx array
//    __in_ecount_opt(1) SCRIPT_TABDEF                *pTabdef,   //In  Tab positions (optional)
//    const BYTE                                      *pbInClass, //In  Legacy GetCharacterPlacement character classifications (deprecated)
//    __deref_out_ecount(1) SCRIPT_STRING_ANALYSIS    *pssa);     //Out Analysis of string
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringAnalyse(
//    HDC                                             hdc,        //In  Device context (required)
//	//If dwFlags is SSA_GLYPH, the hdc is required. If dwFlags is SSA_BREAK, the hdc is optional.
//    const void                                      *pString,   //In  String in 8 or 16 bit characters
//    int                                             cString,    //In  Length in characters (Must be at least 1)
//    int                                             cGlyphs,    //In  Required glyph buffer size (default cString*1.5 + 16)
//    int                                             iCharset,   //In  Charset if an ANSI string, -1 for a Unicode string
//    DWORD                                           dwFlags,    //In  Analysis required
//    int                                             iReqWidth,  //In  Required width for fit and/or clip
//    __in_ecount_opt(1) SCRIPT_CONTROL               *psControl, //In  Analysis control (optional)
//    __in_ecount_opt(1) SCRIPT_STATE                 *psState,   //In  Analysis initial state (optional)
//    __in_ecount_opt(cString) const int              *piDx,      //In  Requested logical dx array
//    __in_ecount_opt(1) SCRIPT_TABDEF                *pTabdef,   //In  Tab positions (optional)
//    const BYTE                                      *pbInClass, //In  Legacy GetCharacterPlacement character classifications (deprecated)
//    __deref_out_ecount(1) SCRIPT_STRING_ANALYSIS    *pssa)     //Out Analysis of string
//{
//	WRAP_BEGIN(ScriptStringAnalyse, LPFNSCRIPTSTRINGANALYSE)
//	hResult = ScriptStringAnalyse(hdc,pString,cString,cGlyphs,iCharset,dwFlags,iReqWidth,psControl,psState,piDx,pTabdef,pbInClass,pssa);
//
//	if(hResult == S_OK && hdc && IsGraphiteFont(hdc))
//	{
//		GRAPHITE_SCRIPT_STRING_ANALYSIS * pgssa = CreateGraphiteScriptStringAnalysis(*pssa);
//		assert(pgssa != NULL);
//		if(pgssa == NULL){
//			return E_FAIL;
//		}
//		pgssa->hdc = hdc;
//
//		// Create the Graphite font object.
//		pgssa->pFont = new gr::WinFont(hdc);
//
//		// Create the segment.
//		pgssa->pLayout = new gr::LayoutEnvironment();	// use all the defaults...
//		pgssa->pLayout->setDumbFallback(true);	// except that we want it to try its best, no matter what
//
//		const WCHAR* buffer = NULL;
//		int size = 0;
//		if(iCharset == -1) { //already unicode
//			buffer = reinterpret_cast<const WCHAR*>(pString);
//			size = cString;
//		}
//		else { // needs to be converted to unicode
//			size = MultiByteToWideChar(iCharset, 0, reinterpret_cast<LPCSTR>(pString), cString, NULL, 0);
//			if (size > 0) { // function failed
//				buffer = new WCHAR[size+1];
//				size = MultiByteToWideChar(iCharset, 0, reinterpret_cast<LPCSTR>(pString), cString, NULL, 0);
//				if(size == 0){
//					delete[] buffer;
//					buffer = NULL;
//				}
//			}
//		}
//
//		if(buffer){
//			pgssa->textSource = TextSource(buffer, size);
//			pgssa->pSegment = new gr::RangeSegment(pgssa->pFont, &pgssa->textSource, pgssa->pLayout);
//			if(iCharset != -1){
//				delete [] buffer; // had to allocate space for the conversion
//			}
//		}
//		else {
//			delete pgssa->pFont;
//			delete pgssa->pLayout;
//			FreeGraphiteScriptStringAnalysis(*pssa);
//		}
//	}
//
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
