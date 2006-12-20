// gusp10.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//#include "GraphiteScriptStringAnalysis.h"
#include "GlyphsToTextSourceMap.h"
#include "hook.h"

__checkReturn HRESULT WINAPI GraphiteEnabledScriptPlace(
	HDC                                         hdc,        // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE        *psc,       // InOut Cache handle
	__in_ecount(cGlyphs) const WORD             *pwGlyphs,  // In    Glyph buffer from prior ScriptShape call
	int                                         cGlyphs,    // In    Number of glyphs
	__in_ecount(cGlyphs) const SCRIPT_VISATTR   *psva,      // In    Visual glyph attributes
	__inout_ecount(1) SCRIPT_ANALYSIS           *psa,       // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_full(cGlyphs) int              *piAdvance, // Out   Advance wdiths
	__out_ecount_full_opt(cGlyphs) GOFFSET      *pGoffset,  // Out   x,y offset for combining glyph
	__out_ecount(1) ABC                         *pABC);      // Out   Composite ABC for the whole run (Optional)

__checkReturn HRESULT WINAPI GraphiteEnabledScriptShape(
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

__checkReturn HRESULT WINAPI GraphiteEnabledScriptIsComplex(
	__in_ecount(cInChars) const WCHAR   *pwcInChars,    //In  String to be tested
	int                                 cInChars,       //In  Length in characters
	DWORD                               dwFlags);       //In  Flags (see above)

//void FreeScriptProperties();

//static GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP * gpGraphiteScriptStringAnalysisMap;
static GLYPHS_TO_TEXTSOURCE_MAP * gpGlyphsToTextSourceMap;
static Interceptor * gpScriptShapeInterceptor;
static Interceptor * gpScriptPlaceInterceptor;
static Interceptor * gpScriptIsComplexInterceptor;

static HINSTANCE ghUSP10DLL;

LPVOID GetOriginalScriptShape()
{
	return gpScriptShapeInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptPlace()
{
	return gpScriptPlaceInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptIsComplex()
{
	return gpScriptIsComplexInterceptor->GetOriginal();
}


typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETPROPERTIES) (
	__deref_out_ecount(1) const SCRIPT_PROPERTIES   ***pppSp,        // Out  Receives pointer to table of pointers to properties indexed by script
	__out_ecount(1) int                             *piNumScripts); // Out  Receives number of scripts (valid values are 0 through NumScripts-1)

HRESULT MakeAllScriptPropertiesComplex(){
	WRAP_BEGIN(ScriptGetProperties, LPFNSCRIPTGETPROPERTIES)

	const SCRIPT_PROPERTIES ** ppSp;
	SCRIPT_PROPERTIES * pSp;
	DWORD dwOriginalProtection;

	int iNumScripts;
	hResult = ScriptGetProperties(&ppSp, &iNumScripts);
	if (hResult == S_OK){
		for(int i = 0; i < iNumScripts; ++i){
			pSp = const_cast<SCRIPT_PROPERTIES *>(ppSp[i]);
			VirtualProtect(pSp, sizeof(SCRIPT_PROPERTIES), PAGE_EXECUTE_READWRITE, &dwOriginalProtection); // unlock
			pSp->fComplex = true;
			VirtualProtect(pSp, sizeof(SCRIPT_PROPERTIES), dwOriginalProtection, &dwOriginalProtection); // lock
		}
	}
	WRAP_END
}

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _MANAGED
#pragma managed(push, off)
#endif
BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	hModule;
	lpReserved;

	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			ghUSP10DLL = LoadLibraryA("_usp10.dll");
			MakeAllScriptPropertiesComplex();
//			gpGraphiteScriptStringAnalysisMap = new GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP();
			gpGlyphsToTextSourceMap = new GLYPHS_TO_TEXTSOURCE_MAP();
			gpScriptPlaceInterceptor = new Interceptor(ghUSP10DLL, "ScriptPlace", &GraphiteEnabledScriptPlace);
			gpScriptShapeInterceptor = new Interceptor(ghUSP10DLL, "ScriptShape", &GraphiteEnabledScriptShape);
			gpScriptIsComplexInterceptor = new Interceptor(ghUSP10DLL, "ScriptIsComplex", &GraphiteEnabledScriptIsComplex);
			break;
		case DLL_PROCESS_DETACH:
//			delete gpGraphiteScriptStringAnalysisMap;
			delete gpGlyphsToTextSourceMap;
//			FreeScriptProperties();
			delete gpScriptPlaceInterceptor;
			delete gpScriptShapeInterceptor;
			delete gpScriptIsComplexInterceptor;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		}
	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
#ifdef __cplusplus
}
#endif

//GRAPHITE_SCRIPT_STRING_ANALYSIS * const
//GetGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa)
//{
//    //GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = reinterpret_cast<GRAPHITE_SCRIPT_STRING_ANALYSIS*> (ssa);
//	//if(strncmp(pgssa->graphiteId, "graphite", 8) == 0){
//	//	return pgssa;
//	//}
//	//return NULL;
//
//	assert(gpGraphiteScriptStringAnalysisMap);
//	if(!gpGraphiteScriptStringAnalysisMap){
//		return NULL;
//	}
//	GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP::const_iterator it;
//	it = gpGraphiteScriptStringAnalysisMap->find(ssa);
//	if(it == gpGraphiteScriptStringAnalysisMap->end()){
//		return NULL;
//	}
//	return it->second;
//}
//
//void FreeGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa){
//
//	//GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = GetGraphiteScriptStringAnalysis(ssa);
//	//if(pgssa)
//	//{
//	//	delete pgssa;
//	//}
//
//	assert(gpGraphiteScriptStringAnalysisMap);
//	if(!gpGraphiteScriptStringAnalysisMap){
//		return;
//	}
//	GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP::iterator it;
//	it = gpGraphiteScriptStringAnalysisMap->find(ssa);
//	if(it == gpGraphiteScriptStringAnalysisMap->end()){
//		return;
//	}
//	delete it->second;
//	gpGraphiteScriptStringAnalysisMap->erase(it);
//}
//
//GRAPHITE_SCRIPT_STRING_ANALYSIS * const
//CreateGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa){
//
//	assert(gpGraphiteScriptStringAnalysisMap);
//	if(!gpGraphiteScriptStringAnalysisMap){
//		return NULL;
//	}
//    GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = new GRAPHITE_SCRIPT_STRING_ANALYSIS();
//	gpGraphiteScriptStringAnalysisMap->insert(std::make_pair(ssa, pgssa));
//	//strncpy(pgssa->graphiteId, "graphite", 8);
//	//pgssa->ssa = ssa;
//	return pgssa;
//}


TextSource * const
GetTextSource(const WORD * glyphs, const int cGlyphs){
	assert(glyphs);
	assert(gpGlyphsToTextSourceMap);
	if(!gpGlyphsToTextSourceMap){
		return NULL;
	}
	std::basic_string<WORD> rgGlyphs(glyphs, glyphs+cGlyphs);
	GLYPHS_TO_TEXTSOURCE_MAP::const_iterator it;
	it = gpGlyphsToTextSourceMap->find(rgGlyphs);
	if(it == gpGlyphsToTextSourceMap->end()){
		return NULL;
	}
	return it->second;
}

TextSource * const
CreateTextSource(const WORD * glyphs, const int cGlyphs){
	assert(glyphs);
	assert(gpGlyphsToTextSourceMap);
	if(!gpGlyphsToTextSourceMap){
		return NULL;
	}

	std::basic_string<WORD> rgGlyphs(glyphs, glyphs+cGlyphs);
	GLYPHS_TO_TEXTSOURCE_MAP::const_iterator it;
	it = gpGlyphsToTextSourceMap->find(rgGlyphs);
	if(it == gpGlyphsToTextSourceMap->end()){
		TextSource* pTextSource = new TextSource();
		gpGlyphsToTextSourceMap->insert(std::make_pair(rgGlyphs, pTextSource));
		return pTextSource;
	}
	else{
		return it->second;
	}
}
