#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetLogicalWidths=_usp10.ScriptGetLogicalWidths")

/////   ScriptGetLogicalWidths
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETLOGICALWIDTHS)(
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
	int                                         cChars,         // In   Count of logical codepoints in run
	int                                         cGlyphs,        // In   Count of glyphs in run
	__in_ecount(cGlyphs) const int              *piGlyphWidth,  // In   Advance widths
	__in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes
	__in_ecount(cChars) int                     *piDx);         // Out  Logical widths

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptGetLogicalWidths(
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
	int                                         cChars,         // In   Count of logical codepoints in run
	int                                         cGlyphs,        // In   Count of glyphs in run
	__in_ecount(cGlyphs) const int              *piGlyphWidth,  // In   Advance widths
	__in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes
	__in_ecount(cChars) int                     *piDx)         // Out  Logical widths
{
	WRAP_BEGIN(ScriptGetLogicalWidths, LPFNSCRIPTGETLOGICALWIDTHS)
	LOG(L"<ScriptGetLogicalWidths>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptGetLogicalWidths(psa, cChars, cGlyphs, piGlyphWidth, pwLogClust, psva, piDx);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptGetLogicalWidths>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
