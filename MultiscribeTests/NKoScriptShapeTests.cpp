#include "stdafx.h"
#include "ScriptTests.h"

struct NKoScriptLogical:ScriptTests{
  NKoScriptLogical():ScriptTests(L"ߒ߬ߓߊ߬߸ ߟߏ߲ ߘߏ߫", L"N'ko Kankan"){
	//assert(pItems[0].a.fRTL);
	//assert(pItems[0].a.fLayoutRTL);

	psa->fLogicalOrder = true;
  }
};

struct NKoScriptVisual:ScriptTests{
  NKoScriptVisual():ScriptTests(L"ߒ߬ߓߊ߬߸ ߟߏ߲ ߘߏ߫", L"N'ko Kankan"){
	//assert(pItems[0].a.fRTL);
	//assert(pItems[0].a.fLayoutRTL);

	psa->fLogicalOrder = false;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(NKoScriptShapeTests)
{
  TEST_FIXTURE(NKoScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(13, cGlyphs);
	WORD pwExpectedGlyphs[] = {105,68,107,83,68,80,3,144,233,3,123,97,67};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, cGlyphs);
  }

  TEST_FIXTURE(NKoScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(13, cGlyphs);
	WORD pwExpectedGlyphs[] = {67,97,123,3,233,144,3,80,68,83,107,68,105};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, cGlyphs);
  }

  TEST_FIXTURE(NKoScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] = {0,0,2,3,3,5,6,7,8,9,10,11,12,12};
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(NKoScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] = {12,12,11,10,9,8,7,6,5,3,3,2,0,0};
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(NKoScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] = {1,0,1,1,0,1,1,1,1,1,1,1,0};
	int *pbActualIsClusterStart = new int[cGlyphs];
	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsClusterStart[i] = psva[i].fClusterStart;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsClusterStart,pbActualIsClusterStart,cGlyphs);
  }

  TEST_FIXTURE(NKoScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] = {0,1,1,1,1,1,1,1,0,1,1,0,1};
	int *pbActualIsClusterStart = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsClusterStart[i] = psva[i].fClusterStart;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsClusterStart,pbActualIsClusterStart,cGlyphs);
  }

  TEST_FIXTURE(NKoScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {0,1,0,0,1,0,0,0,0,0,0,0,1};
	int *pbActualIsDiacritic = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsDiacritic[i] = psva[i].fDiacritic;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsDiacritic,pbActualIsDiacritic,cGlyphs);
 }

  TEST_FIXTURE(NKoScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {1,0,0,0,0,0,0,0,1,0,0,1,0};

	int *pbActualIsDiacritic = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsDiacritic[i] = psva[i].fDiacritic;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsDiacritic,pbActualIsDiacritic,cGlyphs);
  }
}