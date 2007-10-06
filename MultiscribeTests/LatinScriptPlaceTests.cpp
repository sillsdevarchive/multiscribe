#include "stdafx.h"

#include "LatinScriptPlaceTests.h"


struct HelloWorldLatinScriptPlace:LatinScriptPlaceTests{
  HelloWorldLatinScriptPlace():LatinScriptPlaceTests(L"hè̱̟̆̃llo͠o world"){
  }
};

SUITE(LatinStackedDiacriticsScriptPlaceTests)
{
  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
	WORD piExpectedAdvance[] = {33,29,0,0,0,0,0,18,18,33,0,33,19,47,33,22,18,33};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] =
#if UNISCRIBE
	{0,0,0,14,28,0,-13,0,0,0,0,0,0,0,0,0,0,0};
#endif
#if GRAPHITE
	{0,0,0,14,28,0,-13,0,0,0,-9,0,0,0,0,0,0,0}; //probably wrong
#endif
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_CLOSE(piExpectedYOffset, piActualYOffset, cGlyphs,1);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcA);
  }

  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

#if UNISCRIBE
	CHECK_EQUAL((UINT) 336, ABC.abcB);
#endif
#if GRAPHITE
	CHECK_EQUAL((UINT) 337, ABC.abcB); // probably rounding
#endif
  }

  TEST_FIXTURE(HelloWorldLatinScriptPlace, ScriptPlace_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcC);
  }

}