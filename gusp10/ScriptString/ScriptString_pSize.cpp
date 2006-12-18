#include "../stdafx.h"
#include "../GraphiteScriptStringAnalysis.h"
#include <math.h>

/////   ScriptStringSize
typedef const SIZE* (CALLBACK* LPFNSCRIPTSTRING_PSIZE) (
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa);

#ifdef __cplusplus
extern "C" {
#endif

const SIZE* WINAPI GraphiteEnabledScriptString_pSize(
	__in_ecount(1) SCRIPT_STRING_ANALYSIS   ssa)
{
	GRAPHITE_SCRIPT_STRING_ANALYSIS *pgssa = GetGraphiteScriptStringAnalysis(ssa);
	if(pgssa){
		pgssa->size.cx = 0;
		pgssa->size.cy = 0;
		HDC hdc = pgssa->hdc;
		assert(hdc);
		if(hdc){
			gr::Rect boundingRect = pgssa->pSegment->boundingRect();
			float boundingWidth = abs(boundingRect.right - boundingRect.left);
			pgssa->size.cx = static_cast<int>(ceil(boundingWidth));
			float boundingHeight = abs(boundingRect.bottom - boundingRect.top);
			pgssa->size.cy = static_cast<int>(ceil(boundingHeight));
		}
		return &pgssa->size;
	}
	else{
		WRAP_BEGIN_RETURNING(ScriptString_pSize, LPFNSCRIPTSTRING_PSIZE, const SIZE*, result, NULL)
		result = ScriptString_pSize(ssa);
		WRAP_END_RETURNING(result, NULL)
	}
}
#ifdef __cplusplus
}
#endif
