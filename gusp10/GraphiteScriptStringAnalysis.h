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
	TextSource				textSource;
	int						iReqWidth;
	int						cOutChars;
	SCRIPT_LOGATTR*			pLogAttr;
	SIZE					size;
	gr::WinFont	*			pFont; // ideally this would not be allocated in place rather than on the heap but WinFont's copy constructor is buggy
	gr::LayoutEnvironment *	pLayout; // again ideally this would be allocated in place
	gr::Segment	*			pSegment; // same as above
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
