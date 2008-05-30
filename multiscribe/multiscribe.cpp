// gusp10.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//#include "GraphiteScriptStringAnalysis.h"
#include "GlyphsToTextSourceMap.h"
#include "interceptor.h"

__declspec(dllexport) void DoNothing()
{
}

float round(float f){
  int sign = (f < 0)? -1:1;
  f*=sign;
  float fFloored = floor(f);
  if(f - fFloored < 0.5){
	return fFloored * sign;
  }
  return ceil(f)*sign;
}

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

__checkReturn HRESULT WINAPI GraphiteEnabledScriptFreeCache(
	__deref_inout_ecount(1) SCRIPT_CACHE   *psc);       //InOut  Cache handle

__checkReturn HRESULT WINAPI GraphiteEnabledScriptShapeOpenType(
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in                       int                     cChars,         // In    Length of unicode run
	__in                       int                     cMaxGlyphs,     // In    Max glyphs to generate

	__out_ecount_full(cChars)  WORD                   *pwLogClust,     // Out   Logical clusters
	__out_ecount_full(cChars)  SCRIPT_CHARPROP        *pCharProps,     // Out   Output buffer for character properties

	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD                   *pwOutGlyphs,    // Out   Output glyph buffer
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_GLYPHPROP       *pOutGlyphProps, // Out   Visual glyph attributes
	__out                                    int                    *pcGlyphs);      // Out   Count of glyphs generated

__checkReturn HRESULT WINAPI GraphiteEnabledScriptPlaceOpenType(
	__in_opt                   HDC                     hdc,            // In    Optional (see under caching)
	__inout                    SCRIPT_CACHE           *psc,            // InOut Cache handle
	__inout                    SCRIPT_ANALYSIS        *psa,            // InOut Result of ScriptItemize (may have fNoGlyphIndex set)

	__in                       OPENTYPE_TAG            tagScript,      // In    Font script tag for shaping
	__in                       OPENTYPE_TAG            tagLangSys,     // In    Font language system tag for shaping
	__in_ecount_opt(cRanges)   int                    *rcRangeChars,      // In    Array of number of characters per range
	__in_ecount_opt(cRanges)   TEXTRANGE_PROPERTIES  **rpRangeProperties, // In    Array of range properties (for each range)
	__in                       int                     cRanges,           // In    Number of ranges

	__in_ecount(cChars)        const WCHAR            *pwcChars,       // In    Logical unicode run
	__in_ecount(cChars)        WORD                   *pwLogClust,     // In    Logical clusters
	__in_ecount(cChars)        SCRIPT_CHARPROP        *pCharProps,     // In    Output buffer for character properties
	__in                       int                     cChars,         // In    Length of unicode run

	__in_ecount(cGlyphs)       const WORD             *pwGlyphs,       // In    Glyph buffer from prior ScriptShape call
	__in_ecount(cGlyphs)       const SCRIPT_GLYPHPROP *pGlyphProps,    // In    Glyph properties
	__in                       int                     cGlyphs,        // In    Number of glyphs

	__out_ecount_full(cGlyphs) int                    *piAdvance,      // Out   Advance widths
	__out_ecount_full(cGlyphs) GOFFSET                *pGoffset,       // Out   x,y offset for combining glyph
	__out_opt                  ABC                    *pABC);          // Out   Composite ABC for the whole run (Optional)

__checkReturn HRESULT WINAPI GraphiteEnabledScriptTextOut(
	const HDC                               hdc,            // In     OS handle to device context (required)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,           // InOut  Cache handle
	int                                     x,              // In     x,y position for first glyph
	int                                     y,              // In
	UINT                                    fuOptions,      // In     ExtTextOut options
	__in_ecount_opt(1) const RECT           *lprc,          // In     optional clipping/opaquing rectangle
	__in_ecount(1) const SCRIPT_ANALYSIS    *psa,           // In     Result of ScriptItemize
	__reserved const WCHAR                  *pwcReserved,   // In     Reserved (requires NULL)
	__reserved int                          iReserved,      // In     Reserved (requires 0)
	__in_ecount(cGlyphs) const WORD         *pwGlyphs,      // In     Glyph buffer from prior ScriptShape call
	int                                     cGlyphs,        // In     Number of glyphs
	__in_ecount(cGlyphs) const int          *piAdvance,     // In     Advance widths from ScriptPlace
	__in_ecount_opt(cGlyphs) const int      *piJustify,     // In     Justified advance widths (optional)
	__in_ecount(cGlyphs) const GOFFSET      *pGoffset);     // In     x,y offset for combining glyph

#ifdef COLORIZE_SCRIPTSTRINGOUT
__checkReturn HRESULT WINAPI GraphiteEnabledScriptStringOut(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa,            //In  Analysis with glyphs
	int                                     iX,             //In
	int                                     iY,             //In
	UINT                                    uOptions,       //In  ExtTextOut options
	__in_ecount_opt(1) const RECT           *prc,           //In  Clipping rectangle (iff ETO_CLIPPED)
	int                                     iMinSel,        //In  Logical selection. Set iMinSel>=iMaxSel for no selection
	int                                     iMaxSel,        //In
	BOOL                                    fDisabled)      //In  If disabled, only the background is highlighted.
#endif

#ifdef INTERCEPT_SCRIPTITEMIZE

__checkReturn HRESULT WINAPI GraphiteEnabledScriptItemize(
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	int                                                 cInChars,       // In   Codepoint count to itemize
	int                                                 cMaxItems,      // In   Max length of itemization array
	__in_ecount_opt(1) const SCRIPT_CONTROL             *psControl,     // In   Analysis control (optional)
	__in_ecount_opt(1) const SCRIPT_STATE               *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount(1) int                                 *pcItems);      // Out  Count of items processed (optional)
#endif


#ifdef INTERCEPT_SCRIPTITEMIZEOPENTYPE

__checkReturn HRESULT WINAPI GraphiteEnabledScriptItemizeOpenType(
	__in_ecount(cInChars) const WCHAR                   *pwcInChars,    // In   Unicode string to be itemized
	__in                  int                            cInChars,      // In   Codepoint count to itemize
	__in                  int                            cMaxItems,     // In   Max length of itemization array
	__in_opt              const SCRIPT_CONTROL          *psControl,     // In   Analysis control (optional)
	__in_opt              const SCRIPT_STATE            *psState,       // In   Initial bidi algorithm state (optional)
	__out_ecount_part(cMaxItems, *pcItems) SCRIPT_ITEM  *pItems,        // Out  Array to receive itemization
	__out_ecount_part(cMaxItems, *pcItems) OPENTYPE_TAG *pScriptTags,   // Out  Array of script tags - parallel to items
	__out                 int                           *pcItems);      // Out  Count of items processed (optional)
#endif

//void FreeScriptProperties();

//static GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP * gpGraphiteScriptStringAnalysisMap;
static SESSION_TO_GLYPHPOSITIONS * gpGlyphPositions;
static Interceptor * gpScriptShapeInterceptor;
static Interceptor * gpScriptPlaceInterceptor;
static Interceptor * gpScriptShapeOpenTypeInterceptor;
static Interceptor * gpScriptPlaceOpenTypeInterceptor;
static Interceptor * gpScriptIsComplexInterceptor;
static Interceptor * gpScriptFreeCacheInterceptor;
static Interceptor * gpScriptTextOutInterceptor;
#ifdef COLORIZE_SCRIPTSTRINGOUT
static Interceptor * gpScriptStringOutInterceptor;
#endif
#ifdef INTERCEPT_SCRIPTITEMIZE
static Interceptor * gpScriptItemizeInterceptor;
#endif
#ifdef INTERCEPT_SCRIPTITEMIZEOPENTYPE
static Interceptor * gpScriptItemizeOpenTypeInterceptor;
#endif
static HINSTANCE ghUSP10DLL;

LPVOID GetOriginalScriptShape()
{
	return gpScriptShapeInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptPlace()
{
	return gpScriptPlaceInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptShapeOpenType()
{
	return gpScriptShapeOpenTypeInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptPlaceOpenType()
{
	return gpScriptPlaceOpenTypeInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptIsComplex()
{
	return gpScriptIsComplexInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptFreeCache()
{
	return gpScriptFreeCacheInterceptor->GetOriginal();
}

LPVOID GetOriginalScriptTextOut()
{
  return gpScriptTextOutInterceptor->GetOriginal();
}
#ifdef COLORIZE_SCRIPTSTRINGOUT
LPVOID GetOriginalScriptStringOut()
{
	return gpScriptStringOutInterceptor->GetOriginal();
}
#endif

#ifdef INTERCEPT_SCRIPTITEMIZE
LPVOID GetOriginalScriptItemize()
{
  return gpScriptItemizeInterceptor->GetOriginal();
}
#endif

#ifdef INTERCEPT_SCRIPTITEMIZEOPENTYPE
LPVOID GetOriginalScriptItemizeOpenType()
{
  return gpScriptItemizeOpenTypeInterceptor->GetOriginal();
}
#endif

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


BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	hModule;
	lpReserved;

	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			ghUSP10DLL = LoadLibraryA(USP10DLLNAME);
			if(!ghUSP10DLL) {
			  // try again, this time using the specified path used to load this.
			  char szModuleFileName[MAX_PATH];
			  DWORD cbModuleFileName = GetModuleFileNameA(hModule, &szModuleFileName[0], MAX_PATH-1);
			  if(cbModuleFileName != 0) {
				char szFileName[_MAX_FNAME];
				char szExt[_MAX_EXT];
				_splitpath(szModuleFileName, NULL, NULL, &szFileName[0], &szExt[0]);
				// remove filename and extension
				szModuleFileName[cbModuleFileName - strlen(szFileName) - strlen(szExt)] = NULL;
				strcat(szModuleFileName, USP10DLLNAME);
				ghUSP10DLL = LoadLibraryA(szModuleFileName);
			  }
			  if(!ghUSP10DLL) {
				return FALSE;
			  }
			}
			MakeAllScriptPropertiesComplex();
//			gpGraphiteScriptStringAnalysisMap = new GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP();
			gpGlyphPositions = new SESSION_TO_GLYPHPOSITIONS();
			gpScriptPlaceInterceptor = new Interceptor(ghUSP10DLL, "ScriptPlace", &GraphiteEnabledScriptPlace);
			gpScriptShapeInterceptor = new Interceptor(ghUSP10DLL, "ScriptShape", &GraphiteEnabledScriptShape);
			gpScriptPlaceOpenTypeInterceptor = new Interceptor(ghUSP10DLL, "ScriptPlaceOpenType", &GraphiteEnabledScriptPlaceOpenType);
			gpScriptShapeOpenTypeInterceptor = new Interceptor(ghUSP10DLL, "ScriptShapeOpenType", &GraphiteEnabledScriptShapeOpenType);
			gpScriptIsComplexInterceptor = new Interceptor(ghUSP10DLL, "ScriptIsComplex", &GraphiteEnabledScriptIsComplex);
			gpScriptFreeCacheInterceptor = new Interceptor(ghUSP10DLL, "ScriptFreeCache", &GraphiteEnabledScriptFreeCache);
			gpScriptTextOutInterceptor = new Interceptor(ghUSP10DLL, "ScriptTextOut", &GraphiteEnabledScriptTextOut);
#ifdef COLORIZE_SCRIPTSTRINGOUT
			gpScriptStringOutInterceptor = new Interceptor(ghUSP10DLL, "ScriptStringOut", &GraphiteEnabledScriptStringOut);
#endif
#ifdef INTERCEPT_SCRIPTITEMIZE
			gpScriptItemizeInterceptor = new Interceptor(ghUSP10DLL, "ScriptItemize", &GraphiteEnabledScriptItemize);
#endif
#ifdef INTERCEPT_SCRIPTITEMIZEOPENTYPE
			gpScriptItemizeOpenTypeInterceptor = new Interceptor(ghUSP10DLL, "ScriptItemizeOpenType", &GraphiteEnabledScriptItemizeOpenType);
#endif
	  break;
		case DLL_PROCESS_DETACH:
//			delete gpGraphiteScriptStringAnalysisMap;
			delete gpGlyphPositions;
//			FreeScriptProperties();
			delete gpScriptPlaceInterceptor;
			delete gpScriptShapeInterceptor;
			delete gpScriptPlaceOpenTypeInterceptor;
			delete gpScriptShapeOpenTypeInterceptor;
			delete gpScriptIsComplexInterceptor;
			delete gpScriptFreeCacheInterceptor;
			delete gpScriptTextOutInterceptor;
#ifdef COLORIZE_SCRIPTSTRINGOUT
			delete gpScriptStringOutInterceptor;
#endif
#ifdef INTERCEPT_SCRIPTITEMIZE
			delete gpScriptItemizeInterceptor;
#endif
#ifdef INTERCEPT_SCRIPTITEMIZEOPENTYPE
			delete gpScriptItemizeOpenTypeInterceptor;
#endif
	  break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		}
	return TRUE;
}

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


//static GLYPHS_TO_TEXTSOURCE_MAP * gpGlyphsToTextSourceMap;

static TextSource gLastTextSourceCache;
static GlyphPositions gLastGlyphPositionsCache;

TextSource & GetLastScriptShapeTextSource(){
  return gLastTextSourceCache;
}

void SetLastScriptShapeTextSource(TextSource &textSource){
  gLastTextSourceCache = textSource;
}

std::basic_string<WORD>&
GetLastScriptShapeGlyphs() {
  return gLastGlyphPositionsCache.glyphs;
}

GlyphPositions *
GetGlyphPositions(LPVOID pSessionKey, LPVOID pKey,
				  const WORD * pGlyphs, int cGlyphs)
{
	assert(pSessionKey);
	assert(pKey);
	assert(gpGlyphPositions);
	assert(pGlyphs);

	if(!pSessionKey || !pKey || !gpGlyphPositions || !pGlyphs){
		return NULL;
	}

	GLYPHPOSITIONS_MAP& glyphPositionsMap = (*gpGlyphPositions)[pSessionKey];

	GLYPHPOSITIONS_MAP::iterator it;
	it = glyphPositionsMap.find(pKey);
	if (it == glyphPositionsMap.end()) {
		return NULL;
	}

	if (static_cast<int>(it->second.glyphs.size()) == cGlyphs
		&& std::equal(it->second.glyphs.begin(),
				it->second.glyphs.end(),
				pGlyphs))
	{
		GlyphPositions* pTextSource = &it->second;
		return pTextSource;
	}

	// old cache
	glyphPositionsMap.erase(it);
	return NULL;
}

void
SetGlyphPositions(LPVOID pSessionKey, LPVOID pKey, GlyphPositions & glyphPositions)
{
	assert(pSessionKey);
	assert(pKey);
	assert(gpGlyphPositions);
	if (!pSessionKey || !pKey || !gpGlyphPositions) {
		return;
	}

	(*gpGlyphPositions)[pSessionKey][pKey] = glyphPositions;
	gLastGlyphPositionsCache = glyphPositions;
}

void FreeGlyphPositionsForSession(LPVOID pSessionKey)
{
//	assert(pSessionKey);
	assert(gpGlyphPositions);
	if (!pSessionKey || !gpGlyphPositions) {
		return;
	}
	gpGlyphPositions->erase(pSessionKey);
}
