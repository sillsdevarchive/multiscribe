#include "stdafx.h"
#include "ArabicScriptPlaceTests.h"

struct ArabicScriptPlaceLogical:ArabicScriptPlaceTests{
  ArabicScriptPlaceLogical():ArabicScriptPlaceTests(L"سہ ست ݜِݜو", true){
  }
};

struct ArabicScriptPlaceVisual:ArabicScriptPlaceTests{
  ArabicScriptPlaceVisual():ArabicScriptPlaceTests(L"سہ ست ݜِݜو", false){
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(ArabicRTLScriptPlaceTests)
{
  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {34,16,19,34,50,19,34,0,37,21};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAdvance){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	WORD piExpectedAdvance[] = {21,37,0,34,19,50,34,19,16,34};
	CHECK_ARRAY_CLOSE(piExpectedAdvance, piAdvance, cGlyphs,1);
  }

  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,0,0,0,0,0,-11,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectXOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedXOffset[] = {0,0,11,0,0,0,0,0,0,0};
	LONG* piActualXOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualXOffset[i] = pGoffset[i].du;
	}
	CHECK_ARRAY_CLOSE(piExpectedXOffset, piActualXOffset, cGlyphs,1);
	delete[] piActualXOffset;
  }

  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,0,0,0,0,0,14,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectYOffset){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	LONG piExpectedYOffset[] = {0,0,14,0,0,0,0,0,0,0};
	LONG* piActualYOffset = new LONG[cGlyphs];
	for(int i = 0; i != cGlyphs; ++i){
	  piActualYOffset[i] = pGoffset[i].dv;
	}
	CHECK_ARRAY_EQUAL(piExpectedYOffset, piActualYOffset, cGlyphs);
	delete[] piActualYOffset;
  }

  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

	CHECK_EQUAL(-1, ABC.abcA);
  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAbcA){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

#if UNISCRIBE
	CHECK_EQUAL(-2, ABC.abcA);
#endif
#if GRAPHITE
	CHECK_EQUAL(-1, ABC.abcA); // probably rounding error
#endif

  }

  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);
#if UNISCRIBE
	CHECK_EQUAL((UINT) 266, ABC.abcB);
#endif
#if GRAPHITE
	CHECK_EQUAL((UINT) 264, ABC.abcB); // probably rounding error
#endif

  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAbcB){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

#if UNISCRIBE
	CHECK_EQUAL((UINT) 262, ABC.abcB);
#endif
#if GRAPHITE
	CHECK_EQUAL((UINT) 264, ABC.abcB); // probably rounding error
#endif
  }

  TEST_FIXTURE(ArabicScriptPlaceLogical, ScriptPlace_LogicalOrder_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

#if UNISCRIBE
	CHECK_EQUAL(-1, ABC.abcC);
#endif
#if GRAPHITE
	CHECK_EQUAL(0, ABC.abcC); // probably rounding error
#endif
  }

  TEST_FIXTURE(ArabicScriptPlaceVisual, ScriptPlace_VisualOrder_GeneratesCorrectAbcC){
	HRESULT hResult = ScriptPlace(hdc, &sc, pwOutGlyphs, cGlyphs, psva, psa, piAdvance, pGoffset, &ABC);
	CHECK_EQUAL(S_OK, hResult);

#if UNISCRIBE
	CHECK_EQUAL(4, ABC.abcC);
#endif
#if GRAPHITE
	CHECK_EQUAL(0, ABC.abcC); // probably rounding error
#endif
  }
}