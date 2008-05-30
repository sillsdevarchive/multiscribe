#include "../stdafx.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptCPtoX=" USP10DLL ".ScriptCPtoX")
#endif

///////   ScriptCPtoX
//#ifdef __cplusplus
//extern "C" {
//#endif
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTCPTOX)(
//    int                                         iCP,            // In   Logical character position in run
//    BOOL                                        fTrailing,      // In   Which edge (default - leading)
//    int                                         cChars,         // In   Count of logical codepoints in run
//    int                                         cGlyphs,        // In   Count of glyphs in run
//    __in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes array
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
//    int                                         *piX);          // Out  Resulting X position
//
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptCPtoX(
//    int                                         iCP,            // In   Logical character position in run
//    BOOL                                        fTrailing,      // In   Which edge (default - leading)
//    int                                         cChars,         // In   Count of logical codepoints in run
//    int                                         cGlyphs,        // In   Count of glyphs in run
//    __in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes array
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
//    int                                         *piX)          // Out  Resulting X position
//{
//	WRAP_BEGIN(ScriptCPtoX, LPFNSCRIPTCPTOX)
//	hResult = ScriptCPtoX(iCP, fTrailing, cChars, cGlyphs, pwLogClust, psva, piAdvance, psa, piX);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
