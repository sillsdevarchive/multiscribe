#include "stdafx.h"
#include "ScriptTests.h"

struct ToneBarsLatinScript:ScriptTests{
  ToneBarsLatinScript():ScriptTests(L"˥˧˥˩ ˥˩˧˨˦˩˥", L"Doulos SIL"){}//version 4.1
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(LatinToneBarsScriptShapeTests)
{
  TEST_FIXTURE(ToneBarsLatinScript, ScriptShape_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(12, cGlyphs);
	WORD pwExpectedGlyphs[] = {1956,1948,1954,1924,3,1954,1936,1945,1942,1949,1938,1928};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, cGlyphs);
  }

  TEST_FIXTURE(ToneBarsLatinScript, ScriptShape_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] =
#if UNISCRIBE
	  {0,1,2,3,4,5,6,7,8,9,10,11};
#endif
#if GRAPHITE
	{0,0,0,0,4,5,5,5,5,5,5,5}; // graphite is treating tone letters as forming a cluster
#endif
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(ToneBarsLatinScript, ScriptShape_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] =
#if UNISCRIBE
	  {1,1,1,1,1,1,1,1,1,1,1,1};
#endif
#if GRAPHITE
	  {1,0,0,0,1,1,0,0,0,0,0,0}; // graphite is treating tone letters as forming a cluster
#endif

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsClusterStart[i], psva[i].fClusterStart);
	}
  }

  TEST_FIXTURE(ToneBarsLatinScript, ScriptShape_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =
#if UNISCRIBE
	   {0,0,0,0,0,0,0,0,0,0,0,0};
#endif
#if GRAPHITE
	 {0,1,1,1,0,0,1,1,1,1,1,1};
#endif

	for(int i=0; i!=cGlyphs; ++i){
	  CHECK_EQUAL(pbExpectedIsDiacritic[i], psva[i].fDiacritic);
	}
  }

}