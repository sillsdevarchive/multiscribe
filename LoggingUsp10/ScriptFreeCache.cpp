#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptFreeCache=_usp10.ScriptFreeCache")

/////   ScriptFreeCache
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTFREECACHE) (
	__deref_inout_ecount(1) SCRIPT_CACHE   *psc);       //InOut  Cache handle


#ifdef __cplusplus
extern "C" {
#endif
__checkReturn HRESULT WINAPI LoggingScriptFreeCache(
	__deref_inout_ecount(1) SCRIPT_CACHE   *psc)       //InOut  Cache handle
{
	WRAP_BEGIN(ScriptFreeCache, LPFNSCRIPTFREECACHE)
	LOG(L"<ScriptFreeCache>");
	LOG(L"<in>");
	LogScriptCache(psc);
	LOG(L"</in>");
	hResult = ScriptFreeCache(psc);
	LOG(L"</ScriptFreeCache>");
	WRAP_END
}
#ifdef __cplusplus
}
#endif
