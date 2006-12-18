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
