#include "stdafx.h"

#include "BurmeseScriptPlaceTests.h"


struct BurmeseDiacriticScriptPlace:BurmeseScriptPlaceTests{
  BurmeseDiacriticScriptPlace():BurmeseScriptPlaceTests(L"ကျွနှ်ပ်တို့၏"){
  }
};

SUITE(BurmeseOverlappingSymbolsScriptPlaceTests)
{
  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
	WORD piExpectedAdvance[] = {65,11,7,25,4,34,4,57,4,11,0,59};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,0,0,0,0,0,0,-21,-11,-8};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,0,0,2,0,2,0,0,0,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcA);
  }

  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL((UINT) 274, ABC.abcB);
  }

  TEST_FIXTURE(BurmeseDiacriticScriptPlace, ScriptPlace_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcC);
  }

}