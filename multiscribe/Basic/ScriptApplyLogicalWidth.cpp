#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptApplyLogicalWidth=" USP10DLL ".ScriptApplyLogicalWidth")
#endif

///////   ScriptApplyLogicalWidth
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTAPPLYLOGICALWIDTH)(
//    __in_ecount(cChars) const int               *piDx,          // In     Logical dx array to apply
//    int                                         cChars,         // In     Count of logical codepoints in run
//    int                                         cGlyphs,        // In     Glyph count
//    __in_ecount(cChars) const WORD              *pwLogClust,    // In     Logical clusters
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In     Visual attributes from ScriptShape/Place
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In     Glyph advance widths from ScriptPlace
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In     Script analysis from item attributes
//    __inout_ecount_opt(1) ABC                   *pABC,          // InOut  Updated item ABC width (optional)
//	__out_ecount_full(cGlyphs) int              *piJustify);    // Out    Resulting glyph advance widths for ScriptTextOut
//
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptApplyLogicalWidth(
//    __in_ecount(cChars) const int               *piDx,          // In     Logical dx array to apply
//    int                                         cChars,         // In     Count of logical codepoints in run
//    int                                         cGlyphs,        // In     Glyph count
//    __in_ecount(cChars) const WORD              *pwLogClust,    // In     Logical clusters
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In     Visual attributes from ScriptShape/Place
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In     Glyph advance widths from ScriptPlace
//    __in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In     Script analysis from item attributes
//    __inout_ecount_opt(1) ABC                   *pABC,          // InOut  Updated item ABC width (optional)
//	__out_ecount_full(cGlyphs) int              *piJustify)    // Out    Resulting glyph advance widths for ScriptTextOut
//{
//	WRAP_BEGIN(ScriptApplyLogicalWidth, LPFNSCRIPTAPPLYLOGICALWIDTH)
//	hResult = ScriptApplyLogicalWidth(piDx,cChars,cGlyphs,pwLogClust,psva,piAdvance,psa,pABC,piJustify);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
