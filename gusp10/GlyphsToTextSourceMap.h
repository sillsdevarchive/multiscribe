#pragma once

#include <map>
#include "TextSource.h"

typedef std::map<std::basic_string<WORD>, TextSource * const> GLYPHS_TO_TEXTSOURCE_MAP;

TextSource * const
GetTextSource(const WORD * glyphs, const int cGlyphs);

TextSource * const
CreateTextSource(const WORD * glyphs, const int cGlyphs);
