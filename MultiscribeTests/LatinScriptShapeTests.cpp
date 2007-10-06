#include "stdafx.h"
#include "ScriptTests.h"

struct LatinScript:ScriptTests{
  LatinScript():ScriptTests(L"hè̱̟̆̃llo͠o world", L"Doulos SIL"){}//version 4.1
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(LatinScriptShapeTests)
{
  TEST_FIXTURE(LatinScript, ScriptShape_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(18, cGlyphs);
	WORD pwExpectedGlyphs[] = {75,72,1768,1793,1815,1835,1886,79,79,82,1822,82,3,90,82,85,79,71};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, cGlyphs);
  }

  TEST_FIXTURE(LatinScript, ScriptShape_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] =
#if UNISCRIBE
	  {0,1,1,1,1,1,1,7,8,9,9,11,12,13,14,15,16,17};
#endif
#if GRAPHITE
	  {0,1,1,1,1,1,1,7,8,9,10,11,12,13,14,15,16,17}; //graphite doesn't seem to be treating double wide tilde as a combining character
#endif
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(LatinScript, ScriptShape_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] =
#if UNISCRIBE
	  {1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1};
#endif
#if GRAPHITE
	  {1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1}; //graphite doesn't seem to be treating double wide tilde as a combining character
#endif

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsClusterStart[i], psva[i].fClusterStart);
	}
  }

  TEST_FIXTURE(LatinScript, ScriptShape_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0};

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsDiacritic[i], psva[i].fDiacritic);
	}
  }

}