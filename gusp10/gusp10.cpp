// gusp10.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "GraphiteScriptStringAnalysis.h"
#include "GlyphsToTextSourceMap.h"

HRESULT InitializeScriptProperties();
void FreeScriptProperties();

static GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP * gpGraphiteScriptStringAnalysisMap;
static GLYPHS_TO_TEXTSOURCE_MAP * gpGlyphsToTextSourceMap;

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
			gpGraphiteScriptStringAnalysisMap = new GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP();
			gpGlyphsToTextSourceMap = new GLYPHS_TO_TEXTSOURCE_MAP();
			break;
		case DLL_PROCESS_DETACH:
			delete(gpGraphiteScriptStringAnalysisMap);
			delete(gpGlyphsToTextSourceMap);
			FreeScriptProperties();
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

GRAPHITE_SCRIPT_STRING_ANALYSIS * const
GetGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa)
{
	//GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = reinterpret_cast<GRAPHITE_SCRIPT_STRING_ANALYSIS*> (ssa);
	//if(strncmp(pgssa->graphiteId, "graphite", 8) == 0){
	//	return pgssa;
	//}
	//return NULL;

	assert(gpGraphiteScriptStringAnalysisMap);
	if(!gpGraphiteScriptStringAnalysisMap){
		return NULL;
	}
	GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP::const_iterator it;
	it = gpGraphiteScriptStringAnalysisMap->find(ssa);
	if(it == gpGraphiteScriptStringAnalysisMap->end()){
		return NULL;
	}
	return it->second;
}

void FreeGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa){

	//GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = GetGraphiteScriptStringAnalysis(ssa);
	//if(pgssa)
	//{
	//	delete pgssa;
	//}

	assert(gpGraphiteScriptStringAnalysisMap);
	if(!gpGraphiteScriptStringAnalysisMap){
		return;
	}
	GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP::iterator it;
	it = gpGraphiteScriptStringAnalysisMap->find(ssa);
	if(it == gpGraphiteScriptStringAnalysisMap->end()){
		return;
	}
	delete it->second;
	gpGraphiteScriptStringAnalysisMap->erase(it);
}

GRAPHITE_SCRIPT_STRING_ANALYSIS * const
CreateGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa){

	assert(gpGraphiteScriptStringAnalysisMap);
	if(!gpGraphiteScriptStringAnalysisMap){
		return NULL;
	}
	GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = new GRAPHITE_SCRIPT_STRING_ANALYSIS();
	gpGraphiteScriptStringAnalysisMap->insert(std::make_pair(ssa, pgssa));
	//strncpy(pgssa->graphiteId, "graphite", 8);
	//pgssa->ssa = ssa;
	return pgssa;
}


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
