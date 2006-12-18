#pragma once


#include <map>
#include "TextSource.h"

typedef struct {
	HDC						hdc;			// Device context
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
