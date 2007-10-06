#pragma once
#include "stdafx.h"
#include "RtlScriptPlaceTests.h"

struct ArabicScriptPlaceTests:RtlScriptPlaceTests{
  ArabicScriptPlaceTests(std::wstring s, bool fLogicalOrder):RtlScriptPlaceTests(s,
#if UNISCRIBE
	L"Scheherazade"
#endif
#if GRAPHITE
	L"Scheherazade Graphite Alpha"
#endif
	,fLogicalOrder){
  }
};