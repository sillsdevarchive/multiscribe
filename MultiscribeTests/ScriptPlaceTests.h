#pragma once
#include <usp10.h>
#include "ScriptTests.h"

struct ScriptPlaceTests:ScriptTests{
  ScriptPlaceTests(std::wstring s, std::wstring sFontName):ScriptTests(s, sFontName){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	assert(hResult == S_OK);hResult;

	piAdvance = new int[cGlyphs];
	pGoffset = new GOFFSET[cGlyphs];
  }

  ~ScriptPlaceTests(){
	delete[] piAdvance;
	delete[] pGoffset;
  }

  int*      piAdvance;
  GOFFSET*  pGoffset;
  ABC       ABC;
};
