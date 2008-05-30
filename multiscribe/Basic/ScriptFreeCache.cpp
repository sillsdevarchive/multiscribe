#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"

#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:ScriptFreeCache=" USP10DLL ".ScriptFreeCache")
#endif

LPVOID GetOriginalScriptFreeCache();

/////   ScriptFreeCache
typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTFREECACHE) (
	__deref_inout_ecount(1) SCRIPT_CACHE   *psc);       //InOut  Cache handle


//#ifdef __cplusplus
//extern "C" {
//#endif
__checkReturn HRESULT WINAPI GraphiteEnabledScriptFreeCache(
	__deref_inout_ecount(1) SCRIPT_CACHE   *psc)       //InOut  Cache handle
{
	//WRAP_BEGIN(ScriptFreeCache, LPFNSCRIPTFREECACHE)
	LPFNSCRIPTFREECACHE ScriptFreeCache = (LPFNSCRIPTFREECACHE) GetOriginalScriptFreeCache();

	FreeGlyphPositionsForSession(*psc);
	HRESULT hResult = ScriptFreeCache(psc);
	return hResult;
	//WRAP_END
}
//#ifdef __cplusplus
//}
//#endif
