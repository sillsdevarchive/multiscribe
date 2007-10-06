#pragma once
#include <usp10.h>
#include "RtlScriptPlaceTests.h"

struct NKoScriptPlaceTests:RtlScriptPlaceTests{
  NKoScriptPlaceTests(std::wstring s, bool fLogicalOrder):RtlScriptPlaceTests(s, L"N'ko Kankan", fLogicalOrder){
  }
};
