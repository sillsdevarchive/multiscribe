#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptXtoCP=_usp10.ScriptXtoCP")

/////   ScriptXtoCP
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTXTOCP)(
	int                                         iX,             // In   X offset from left of run
	int                                         cChars,         // In   Count of logical codepoints in run
	int                                         cGlyphs,        // In   Count of glyphs in run
	__in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes
	__in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
	__out_ecount(1) int                         *piCP,          // Out  Resulting character position
	__out_ecount(1) int                         *piTrailing);   // Out  Leading or trailing half flag

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptXtoCP(
	int                                         iX,             // In   X offset from left of run
	int                                         cChars,         // In   Count of logical codepoints in run
	int                                         cGlyphs,        // In   Count of glyphs in run
	__in_ecount(cChars) const WORD              *pwLogClust,    // In   Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In   Visual glyph attributes
	__in_ecount(cGlyphs) const int              *piAdvance,     // In   Advance widths
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In   Script analysis from item attributes
	__out_ecount(1) int                         *piCP,          // Out  Resulting character position
	__out_ecount(1) int                         *piTrailing)   // Out  Leading or trailing half flag
{
	WRAP_BEGIN(ScriptXtoCP, LPFNSCRIPTXTOCP)
	LOG(L"<ScriptXtoCP>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptXtoCP(iX, cChars, cGlyphs, pwLogClust, psva, piAdvance, psa, piCP, piTrailing);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptXtoCP>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
