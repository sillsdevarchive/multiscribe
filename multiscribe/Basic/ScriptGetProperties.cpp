// we define this since it is typically only executed once and we need to have
// some function that we don't forward or we won't get loaded.
#include "../stdafx.h"
//static SCRIPT_PROPERTIES **gppScriptProperties;
//static int giNumScripts;
//
//HRESULT InitializeScriptProperties();

///////////////////////////////////////////////////////////////////////////////////////////////////
///// ScriptGetProperties
//#pragma comment(linker, "/export:ScriptGetProperties=_usp10.ScriptGetProperties")

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETPROPERTIES) (
	__deref_out_ecount(1) const SCRIPT_PROPERTIES   ***pppSp,        // Out  Receives pointer to table of pointers to properties indexed by script
	__out_ecount(1) int                             *piNumScripts); // Out  Receives number of scripts (valid values are 0 through NumScripts-1)

#ifdef __cplusplus
extern "C" {
#endif
__checkReturn HRESULT WINAPI GraphiteEnabledScriptGetProperties(
	__deref_out_ecount(1) const SCRIPT_PROPERTIES   ***pppSp,        // Out  Receives pointer to table of pointers to properties indexed by script
	__out_ecount(1) int                             *piNumScripts)  // Out  Receives number of scripts (valid values are 0 through NumScripts-1)
{
	WRAP_BEGIN(ScriptGetProperties, LPFNSCRIPTGETPROPERTIES)
	hResult = ScriptGetProperties(pppSp, piNumScripts);
	WRAP_END

	//if(piNumScripts){
	//	*piNumScripts = giNumScripts;
	//}
	//if(pppSp){
	//	if(!gppScriptProperties){ // hasn't been initialized yet, initialized first time called
	//		HRESULT hr = InitializeScriptProperties();
	//		if(FAILED(hr)){
	//			return hr;
	//		}
	//	}

	//	*pppSp = const_cast<const SCRIPT_PROPERTIES**>(gppScriptProperties);
	//}
	//return S_OK;
}
#ifdef __cplusplus
}
#endif

//SCRIPT_PROPERTIES * GetScriptPropertiesOfEngine(int i){
//	assert(i > 0 && i < giNumScripts);
//	if(i > 0 && i < giNumScripts){
//		return(gppScriptProperties[i]);
//	}
//	return NULL;
//}
//
//int GetGraphiteScriptId(){
//	return giNumScripts - 1;
//}
//
//void FreeScriptProperties(){
//	if(gppScriptProperties){
//		LocalFree(gppScriptProperties);
//	}
//}
//
//HRESULT InitializeScriptProperties(){
//	WRAP_BEGIN(ScriptGetProperties, LPFNSCRIPTGETPROPERTIES)
//
//	const SCRIPT_PROPERTIES ** ppSp;
//	hResult = ScriptGetProperties(&ppSp, &giNumScripts);
//	if (hResult == S_OK){
//		int iGraphiteScriptId = giNumScripts;
//		++giNumScripts; //allocate space for our generic graphite script
//
//		gppScriptProperties = (SCRIPT_PROPERTIES **)LocalAlloc(LPTR, giNumScripts*sizeof(SCRIPT_PROPERTIES *));
//		if(gppScriptProperties == NULL){
//			hResult = HRESULT_FROM_WIN32(GetLastError());
//		}
//		else {
//			for(int i = 0; i < giNumScripts-1; ++i){
//				gppScriptProperties[i] = (SCRIPT_PROPERTIES *)LocalAlloc(LPTR, sizeof(SCRIPT_PROPERTIES));
//				if(gppScriptProperties[i] == NULL) {
//					hResult = HRESULT_FROM_WIN32(GetLastError());
//				}
//				else {
//					memcpy_s(gppScriptProperties[i], sizeof(SCRIPT_PROPERTIES), ppSp[i], sizeof(SCRIPT_PROPERTIES));
//					if(gppScriptProperties[i]->langid != SCRIPT_UNDEFINED){
//						gppScriptProperties[i]->fComplex = true;
//					}
//				}
//			}
//			gppScriptProperties[iGraphiteScriptId] = (SCRIPT_PROPERTIES *)LocalAlloc(LPTR, sizeof(SCRIPT_PROPERTIES));
//			if(gppScriptProperties[iGraphiteScriptId] == NULL) {
//				hResult = HRESULT_FROM_WIN32(GetLastError());
//			}
//			else {
//				gppScriptProperties[iGraphiteScriptId]->langid = LANG_USER_DEFAULT; //TODO: figure out what should be here;
//				gppScriptProperties[iGraphiteScriptId]->fNumeric = false;
//				gppScriptProperties[iGraphiteScriptId]->fComplex = true;
//				gppScriptProperties[iGraphiteScriptId]->fNeedsWordBreaking = false; // we aren't up to handling this case
//				gppScriptProperties[iGraphiteScriptId]->fNeedsCaretInfo = false; // may need to make one with and one without this property
//				gppScriptProperties[iGraphiteScriptId]->bCharSet= DEFAULT_CHARSET;
//				gppScriptProperties[iGraphiteScriptId]->fControl=false;
//				gppScriptProperties[iGraphiteScriptId]->fPrivateUseArea=true;
//				gppScriptProperties[iGraphiteScriptId]->fNeedsCharacterJustify = false; // we may need to do something special with this one
//				gppScriptProperties[iGraphiteScriptId]->fInvalidGlyph=true;
//				gppScriptProperties[iGraphiteScriptId]->fInvalidLogAttr = false;
//				gppScriptProperties[iGraphiteScriptId]->fCDM = true;
//				gppScriptProperties[iGraphiteScriptId]->fAmbiguousCharSet=true;
//				gppScriptProperties[iGraphiteScriptId]->fClusterSizeVaries=true;
//			}
//		}
//	}
//
//	WRAP_END
//}