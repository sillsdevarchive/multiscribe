#pragma comment(linker, "/export:ScriptShape=_usp10.ScriptShape")

#include "../stdafx.h"
#include "../GlyphsToTextSourceMap.h"
#include <utility>
#include <limits>
LPVOID GetOriginalScriptShape();


///////////////////////////////////////////////////////////////////////////////////////////////////
/////   ScriptShape

typedef __checkReturn HRESULT (CALLBACK* LPFNSCRIPTSHAPE) (
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs);     // Out   Count of glyphs generated

//#ifdef __cplusplus
//extern "C" {
//#endif
__checkReturn HRESULT WINAPI GraphiteEnabledScriptShape(
	HDC                                                     hdc,            // In    Optional (see under caching)
	__deref_inout_ecount(1) SCRIPT_CACHE                    *psc,           // InOut Cache handle
	__in_ecount(cChars) const WCHAR                         *pwcChars,      // In    Logical unicode run
	int                                                     cChars,         // In    Length of unicode run
	int                                                     cMaxGlyphs,     // In    Max glyphs to generate
	__inout_ecount(1) SCRIPT_ANALYSIS                       *psa,           // InOut Result of ScriptItemize (may have fNoGlyphIndex set)
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) WORD           *pwOutGlyphs,   // Out   Output glyph buffer
	__out_ecount_full(cChars) WORD                          *pwLogClust,    // Out   Logical clusters
	__out_ecount_part(cMaxGlyphs, *pcGlyphs) SCRIPT_VISATTR *psva,          // Out   Visual glyph attributes
	__out_ecount(1) int                                     *pcGlyphs)     // Out   Count of glyphs generated
{
	if(!hdc){ //TODO: keep a cache
		return E_PENDING;
	}
	LPFNSCRIPTSHAPE ScriptShape = (LPFNSCRIPTSHAPE) GetOriginalScriptShape();

	if(IsGraphiteFont(hdc))
	{
		if(!psc)
		{
			HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
			hResult;
			//WRAP_BEGIN(ScriptShape, LPFNSCRIPTSHAPE)
			//// only to setup the cache correctly:
			//hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
			//WRAP_END_NO_RETURN
		}

		 TextSource textSource(pwcChars, cChars);
		 textSource.setRightToLeft(psa->fRTL);

		// Create the Graphite font object.
		gr::WinFont font(hdc);

		// Create the segment.
		gr::LayoutEnvironment layout;	// use all the defaults...
		layout.setDumbFallback(true);	// except that we want it to try its best, no matter what
		gr::RangeSegment seg(&font, &textSource, &layout);

		std::pair<gr::GlyphIterator, gr::GlyphIterator> prGlyphIterators =
			seg.glyphs();

		std::vector<gr::GlyphInfo> rgGlyphInfo;

		for(gr::GlyphIterator it = prGlyphIterators.first;
							  it != prGlyphIterators.second;
							  ++it){
			rgGlyphInfo.push_back(*it);
		}

		// if the output buffer length, cMaxGlyphs, is insufficient.
		if(rgGlyphInfo.size() >  static_cast<size_t>(std::max(cMaxGlyphs,0))){
			return E_OUTOFMEMORY;
		}

		*pcGlyphs = static_cast<int>(rgGlyphInfo.size());



		int * rgFirstGlyphOfCluster = new int [cChars];
		bool * rgIsClusterStart = new bool [*pcGlyphs];
		int cCharsX, cgidX;
		seg.getUniscribeClusters(rgFirstGlyphOfCluster, cChars, &cCharsX,
								 rgIsClusterStart, *pcGlyphs, &cgidX);


		for(int i=0; i != *pcGlyphs; ++i){
		  pwOutGlyphs[i] = rgGlyphInfo[i].glyphID();
		  psva[i].fClusterStart = rgIsClusterStart[i];
		  psva[i].fDiacritic = rgGlyphInfo[i].isAttached(); // VERIFY
		  psva[i].fZeroWidth = false; // TODO: when does this need to be set?
		  psva[i].uJustification = SCRIPT_JUSTIFY_NONE; //TODO: when does this need to change
		}

		delete[] rgIsClusterStart;

		for(int i=0; i < cChars; ++i){
			pwLogClust[i] = static_cast<WORD>(rgFirstGlyphOfCluster[i]);
		}

		delete[] rgFirstGlyphOfCluster;

		TextSource * pTextSource = CreateTextSource(pwOutGlyphs, *pcGlyphs);
		*pTextSource = textSource;
		return S_OK;
	}
	else
	{
		HRESULT hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
		return hResult;
		//WRAP_BEGIN(ScriptShape, LPFNSCRIPTSHAPE)
		//hResult = ScriptShape(hdc,psc,pwcChars,cChars,cMaxGlyphs,psa,pwOutGlyphs,pwLogClust, psva,pcGlyphs);
	 //   WRAP_END
	}
}
//#ifdef __cplusplus
//}
//#endif
