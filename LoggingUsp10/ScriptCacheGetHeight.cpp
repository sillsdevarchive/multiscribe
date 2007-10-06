#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptCacheGetHeight=_usp10.ScriptCacheGetHeight")

/////   ScriptCacheGetHeight
#ifdef __cplusplus
extern "C" {
#endif

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTCACHEGETHEIGHT)(
	HDC                                     hdc,        // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
	__out_ecount(1) long                    *tmHeight); // Out   Receives font height in pixels


__checkReturn HRESULT WINAPI LoggingScriptCacheGetHeight(
	HDC                                     hdc,        // In    Optional (see notes on caching)
	__deref_inout_ecount(1) SCRIPT_CACHE    *psc,       // InOut Address of Cache handle
	__out_ecount(1) long                    *tmHeight) // Out   Receives font height in pixels
{
	WRAP_BEGIN(ScriptCacheGetHeight, LPFNSCRIPTCACHEGETHEIGHT)
	LOG(L"<ScriptCacheGetHeight>");
	LOG(L"<in>");
  LogHdc(hdc);
	LOG(L"</in>");
	hResult = ScriptCacheGetHeight(hdc,psc,tmHeight);
	LOG(L"<out>");
	LogHResult(hResult);
	LOG(L"</out>");
	LOG(L"</ScriptCacheGetHeight>");
	WRAP_END

}
#ifdef __cplusplus
}
#endif
