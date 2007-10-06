#pragma once
#include <usp10.h>
#include "ScriptPlaceTests.h"

struct LatinScriptPlaceTests:ScriptPlaceTests{
  LatinScriptPlaceTests(std::wstring s):ScriptPlaceTests(s, L"Doulos SIL"){//version 4.1
  }
};
