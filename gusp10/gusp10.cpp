// gusp10.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "GraphiteScriptStringAnalysis.h"
HRESULT InitializeScriptProperties();
void FreeScriptProperties();

static GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP * gpGraphiteScriptStringAnalysisMap;

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
			if(InitializeScriptProperties()!=S_OK){
				return FALSE;
			}
			break;
		case DLL_PROCESS_DETACH:
			delete(gpGraphiteScriptStringAnalysisMap);
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

GRAPHITE_SCRIPT_STRING_ANALYSIS *
GetGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa)
{
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

GRAPHITE_SCRIPT_STRING_ANALYSIS*
CreateGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa){
	assert(gpGraphiteScriptStringAnalysisMap);
	if(!gpGraphiteScriptStringAnalysisMap){
		return NULL;
	}
	GRAPHITE_SCRIPT_STRING_ANALYSIS* pgssa = new GRAPHITE_SCRIPT_STRING_ANALYSIS();
	(*gpGraphiteScriptStringAnalysisMap)[ssa] = pgssa;
	return pgssa;
}
