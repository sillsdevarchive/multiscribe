#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptSubstituteSingleGlyph=_usp10.ScriptSubstituteSingleGlyph")

/////  ScriptSubstituteSingleGlyph
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSUBSTITUTESINGLEGLYPH) (
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
	__in               LONG                   lParameter,      // In    Feature parameter

	__in               WORD                   wGlyphId,         // In    Original glyph id
	__out              WORD                  *pwOutGlyphId);      // Out   Substituted glyph id



#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptSubstituteSingleGlyph(
	__in_opt           HDC                    hdc,             // In    Optional (see under caching)
	__inout            SCRIPT_CACHE          *psc,             // InOut Cache handle
	__in_opt           SCRIPT_ANALYSIS       *psa,             // In    Result of ScriptItemize  (can be NULL)
	__in               OPENTYPE_TAG           tagScript,       // In    Font script tag
	__in               OPENTYPE_TAG           tagLangSys,      // In    Font language system tag for shaping
	__in               OPENTYPE_TAG           tagFeature,      // In    Feature tag to test for alternates
	__in               LONG                   lParameter,      // In    Feature parameter

	__in               WORD                   wGlyphId,         // In    Original glyph id
	__out              WORD                  *pwOutGlyphId      // Out   Substituted glyph id
)
{
	WRAP_BEGIN(ScriptSubstituteSingleGlyph, LPFNSCRIPTSUBSTITUTESINGLEGLYPH)
	LOG(L"<ScriptSubstituteSingleGlyph>");
	LOG(L"<in>");
	LOG(L"</in>");
	hResult = ScriptSubstituteSingleGlyph(hdc,psc,psa,tagScript,tagLangSys,tagFeature, lParameter,wGlyphId,pwOutGlyphId);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptSubstituteSingleGlyph>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
