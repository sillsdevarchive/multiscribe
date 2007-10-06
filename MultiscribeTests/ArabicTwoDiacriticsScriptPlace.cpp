#include "stdafx.h"
#include "ArabicScriptPlaceTests.h"

struct Arabic2DiacriticsScriptPlaceLogical:ArabicScriptPlaceTests{
  Arabic2DiacriticsScriptPlaceLogical():ArabicScriptPlaceTests(L"تيۡپُھور", true){
  }
};

struct Arabic2DiacriticsScriptPlaceVisual:ArabicScriptPlaceTests{
  Arabic2DiacriticsScriptPlaceVisual():ArabicScriptPlaceTests(L"تيۡپُھور", false){
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(Arabic2DiacriticsScriptPlaceTests)
{
  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {13,13,0,13,0,25,21,19};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {19,21,25,0,13,0,13,13};
	CHECK_ARRAY_EQUAL(piExpectedAdvance, piAdvance, cGlyphs);
  }

  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,-8,0,-2,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_EQUAL(piExpectedXOffset, piActualXOffset, cGlyphs);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,2,0,8,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_EQUAL(piExpectedXOffset, piActualXOffset, cGlyphs);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,-12,0,-15,0,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_CLOSE(piExpectedYOffset, piActualYOffset, cGlyphs,1);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(Arabic2DiacriticsScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,0,-15,0,-12,0,0};
	 LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_CLOSE(piExpectedYOffset, piActualYOffset, cGlyphs,1);
	delete[] piActualYOffset;
 }
}