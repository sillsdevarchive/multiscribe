#include "stdafx.h"
//#pragma comment(linker, "/export:ScriptGetProperties=_usp10.ScriptGetProperties")

///////////////////////////////////////////////////////////////////////////////////////////////////
// ScriptGetProperties
//
// Notes:
//   pppSp can be NULL
//   piNumScripts can be NULL
//   I don't expect both to be null though


typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTGETPROPERTIES) (
	__deref_out_ecount(1) const SCRIPT_PROPERTIES   ***pppSp,        // Out  Receives pointer to table of pointers to properties indexed by script
	__out_ecount(1) int                             *piNumScripts); // Out  Receives number of scripts (valid values are 0 through NumScripts-1)

#ifdef __cplusplus
extern "C" {
#endif
__checkReturn HRESULT WINAPI LoggingScriptGetProperties(
	__deref_out_ecount(1) const SCRIPT_PROPERTIES   ***pppSp,        // Out  Receives pointer to table of pointers to properties indexed by script
	__out_ecount(1) int                             *piNumScripts)  // Out  Receives number of scripts (valid values are 0 through NumScripts-1)
{
	WRAP_BEGIN(ScriptGetProperties, LPFNSCRIPTGETPROPERTIES)
	LOG(L"<ScriptGetProperties>");

	int iNumScripts;
	hResult = ScriptGetProperties(pppSp, &iNumScripts);
	if(piNumScripts){
		*piNumScripts = iNumScripts;
	}
	LOG(L"<out>");
	if(pppSp){
		LOG(L"<ScriptPropertiesTable>");
		for(int i = 0; i < iNumScripts; ++i){
			LOG(L"<ScriptProperties index='%d'>", i);
			LOG(L"<CharSet>%d</CharSet>", (*pppSp)[i]->bCharSet);
			LOG(L"<LanguageId>%d</LanguageId>", (*pppSp)[i]->langid);
			if((*pppSp)[i]->fAmbiguousCharSet){
				LOG(L"<AmbiguousCharSet/>");
			}
			if((*pppSp)[i]->fCDM){
				LOG(L"<ContainsCombiningDiacriticMarks/>");
			}
			if((*pppSp)[i]->fClusterSizeVaries){
				LOG(L"<ClusterSizeVaries/>");
			}
			if((*pppSp)[i]->fComplex){
				LOG(L"<Complex/>");
			}
			if((*pppSp)[i]->fControl){
				LOG(L"<Control/>");
			}
			if((*pppSp)[i]->fInvalidGlyph){
				LOG(L"<InvalidGlyph/>");
			}
			if((*pppSp)[i]->fInvalidLogAttr){
				LOG(L"<InvalidLogAttr/>");
			}
			if((*pppSp)[i]->fNeedsCaretInfo){
				LOG(L"<NeedsCaretInfo/>");
			}
			if((*pppSp)[i]->fNeedsCharacterJustify){
				LOG(L"<NeedsCharacterJustify/>");
			}
			if((*pppSp)[i]->fNeedsWordBreaking){
				LOG(L"<NeedsAlgorithmicWordBreaking/>");
			}
			if((*pppSp)[i]->fNumeric){
				LOG(L"<Numeric/>");
			}
			if((*pppSp)[i]->fPrivateUseArea){
				LOG(L"<PrivateUseArea/>");
			}
			if((*pppSp)[i]->fRejectInvalid){
				LOG(L"<RejectInvalid/>");
			}
			LOG(L"</ScriptProperties>");
		}
		LOG(L"</ScriptPropertiesTable>");
	}
	if(piNumScripts){
		LOG(L"<NumScripts>%d</NumScripts>", *piNumScripts);
	}
	LogHResult(hResult);
	LOG(L"</out>");

	LOG(L"</ScriptGetProperties>");
	WRAP_END
}

#ifdef __cplusplus
}
#endif
