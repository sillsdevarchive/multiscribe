#pragma once

#include <map>
#include <vector>

struct GlyphPositions{
	std::vector<int> advanceWidths;
	std::vector<GOFFSET> goffsets;
	ABC abc;
};

typedef std::map<LPVOID, GlyphPositions> GLYPHPOSITIONS_MAP;
typedef std::map<LPVOID, GLYPHPOSITIONS_MAP> SESSION_TO_GLYPHPOSITIONS;

GlyphPositions *
GetGlyphPositions(LPVOID pSessionKey, LPVOID pKey);

GlyphPositions *
CreateGlyphPositions(LPVOID pSessionKey, LPVOID pKey, int size);

void
FreeGlyphPositionsForSession(LPVOID pSessionKey);