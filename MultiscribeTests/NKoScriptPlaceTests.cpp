#include "stdafx.h"

#include "N'KoScriptPlaceTests.h"


struct NKoDiacriticScriptPlaceLogical:NKoScriptPlaceTests{
  NKoDiacriticScriptPlaceLogical():NKoScriptPlaceTests(L"ߒ߬ߓߊ߬߸ ߟߏ߲ ߘߏ߫", true){
  }
};
struct NKoDiacriticScriptPlaceVisual:NKoScriptPlaceTests{
  NKoDiacriticScriptPlaceVisual():NKoScriptPlaceTests(L"ߒ߬ߓߊ߬߸ ߟߏ߲ ߘߏ߫", false){
  }
};

SUITE(NKoRtlDiacriticWithAdvanceScriptPlaceTests)
{
  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
//    WORD piExpectedAdvance[] = {42,0,42,4,0,32,32,50,28,32,58,2,27};
	WORD piExpectedAdvance[] = {42,0,42,4,0,32,32,50,28,32,58,29,0};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
	WORD piExpectedAdvance[] = {0,29,58,32,28,50,32,32,0,4,42,0,42};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

//    LONG piExpectedXOffset[] = {5,-47,0,0,-18,14,0,0,0,0,0,0,0};
	LONG piExpectedXOffset[] = {0,-15,0,0,14,0,0,0,0,0,0,0,1};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {-1,0,0,0,0,0,0,0,-14,0,0,15,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,2,0,0,2,0,0,0,0,0,0,0,2};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }
  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {2,0,0,0,0,0,0,0,2,0,0,2,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(-5, ABC.abcA);
  }
  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(-5, ABC.abcA);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL((UINT) 364, ABC.abcB);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL((UINT) 364, ABC.abcB);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceLogical, ScriptPlace_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcC);
  }

  TEST_FIXTURE(NKoDiacriticScriptPlaceVisual, ScriptPlace_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(0, ABC.abcC);
  }

}