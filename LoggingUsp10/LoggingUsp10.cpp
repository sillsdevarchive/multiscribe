// LoggingUsp10.cpp : Defines the entry point for the DLL application.
//

#include <stdio.h>
#include "stdafx.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

FILE *log;

void __cdecl LogToDebugger(LPWSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	int charsRequired = _vscwprintf(pszFormat, ptr)+1;
	WCHAR* szOutputBuffer = new WCHAR[charsRequired];
	if(vswprintf(szOutputBuffer, charsRequired, pszFormat, ptr) != -1){
		OutputDebugStringW(szOutputBuffer);
		OutputDebugStringW(L"\n");
	}
	va_end(ptr);
}

void __cdecl LogToFile(LPWSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);

	if(log){
		vfwprintf(log, pszFormat, ptr);
		fwprintf(log, L"\n");
	}
	va_end(ptr);
}

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	hModule;
	lpReserved;

	switch(ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			fopen_s( &log, "usp10.dll.log", "w, ccs=UTF-16LE"); // clear contents of file
			LOG(L"<?xml version='1.0' encoding='utf-16'?>");
			LOG(L"<usp10.dll>");
			break;
		case DLL_PROCESS_DETACH:
			LOG(L"</usp10.dll>");
			if(log){
				fclose(log);
			}
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		}


	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


void LogDigitSubstitution(
	__in_ecount(1) const SCRIPT_DIGITSUBSTITUTE *psds)  // In   Digit substitution settings
{
	LOG(L"<ScriptDigitSubstitute>");
	LOG(L"<NationalDigitLanguage>%d</NationalDigitLanguage>", psds->NationalDigitLanguage);
	LOG(L"<TraditionalDigitLanguage>%d</TraditionalDigitLanguage>", psds->TraditionalDigitLanguage);
	switch(psds->DigitSubstitute){
		case SCRIPT_DIGITSUBSTITUTE_CONTEXT:     // Substitute to match preceeding letters
			LOG(L"<DigitSubstitute type='Context'/>");
			break;
		case SCRIPT_DIGITSUBSTITUTE_NONE:        // No substitution
			LOG(L"<DigitSubstitute type='None'/>");
			break;
		case SCRIPT_DIGITSUBSTITUTE_NATIONAL:    // Substitute with official national digits
			LOG(L"<DigitSubstitute type='National'/>");
			break;
		case SCRIPT_DIGITSUBSTITUTE_TRADITIONAL: // Substitute with traditional digits of the locale
			LOG(L"<DigitSubstitute type='Traditional'/>");
			break;
	}
	LOG(L"<Reserved>%d</Reserved>", psds->dwReserved);
	LOG(L"</ScriptDigitSubstitute>");
}

void LogScriptControl(
	__in_ecount(1) const SCRIPT_CONTROL              *psc)   // In  Script control structure
{
	LOG(L"<ScriptControl>");
	LOG(L"<DefaultLanguage>%d</DefaultLanguage>", psc->uDefaultLanguage);
	if(psc->fContextDigits){
		LOG(L"<ContextDigits/>");
	}
	if(psc->fInvertPreBoundDir){
		LOG(L"<InvertPreBoundDir/>");
	}
	if(psc->fInvertPostBoundDir){
		LOG(L"<InvertPostBoundDir/>");
	}
	if(psc->fLinkStringBefore){
		LOG(L"<LinkStringBefore/>");
	}
	if(psc->fLinkStringAfter){
		LOG(L"<LinkStringAfter/>");
	}
	if(psc->fNeutralOverride){
		LOG(L"<NeutralOverride/>");
	}
	if(psc->fNumericOverride){
		LOG(L"<NumericOverride/>");
	}
	if(psc->fLegacyBidiClass){
		LOG(L"<LegacyBidiClass/>");
	}
#if defined(_MSC_VER) && (_MSC_VER >= 1400 )
	if(psc->fMergeNeutralItems){
		LOG(L"<MergeNeutralItems/>");
	}
#endif
	if(psc->fReserved){
		LOG(L"<Reserved>%d</Reserved>", psc->fReserved);
	}
	LOG(L"</ScriptControl>");
}

void LogScriptState(
	__in_ecount(1) const SCRIPT_STATE                *pss)  // In  Script state structure
{
	LOG(L"<ScriptState>");
	LOG(L"<BidiLevel>%d</BidiLevel>", pss->uBidiLevel);
	if(pss->fOverrideDirection){
		LOG(L"<OverrideDirection/>");
	}
	if(pss->fInhibitSymSwap){
		LOG(L"<InhibitSymSwap/>");
	}
	if(pss->fCharShape){
		LOG(L"<CharShape/>");
	}
	if(pss->fDigitSubstitute){
		LOG(L"<DigitSubstitute/>");
	}
	if(pss->fInhibitLigate){
		LOG(L"<InhibitLigate/>");
	}
	if(pss->fDisplayZWG){
		LOG(L"<DisplayZWG/>");
	}
	if(pss->fArabicNumContext){
		LOG(L"<ArabicNumContext/>");
	}
	if(pss->fGcpClusters){
		LOG(L"<GcpClusters/>");
	}
	if(pss->fReserved){
		LOG(L"<Reserved/>");
	}
	if(pss->fEngineReserved){
		LOG(L"<EngineReserved>%d</EngineReserved>", pss->fEngineReserved);
	}
	LOG(L"</ScriptState>");
}

void LogScriptVisualAttributes(
	__in_ecount(1) const SCRIPT_VISATTR   *psva)          // In     Visual attributes from ScriptShape/Place
{
	LOG(L"<VisualAttributes>");
	switch(psva->uJustification){ // Justification class
		case SCRIPT_JUSTIFY_NONE:             // Justification can't be applied at this glyph
			LOG(L"<Justification class='None'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_BLANK:     // This glyph represents a blank in an Arabic run
			LOG(L"<Justification class='ArabicBlank'/>");
			break;
		case SCRIPT_JUSTIFY_CHARACTER:        // Inter-character justification point follows this glyph
			LOG(L"<Justification class='Character'/>");
			break;
		case SCRIPT_JUSTIFY_RESERVED1:        // Reserved #1
			LOG(L"<Justification class='Reserved1'/>");
			break;
		case SCRIPT_JUSTIFY_BLANK:            // This glyph represents a blank outside an Arabic run
			LOG(L"<Justification class='Blank'/>");
			break;
		case SCRIPT_JUSTIFY_RESERVED2:        // Reserved #2
			LOG(L"<Justification class='Reserved2'/>");
			break;
		case SCRIPT_JUSTIFY_RESERVED3:        // Reserved #3
			LOG(L"<Justification class='Reserved3'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_NORMAL:    // Normal Middle-Of-Word glyph that connects to the right (begin)
			LOG(L"<Justification class='ArabicNormal'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_KASHIDA:   // Kashida(U+640) in middle of word
			LOG(L"<Justification class='ArabicKashida'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_ALEF:      // Final form of Alef-like (U+627, U+625, U+623, U+632)
			LOG(L"<Justification class='ArabicAlef'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_HA:        // Final form of Ha (U+647)
			LOG(L"<Justification class='ArabicHa'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_RA:        // Final form of Ra (U+631)
			LOG(L"<Justification class='ArabicRa'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_BA:        // Middle-Of-Word form of Ba (U+628)
			LOG(L"<Justification class='ArabicBa'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_BARA:      // Ligature of alike (U+628,U+631)
			LOG(L"<Justification class='ArabicBara'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_SEEN:      // Highest priority: Initial shape of Seen(U+633) (end)
			LOG(L"<Justification class='ArabicSeen'/>");
			break;
		case SCRIPT_JUSTIFY_ARABIC_SEEN_M:    // Reserved #4
			LOG(L"<Justification class='ArabicSeenM'/>");
			break;
	}
	if(psva->fClusterStart){
		LOG(L"<ClusterStart/>");
	}
	if(psva->fDiacritic){
		LOG(L"<Diacritic/>");
	}
	if(psva->fZeroWidth){
		LOG(L"<ZeroWidth/>");
	}
	if(psva->fReserved){
		LOG(L"<Reserved/>");
	}
	if(psva->fShapeReserved){
		LOG(L"<ShapeReserved>%d</ShapeReserved>", psva->fShapeReserved);
	}
	LOG(L"</VisualAttributes>");

}


void LogScriptAnalysis(
	__in_ecount(1) const SCRIPT_ANALYSIS        *psa)           // In     Script analysis from item attributes
{
	LOG(L"<ScriptAnalysis>");
	LOG(L"<ShapingEngine>%d</ShapingEngine>", psa->eScript);
	if(psa->fRTL){
		LOG(L"<RTL/>");
	}
	if(psa->fLayoutRTL){
		LOG(L"<LayoutRTL/>");
	}
	if(psa->fLinkBefore){
		LOG(L"<LinkBefore/>");
	}
	if(psa->fLinkAfter){
		LOG(L"<LinkAfter/>");
	}
	if(psa->fLogicalOrder){
		LOG(L"<LogicalOrder/>");
	}
	if(psa->fNoGlyphIndex){
		LOG(L"<NoGlyphIndex/>");
	}
	LogScriptState(&psa->s);
	LOG(L"</ScriptAnalysis>");
}

void LogABC(
	__in_ecount(1) const ABC                   *pABC)          // In Updated item ABC width
{
	LOG(L"<ABC>");
	LOG(L"<A underhang='%d'/>", pABC->abcA);
	LOG(L"<B characterWidth='%d'/>", pABC->abcB);
	LOG(L"<C overhang='%d'/>", pABC->abcC);
	LOG(L"</ABC>");
}

void LogScriptLogAttr(
	__in_ecount(1) const SCRIPT_LOGATTR    *psla)     //In  Logical character attributes
{
	LOG(L"<LogAttr>");
	if(psla->fSoftBreak)
	{
		LOG(L"<SoftBreak/>");
	}
	if(psla->fWhiteSpace)
	{
		LOG(L"<WhiteSpace/>");
	}
	if(psla->fCharStop)
	{
		LOG(L"<CharStop/>");
	}
	if(psla->fWordStop)
	{
		LOG(L"<WordStop/>");
	}
	if(psla->fInvalid)
	{
		LOG(L"<Invalid/>");
	}
	if(psla->fReserved)
	{
		LOG(L"<Reserved>%d</Reserved>", psla->fReserved);
	}
	LOG(L"</LogAttr>");
}

void LogString(
	__in_ecount(cChars) const WCHAR             *pwcChars,  // In   Logical unicode item
	int                                         cChars)     // In   Length of unicode item
{
	LOG(L"<Chars count='%d'>", cChars);
	for(int i=0; i<cChars; ++i){
		switch(pwcChars[i]){
			case '&':
				LOG(L"<Char hex='%04x'>&amp;</Char>", pwcChars[i]);
				break;
			case '<':
				LOG(L"<Char hex='%04x'>&lt;</Char>", pwcChars[i]);
				break;
			case '>':
				LOG(L"<Char hex='%04x'>&gt;</Char>", pwcChars[i]);
				break;
			default:
				LOG(L"<Char hex='%04x'>%c</Char>", pwcChars[i], pwcChars[i]);
		}
	}
	LOG(L"</Chars>");
}

void LogScriptStringAnalysis(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)            //In  Analysis with glyphs
{
	// unfortunately, undocumented.
}

void LogScriptCache(
	__in_ecount(1) const SCRIPT_CACHE    *psc)           // In Address of Cache handle
{
	// unfortunately, undocumented.
}

void LogExtTextOutOptions(
	UINT                                    uOptions)       //In  ExtTextOut options
{
	if(uOptions){
		LOG(L"<ExtTextOutOptions>");

		if(uOptions & ETO_CLIPPED){
			LOG(L"<Clipped/>");
		}
		if(uOptions & ETO_GLYPH_INDEX){
			LOG(L"<GlyphIndex/>");
		}
		if(uOptions & ETO_IGNORELANGUAGE){
			LOG(L"<IgnoreLanguage/>");
		}
		if(uOptions & ETO_NUMERICSLATIN){
			LOG(L"<NumericsLatin/>");
		}
		if(uOptions & ETO_NUMERICSLOCAL){
			LOG(L"<NumericsLocal/>");
		}
		if(uOptions & ETO_OPAQUE){
			LOG(L"<Opaque/>");
		}
		if(uOptions & ETO_PDY){
			LOG(L"<PDY/>");
		}
		if(uOptions & ETO_RTLREADING){
			LOG(L"<RightToLeft/>");
		}
		LOG(L"</ExtTextOutOptions>");
	}
}

void LogScriptItem(
	__in_ecount(1) const SCRIPT_ITEM  *pItem)        // In
{
	LOG(L"<ScriptItem offset='%d'>", pItem->iCharPos);
	LogScriptAnalysis(&pItem->a);
	LOG(L"</ScriptItem>");
}

void LogHResult(HRESULT hResult){
	switch(hResult){
		case S_OK:
			break;
		case USP_E_SCRIPT_NOT_IN_FONT :
			LOG(L"<result>USP_E_SCRIPT_NOT_IN_FONT</result>");
		default:
			LOG(L"<result>0x%x</result>", hResult);
	}
}
