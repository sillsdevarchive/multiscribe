#include "stdafx.h"
SUITE(ScriptItemizeTests){
TEST(ScriptItemize_pwcInCharsNull_EInvalidArg){
  int cMaxItems = 1;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed;
  CHECK_EQUAL(E_INVALIDARG, ScriptItemize(NULL, 1, cMaxItems, NULL, NULL, pItems, &cItemsProcessed));
  delete[] pItems;
}


TEST(ScriptItemize_cInChars0_EInvalidArg){
  int cMaxItems = 1;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed;
  CHECK_EQUAL(E_INVALIDARG, ScriptItemize(L"a", 0, cMaxItems, NULL, NULL, pItems, &cItemsProcessed));
  delete[] pItems;
}

TEST(ScriptItemize_cMaxItems1orless_EInvalidArg){
  int cMaxItems = 1;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed;
  HRESULT hResult = ScriptItemize(L"a", 1, cMaxItems, NULL, NULL, pItems, &cItemsProcessed);
  CHECK_EQUAL(E_INVALIDARG, hResult);
  delete[] pItems;
}


TEST(ScriptItemize_cMaxItemsInsufficient_EOutOfMemory){
  int cMaxItems = 2;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed;
  HRESULT hResult = ScriptItemize(L"a ก", 3, cMaxItems, NULL, NULL, pItems, &cItemsProcessed);
  CHECK_EQUAL(E_OUTOFMEMORY, hResult);
  delete[] pItems;
}

TEST(ScriptItemize_SameScript_1Item){
  int cMaxItems = 2;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed=0;
  CHECK_EQUAL(S_OK, ScriptItemize(L"a", 1, cMaxItems, NULL, NULL, pItems, &cItemsProcessed));
  CHECK_EQUAL(1, cItemsProcessed);
  delete[] pItems;
}

TEST(ScriptItemize_DifferentScripts_2Item){
  int cMaxItems = 4;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed=0;
  wchar_t* sz = L"a ก";
  CHECK_EQUAL(S_OK, ScriptItemize(sz, 3, cMaxItems, NULL, NULL, pItems, &cItemsProcessed));
  CHECK_EQUAL(2, cItemsProcessed);
  delete[] pItems;
}

const SCRIPT_PROPERTIES * GetScriptProperties(int i){
  const SCRIPT_PROPERTIES** pSpTable;
  int macScripts;
  HRESULT hr = ScriptGetProperties(&pSpTable, &macScripts);
  assert(hr == S_OK);
  if(hr == S_OK){
	if(i >= 0 && i < macScripts){
	  return pSpTable[i];
	}
  }
  return NULL;
}

TEST(ScriptItemize_ScriptProperties){
  int cMaxItems = 4;
  SCRIPT_ITEM * pItems = new SCRIPT_ITEM[cMaxItems];
  int cItemsProcessed=0;
  wchar_t* sz = L"رِنئ ߒ߬ߓߊ߬߸";
  CHECK_EQUAL(S_OK, ScriptItemize(sz, (int)wcslen(sz), cMaxItems, NULL, NULL, pItems, &cItemsProcessed));
  CHECK_EQUAL(0, pItems[0].iCharPos);
  CHECK_EQUAL(5, pItems[1].iCharPos);
  CHECK_EQUAL(1, pItems[0].a.fRTL);
  CHECK_EQUAL(1, pItems[1].a.fRTL);
  CHECK_EQUAL(0, pItems[0].a.fNoGlyphIndex);
  CHECK_EQUAL(0, pItems[1].a.fNoGlyphIndex);
  CHECK_EQUAL(26, pItems[0].a.eScript);
  CHECK_EQUAL(5, pItems[1].a.eScript);
  CHECK_EQUAL(2, cItemsProcessed);
  const SCRIPT_PROPERTIES * pspArabic = GetScriptProperties(pItems[0].a.eScript);
  const SCRIPT_PROPERTIES * pspNko = GetScriptProperties(pItems[1].a.eScript);

  CHECK_EQUAL((DWORD)178, pspArabic->bCharSet);
  CHECK_EQUAL((DWORD)1, pspArabic->fAmbiguousCharSet);
  CHECK_EQUAL((DWORD)0, pspArabic->fCDM);
  CHECK_EQUAL((DWORD)1, pspArabic->fClusterSizeVaries);
  CHECK_EQUAL((DWORD)1, pspArabic->fComplex);
  CHECK_EQUAL((DWORD)0, pspArabic->fControl);
  CHECK_EQUAL((DWORD)0, pspArabic->fInvalidGlyph);
  CHECK_EQUAL((DWORD)0, pspArabic->fInvalidLogAttr);
  CHECK_EQUAL((DWORD)0, pspArabic->fNeedsCaretInfo);
  CHECK_EQUAL((DWORD)0, pspArabic->fNeedsCharacterJustify);
  CHECK_EQUAL((DWORD)0, pspArabic->fNeedsWordBreaking);
  CHECK_EQUAL((DWORD)0, pspArabic->fNumeric);
  CHECK_EQUAL((DWORD)0, pspArabic->fPrivateUseArea);
  CHECK_EQUAL((DWORD)0, pspArabic->fRejectInvalid);
  CHECK_EQUAL((DWORD)1, pspArabic->langid);

  CHECK_EQUAL((DWORD)0, pspNko->bCharSet);
  CHECK_EQUAL((DWORD)1, pspNko->fAmbiguousCharSet);
  CHECK_EQUAL((DWORD)0, pspNko->fCDM);
  CHECK_EQUAL((DWORD)0, pspNko->fClusterSizeVaries);
  CHECK_EQUAL((DWORD)1, pspNko->fComplex);
  CHECK_EQUAL((DWORD)0, pspNko->fControl);
  CHECK_EQUAL((DWORD)0, pspNko->fInvalidGlyph);
  CHECK_EQUAL((DWORD)0, pspNko->fInvalidLogAttr);
  CHECK_EQUAL((DWORD)0, pspNko->fNeedsCaretInfo);
  CHECK_EQUAL((DWORD)0, pspNko->fNeedsCharacterJustify);
  CHECK_EQUAL((DWORD)0, pspNko->fNeedsWordBreaking);
  CHECK_EQUAL((DWORD)0, pspNko->fNumeric);
  CHECK_EQUAL((DWORD)0, pspNko->fPrivateUseArea);
  CHECK_EQUAL((DWORD)0, pspNko->fRejectInvalid);
  CHECK_EQUAL((DWORD)9, pspNko->langid);

  delete[] pItems;
}
}