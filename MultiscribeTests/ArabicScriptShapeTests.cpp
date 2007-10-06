#include "stdafx.h"
#include "ScriptTests.h"

struct ArabicScriptLogical:ScriptTests{
  ArabicScriptLogical():ScriptTests(L"آسہ ست ݜِݜو",
#if UNISCRIBE
	L"Scheherazade"
#endif
#if GRAPHITE
	L"Scheherazade Graphite Alpha"
#endif
){
	assert(pItems[0].a.fRTL);
	assert(pItems[0].a.fLayoutRTL);

	psa->fLogicalOrder = true;
  }
};

struct ArabicScriptVisual:ScriptTests{
  ArabicScriptVisual():ScriptTests(L"آسہ ست ݜِݜو",
#if UNISCRIBE
	L"Scheherazade"
#endif
#if GRAPHITE
	L"Scheherazade Graphite Alpha"
#endif
){
	assert(pItems[0].a.fRTL);
	assert(pItems[0].a.fLayoutRTL);

	psa->fLogicalOrder = false;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// tests
SUITE(ArabicScriptShapeTests)
{
  TEST_FIXTURE(ArabicScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(12, cGlyphs);
	WORD pwExpectedGlyphs[] = {257,912,821,638,3,821,520,3,829,909,702,461};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, 10);
  }

  TEST_FIXTURE(ArabicScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectGlyphs){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	CHECK_EQUAL(12, cGlyphs);
	WORD pwExpectedGlyphs[] = {461,702,909,829,3,520,821,3,638,821,912,257};
	CHECK_ARRAY_EQUAL(pwExpectedGlyphs, pwOutGlyphs, 10);
  }

  TEST_FIXTURE(ArabicScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] = {0,0,2,3,4,5,6,7,8,8,10,11};
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(ArabicScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectLogClust){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	WORD pwExpectedLogClusts[] = {11,11,9,8,7,6,5,4,3,3,1,0};
	CHECK_ARRAY_EQUAL(pwExpectedLogClusts, pwLogClust, cChars);
  }

  TEST_FIXTURE(ArabicScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] = {1,0,1,1,1,1,1,1,1,0,1,1};
   int *pbActualIsClusterStart = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsClusterStart[i] = psva[i].fClusterStart;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsClusterStart,pbActualIsClusterStart,cGlyphs);
   }

  TEST_FIXTURE(ArabicScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectClusterStart){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsClusterStart[] = {1,1,0,1,1,1,1,1,1,1,0,1};

	int *pbActualIsClusterStart = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsClusterStart[i] = psva[i].fClusterStart;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsClusterStart,pbActualIsClusterStart,cGlyphs);
  }

  TEST_FIXTURE(ArabicScriptLogical, ScriptShape_LogicalOrder_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {0,1,0,0,0,0,0,0,0,1,0,0};
   int *pbActualIsDiacritic = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsDiacritic[i] = psva[i].fDiacritic;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsDiacritic,pbActualIsDiacritic,cGlyphs);
   }

  TEST_FIXTURE(ArabicScriptVisual, ScriptShape_VisualOrder_GeneratesCorrectDiacritic){
	HRESULT hResult = ScriptShape(hdc, &sc, pwcChars, cChars, cMaxGlyphs, psa, pwOutGlyphs, pwLogClust, psva, &cGlyphs);
	CHECK_EQUAL(S_OK, hResult);
	int pbExpectedIsDiacritic[] =    {0,0,1,0,0,0,0,0,0,0,1,0};
   int *pbActualIsDiacritic = new int[cGlyphs];

	for(int i=0; i!=cGlyphs; ++i){
	  pbActualIsDiacritic[i] = psva[i].fDiacritic;
	}
	CHECK_ARRAY_EQUAL(pbExpectedIsDiacritic,pbActualIsDiacritic,cGlyphs);
   }
}