#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptPositionSingleGlyph=_usp10.ScriptPositionSingleGlyph")

/////  ScriptPositionSingleGlyph

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTPOSITIONSINGLEGLYPH)(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
	__in               LONG                   lParameter,      // In    Feature parameter

	__in               WORD                   wGlyphId,         // In    Glyph id to be moved
	__in               int                    iAdvance,         // In    Original glyph advance width
	__in               GOFFSET                GOffset,          // In    Original glyph offset

	__out              int                   *piOutAdvance,     // Out   Adjusted advance width
	__out              GOFFSET               *pOutGoffset);       // Out   Adjusted offset


#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptPositionSingleGlyph(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
	__in               LONG                   lParameter,      // In    Feature parameter

	__in               WORD                   wGlyphId,         // In    Glyph id to be moved
	__in               int                    iAdvance,         // In    Original glyph advance width
	__in               GOFFSET                GOffset,          // In    Original glyph offset

	__out              int                   *piOutAdvance,     // Out   Adjusted advance width
	__out              GOFFSET               *pOutGoffset       // Out   Adjusted offset
)
{
	WRAP_BEGIN(ScriptPositionSingleGlyph, LPFNSCRIPTPOSITIONSINGLEGLYPH)
	LOG(L"<ScriptPositionSingleGlyph>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptPositionSingleGlyph(hdc, psc,psa,tagScript,tagLangSys,tagFeature,lParameter,wGlyphId,iAdvance,GOffset,piOutAdvance,pOutGoffset);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptPositionSingleGlyph>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
