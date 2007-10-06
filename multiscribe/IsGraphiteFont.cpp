#include "stdafx.h"

bool IsGraphiteFont(HDC hdc){
	assert(hdc);
	if(hdc){
		// try to find graphite table in font
		DWORD cbTable = GetFontData(hdc, 0x666c6953 /*Silf*/, 0, NULL, 0);
		return cbTable != GDI_ERROR && cbTable > 0;
	}
	return false;
}

std::wstring FontName(HDC hdc){
  std::wstring sFontName;
	assert(hdc);
	if(hdc){
	int cw = GetTextFace(hdc,0,NULL);
	WCHAR * szFontName = new WCHAR[cw];
	GetTextFace(hdc, cw, szFontName);
	sFontName = std::wstring(szFontName);
	delete[] szFontName;
  }
  return sFontName;
}