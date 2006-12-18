//#include "../stdafx.h"
#pragma comment(linker, "/export:ScriptJustify=_usp10.ScriptJustify")

/////   ScriptJustify
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTJUSTIFY)(
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Collected visual attributes for entire line
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths from ScriptPlace
//    int                                         cGlyphs,        // In   Size of all arrays
//    int                                         iDx,            // In   Desired width change, either increase or descrease
//    int                                         iMinKashida,    // In   Minimum length of continuous kashida glyph to generate
//    __out_ecount_full(cGlyphs) int              *piJustify);    // Out  Updated advance widths to pass to ScriptTextOut
//
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptJustify(
//    __in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Collected visual attributes for entire line
//    __in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths from ScriptPlace
//    int                                         cGlyphs,        // In   Size of all arrays
//    int                                         iDx,            // In   Desired width change, either increase or descrease
//    int                                         iMinKashida,    // In   Minimum length of continuous kashida glyph to generate
//    __out_ecount_full(cGlyphs) int              *piJustify)    // Out  Updated advance widths to pass to ScriptTextOut
//{
//	WRAP_BEGIN(ScriptJustify, LPFNSCRIPTJUSTIFY)
//	hResult = ScriptJustify(psva,piAdvance, cGlyphs, iDx, iMinKashida, piJustify);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
