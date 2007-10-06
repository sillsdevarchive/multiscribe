#include "stdafx.h"
#include "LatinScriptPlaceTests.h"


struct LatinToneBarsScriptPlace:LatinScriptPlaceTests{
  LatinToneBarsScriptPlace():LatinScriptPlaceTests(L"˥˧˥˩ ˥˩˧˨˦˩˥"){
  }
};

SUITE(LatinToneBarsScriptPlaceTests)
{
  TEST_FIXTURE(LatinToneBarsScriptPlace, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
	WORD piExpectedAdvance[] = {14,14,19,7,19,14,14,14,14,14,19,7};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(LatinToneBarsScriptPlace, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,0,0,0,0,0,0,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_EQUAL(piExpectedXOffset, piActualXOffset, cGlyphs);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(LatinToneBarsScriptPlace, ScriptPlace_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(3, ABC.abcA);
  }

  TEST_FIXTURE(LatinToneBarsScriptPlace, ScriptPlace_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL((UINT) 160, ABC.abcB);
  }

  TEST_FIXTURE(LatinToneBarsScriptPlace, ScriptPlace_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(6, ABC.abcC);
  }

}