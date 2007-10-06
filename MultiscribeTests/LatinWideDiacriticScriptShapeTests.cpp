#include "stdafx.h"
#include "ScriptTests.h"

struct WideDiacriticLatinScript:ScriptTests{
  WideDiacriticLatinScript():ScriptTests(L"i̅ i̲", L"Doulos SIL"){}//version 4.1
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(LatinWideDiacriticScriptShapeTests)
{
  TEST_FIXTURE(WideDiacriticLatinScript, ScriptShape_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(5, cGlyphs);
	WORD pwExpectedGlyphs[] = {805,1843,3,76,1842};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, cGlyphs);
  }

  TEST_FIXTURE(WideDiacriticLatinScript, ScriptShape_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] = {0,0,2,3,3};
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(WideDiacriticLatinScript, ScriptShape_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] = {1,0,1,1,0};

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsClusterStart[i], psva[i].fClusterStart);
	}
  }

  TEST_FIXTURE(WideDiacriticLatinScript, ScriptShape_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {0,1,0,0,1};

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsDiacritic[i], psva[i].fDiacritic);
	}
  }

}