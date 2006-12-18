//#include "../stdafx.h"
#pragma comment(linker, "/export:ScriptCacheGetHeight=_usp10.ScriptCacheGetHeight")

/////   ScriptCacheGetHeight
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTCACHEGETHEIGHT)(
//    HDC                                     hdc,        // In    Optional (see notes on caching)
//    __deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
//    __out_ecount(1) long                    *tmHeight); // Out   Receives font height in pixels
//
//
//__checkReturn HRESULT WINAPI GraphiteEnabledScriptCacheGetHeight(
//    HDC                                     hdc,        // In    Optional (see notes on caching)
//    __deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
//    __out_ecount(1) long                    *tmHeight) // Out   Receives font height in pixels
//{
//	WRAP_BEGIN(ScriptCacheGetHeight, LPFNSCRIPTCACHEGETHEIGHT)
//	hResult = ScriptCacheGetHeight(hdc,psc,tmHeight);
//	WRAP_END
//}
//#ifdef __cplusplus
//}
//#endif
