#pragma once


#include <map>
#include "TextSource.h"

// outChars is at offset 0x108 and is accessed directly by lpk.dll
// size is at offset 0x118
// logAttr is at offset 0x26c

// hdc is at offset 0x0
// cString is at offset 0x2c
// pString is at offset 0x28

typedef struct {
	HDC						hdc;			// Device context
	//char					graphiteId[8];  //space for 'graphite'
	//SCRIPT_STRING_ANALYSIS  ssa;
	TextSource*				pTextSource;
	int						iReqWidth;
	int						cOutChars;
	SCRIPT_LOGATTR*			pLogAttr;
	SIZE					size;
/*	gr::WinFont				font;
	gr::LayoutEnvironment	layout;
	gr::Segment				segment;
*/

} GRAPHITE_SCRIPT_STRING_ANALYSIS;

typedef struct {
	HDC     hdc;			// Device context
} CLEAR_SCRIPT_STRING_ANALYSIS;

typedef std::map<const SCRIPT_STRING_ANALYSIS, GRAPHITE_SCRIPT_STRING_ANALYSIS *const> GRAPHITE_SCRIPT_STRING_ANALYSIS_MAP;

GRAPHITE_SCRIPT_STRING_ANALYSIS * const
GetGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa);

GRAPHITE_SCRIPT_STRING_ANALYSIS * const
CreateGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa);

void FreeGraphiteScriptStringAnalysis(const SCRIPT_STRING_ANALYSIS ssa);
