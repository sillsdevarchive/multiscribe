#include "stdafx.h"
#include "LatinScriptPlaceTests.h"


struct WideDiacriticLatinScriptPlace:LatinScriptPlaceTests{
  WideDiacriticLatinScriptPlace():LatinScriptPlaceTests(L"i̅ i̲"){
  }
};


SUITE(LatinWideDiacriticScriptPlaceTests)
{
  TEST_FIXTURE(WideDiacriticLatinScriptPlace, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {18,0,19,18,0};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(WideDiacriticLatinScriptPlace, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,7,0,0,8};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

}