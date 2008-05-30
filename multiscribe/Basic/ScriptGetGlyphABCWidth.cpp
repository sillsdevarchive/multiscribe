#include "../stdafx.h"
#pragma comment(linker, "/export:ScriptGetGlyphABCWidth=" USP10DLL ".ScriptGetGlyphABCWidth")

///////   ScriptGetGlyphABCWidth
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETGLYPHABCWIDTH) (
//    HDC                                     hdc,        // In    Optional (see notes on caching)
//    __deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
//    WORD                                    wGlyph,     // In    Glyph
//    __out_ecount(1) ABC                     *pABC);    // Out   ABC width
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetGlyphABCWidth(
//    HDC                                     hdc,        // In    Optional (see notes on caching)
//    __deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
//    WORD                                    wGlyph,     // In    Glyph
//    __out_ecount(1) ABC                     *pABC)     // Out   ABC width
//{
//	WRAP_BEGIN(ScriptGetGlyphABCWidth, LPFNSCRIPTGETGLYPHABCWIDTH)
//	hResult = ScriptGetGlyphABCWidth(hdc,psc,wGlyph,pABC);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
