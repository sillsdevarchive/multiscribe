#pragma once

#include <map>
#include "TextSource.h"

typedef std::map<std::basic_string<WORD>, TextSource> GLYPHS_TO_TEXTSOURCE_MAP;
typedef std::map<LPVOID, GLYPHS_TO_TEXTSOURCE_MAP> TEXTSOURCES;

TextSource *
GetTextSource(LPVOID p, const WORD * glyphs, const int cGlyphs);

void
CreateTextSource(LPVOID p, const WORD * glyphs, const int cGlyphs, TextSource& ts);

void
FreeTextSources(LPVOID p);