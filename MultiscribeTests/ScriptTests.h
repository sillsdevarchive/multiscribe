#pragma once
#include <usp10.h>


// Test setup and teardown
struct ScriptTests{
  ScriptTests(std::wstring s, std::wstring sFontName):sInputString(s), hdc(NULL),hFont(NULL), hOrigFont(NULL), sc(NULL),cMaxItems(static_cast<int>(s.size())), cItemsProcessed(0),cGlyphs(0)
  {
	pItems = new SCRIPT_ITEM[cMaxItems];

	HRESULT hResult = ScriptItemize(sInputString.c_str(),
							static_cast<int>(sInputString.size()),
							cMaxItems,
							NULL,
							NULL,
							pItems,
							&cItemsProcessed);

	assert(S_OK == hResult);
	if (S_OK == hResult){
	  hdc = CreateCompatibleDC(NULL); // create a memory device context compatible with the current screen screen
	  assert(hdc != NULL);
	  int iResult = SetMapMode(hdc, MM_TEXT);
	  assert(iResult != 0);
	  if(iResult != 0){
		hFont = CreateFont(100,0,0,0,400,false,false,false,DEFAULT_CHARSET,OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH |FF_DONTCARE,sFontName.c_str());
		assert(hFont != NULL);
		if(hFont != NULL){
		  hOrigFont = SelectObject(hdc, hFont);

		  cMaxGlyphs = static_cast<int>(sInputString.size() + sInputString.size()/2) + 16;
		  pwcChars = sInputString.c_str() + pItems[0].iCharPos;
		  cChars = static_cast<int>(sInputString.size() - pItems[0].iCharPos);
		  psa = &pItems[0].a;
		  pwOutGlyphs = new WORD[cMaxGlyphs];
		  pwLogClust = new WORD[cChars];
		  psva = new SCRIPT_VISATTR[cMaxGlyphs]; // we alloc/free
		}
	  }
	}
  }

  ~ScriptTests(){
	delete[] pwOutGlyphs;
	delete[] pwLogClust;
	delete[] psva;
	HRESULT hResult = ScriptFreeCache(&sc);
	assert(S_OK == hResult);
	if(S_OK == hResult){
	  if(hdc != NULL){
		if(hFont != NULL){
		  SelectObject(hdc, hOrigFont);
		  BOOL result = DeleteObject(hFont);
		  assert(result != 0);result;
		}
		BOOL result = DeleteDC(hdc);
		assert(result != 0);result;
	  }
	}
  }

  std::wstring      sInputString;
  SCRIPT_CACHE      sc;
  int               cMaxItems;
  int               cItemsProcessed;
  int               cGlyphs;
  int               cChars;
  const WCHAR*      pwcChars;
  int               cMaxGlyphs;

  HDC               hdc;
  HFONT             hFont;
  HGDIOBJ           hOrigFont;

  SCRIPT_ANALYSIS*  psa;
  WORD*             pwOutGlyphs;
  WORD*             pwLogClust;
  SCRIPT_VISATTR*   psva;
  SCRIPT_ITEM *     pItems;
};
