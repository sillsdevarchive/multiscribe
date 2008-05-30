#pragma once

#include <map>
#include <vector>
#include "TextSource.h"

struct GlyphPositions {
	std::vector<int> advanceWidths;
	std::vector<GOFFSET> goffsets;
	ABC abc;
	std::basic_string<WORD> glyphs;
};

typedef std::map<LPVOID, GlyphPositions> GLYPHPOSITIONS_MAP;
typedef std::map<LPVOID, GLYPHPOSITIONS_MAP> SESSION_TO_GLYPHPOSITIONS;

TextSource & GetLastScriptShapeTextSource();
void SetLastScriptShapeTextSource(TextSource & textSource);

std::basic_string<WORD>& GetLastScriptShapeGlyphs();

GlyphPositions *
GetGlyphPositions(LPVOID pSessionKey, LPVOID pKey, const WORD * pGlyphs, int cGlyphs);

void
SetGlyphPositions(LPVOID pSessionKey, LPVOID pKey, GlyphPositions & glyphPositions);

void
FreeGlyphPositionsForSession(LPVOID pSessionKey);