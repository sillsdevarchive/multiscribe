#include "stdafx.h"
#include "ArabicScriptPlaceTests.h"

struct ArabicWideDiacriticScriptPlaceLogical:ArabicScriptPlaceTests{
  ArabicWideDiacriticScriptPlaceLogical():ArabicScriptPlaceTests(L"آسہ", true){
  }
};

struct ArabicWideDiacriticScriptPlaceVisual:ArabicScriptPlaceTests{
  ArabicWideDiacriticScriptPlaceVisual():ArabicScriptPlaceTests(L"آسہ", false){
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(ArabicWideDiacriticScriptPlaceTests)
{
  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {11,0,34,16};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {16,34,0,11};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_EQUAL(piExpectedXOffset, piActualXOffset, cGlyphs);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_EQUAL(piExpectedXOffset, piActualXOffset, cGlyphs);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,-1,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(ArabicWideDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,-1,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }
}