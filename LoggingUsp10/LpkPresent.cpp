//#include "stdafx.h"

// Language Pack Present ???
// This is an undocumented function
// sets a global internal variable to indicate that the lpk dll is present.

#pragma comment(linker, "/export:LpkPresent=_usp10.LpkPresent")
//
//
///////   LpkPresent
//typedef __checkReturn void (CALLBACK* LPFNLPKPRESENT)(...);
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//__checkReturn void WINAPI LoggingLpkPresent()
//{
//  //6BD3EA19  mov         dword ptr ds:[6BD8B068h],1
//	WRAP_BEGIN(LpkPresent, LPFNLPKPRESENT)
//	LOG(L"<LpkPresent>");
//	LpkPresent();
//	LOG(L"</LpkPresent>");
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
