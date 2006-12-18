#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptApplyLogicalWidth=_usp10.ScriptApplyLogicalWidth")

/////   ScriptApplyLogicalWidth

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTAPPLYLOGICALWIDTH)(
	__in_ecount(cChars) const int               *piDx,          // In     Logical dx array to apply
	int                                         cChars,         // In     Count of logical codepoints in run
	int                                         cGlyphs,        // In     Glyph count
	__in_ecount(cChars) const WORD              *pwLogClust,    // In     Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In     Visual attributes from ScriptShape/Place
	__in_ecount(cGlyphs) const int              *piAdvance,     // In     Glyph advance widths from ScriptPlace
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In     Script analysis from item attributes
	__inout_ecount_opt(1) ABC                   *pABC,          // InOut  Updated item ABC width (optional)
	__out_ecount_full(cGlyphs) int              *piJustify);    // Out    Resulting glyph advance widths for ScriptTextOut



#ifdef __cplusplus
extern "C" {
#endif

__checkReturn HRESULT WINAPI LoggingScriptApplyLogicalWidth(
	__in_ecount(cChars) const int               *piDx,          // In     Logical dx array to apply
	int                                         cChars,         // In     Count of logical codepoints in run
	int                                         cGlyphs,        // In     Glyph count
	__in_ecount(cChars) const WORD              *pwLogClust,    // In     Logical clusters
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,          // In     Visual attributes from ScriptShape/Place
	__in_ecount(cGlyphs) const int              *piAdvance,     // In     Glyph advance widths from ScriptPlace
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa,           // In     Script analysis from item attributes
	__inout_ecount_opt(1) ABC                   *pABC,          // InOut  Updated item ABC width (optional)
	__out_ecount_full(cGlyphs) int              *piJustify)    // Out    Resulting glyph advance widths for ScriptTextOut
{
	WRAP_BEGIN(ScriptApplyLogicalWidth, LPFNSCRIPTAPPLYLOGICALWIDTH)
	LOG(L"<ScriptApplyLogicalWidth>");
	LOG(L"<in>");
	LOG(L"<Chars count='%d'>", cChars);
	for(int i=0;i<cChars;++i){
		LOG(L"<LogicalCluster dx='%d'>%d</LogicalCluster>", piDx[i], pwLogClust[i]);
	}
	LOG(L"</Chars>");
	LOG(L"<Glyphs count='%d'>", cGlyphs);
	for(int i=0;i<cGlyphs;++i){
		LOG(L"<Glyph advance='%d'>", piAdvance[i]);
		LogScriptVisualAttributes(&psva[i]);
		LOG(L"</Glyph>");
	}
	LOG(L"</Glyphs>");
	LogScriptAnalysis(psa);
	if(pABC){
		LogABC(pABC);
	}

	LOG(L"</in>");
	hResult = ScriptApplyLogicalWidth(piDx,cChars,cGlyphs,pwLogClust,psva,piAdvance,psa,pABC,piJustify);
	LOG(L"<out>");
	if(pABC){
		LogABC(pABC);
	}
	LOG(L"<Glyphs count='%d'>", cGlyphs);
	for(int i=0;i<cGlyphs;++i){
		LOG(L"<Glyph advance='%d'/>", piJustify);
	}
	LOG(L"</Glyphs>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptApplyLogicalWidth>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
