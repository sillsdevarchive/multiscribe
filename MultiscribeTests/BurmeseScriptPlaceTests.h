#pragma once
#include <usp10.h>
#include "ScriptPlaceTests.h"

struct BurmeseScriptPlaceTests:ScriptPlaceTests{
  BurmeseScriptPlaceTests(std::wstring s):ScriptPlaceTests(s, L"Padauk"){
  }
};
