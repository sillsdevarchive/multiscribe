#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptShape=_usp10.ScriptShape")

///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptShape
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSHAPE) (
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs);     // Out   Count of glyphs generated

#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptShape(
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs)     // Out   Count of glyphs generated
{
	WRAP_BEGIN(ScriptShape, LPFNSCRIPTSHAPE)
	LOG(L"<ScriptShape>");
	LOG(L"<in>");
  LogHdc(hdc);
	LogScriptCache(psc);
	LogString(pwcChars, cChars);
	LogScriptAnalysis(psa);

	LOG(L"</in>");
	hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
	LOG(L"<out>");
  if(hResult == S_OK){
	  LogScriptAnalysis(psa);
	  LOG(L"<Chars count='%d'>", cChars);
	  for(int i=0;i<cChars;++i){
		  LOG(L"<LogicalCluster>%d</LogicalCluster>", pwLogClust[i]);
	  }
	  LOG(L"</Chars>");
	  LOG(L"<Glyphs count='%d'>", *pcGlyphs);
	  for(int i=0; i<*pcGlyphs;++i){
		  LOG(L"<Glyph hex='%04x'>", pwOutGlyphs[i]);
		  LogScriptVisualAttributes(&psva[i]);
		  LOG(L"</Glyph>");
	  }
	  LOG(L"</Glyphs>");
  }
	LogHResult(hResult);
	LOG(L"</out>");

	LOG(L"</ScriptShape>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
