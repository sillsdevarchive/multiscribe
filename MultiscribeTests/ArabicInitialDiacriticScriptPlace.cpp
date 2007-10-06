#include "stdafx.h"
#include "ArabicScriptPlaceTests.h"

struct ArabicInitialDiacriticScriptPlaceLogical:ArabicScriptPlaceTests{
  ArabicInitialDiacriticScriptPlaceLogical():ArabicScriptPlaceTests(L"رِنئ", true){
  }
};

struct ArabicInitialDiacriticScriptPlaceVisual:ArabicScriptPlaceTests{
  ArabicInitialDiacriticScriptPlaceVisual():ArabicScriptPlaceTests(L"رِنئ", false){
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(ArabicInitialDiacriticScriptPlaceTests)
{
  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {19,0,13,34};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {34,13,0,19};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectXOffset){
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

  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectXOffset){
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

  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,2,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(ArabicInitialDiacriticScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,2,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }
}