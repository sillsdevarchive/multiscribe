#pragma once
#include "stdafx.h"
#include "ScriptTests.h"

struct RtlScriptPlaceTests:ScriptTests{
  RtlScriptPlaceTests(std::wstring s, std::wstring sFontName, bool fLogicalOrder):ScriptTests(s,sFontName){
	assert(pItems[0].a.fRTL);
	assert(pItems[0].a.fLayoutRTL);

	psa->fLogicalOrder = fLogicalOrder;
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	assert(hResult == S_OK || hResult == USP_E_SCRIPT_NOT_IN_FONT);hResult;

	piAdvance = new int[cGlyphs];
	pGoffset = new GOFFSET[cGlyphs];
  }

  ~RtlScriptPlaceTests(){
	delete[] piAdvance;
	delete[] pGoffset;
  }

  int*      piAdvance;
  GOFFSET*  pGoffset;
  ABC       ABC;
};