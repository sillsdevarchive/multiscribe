// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

// Header Annotations are defined in Visual Studio.Net 2005, but not in VS.Net 2003
// 1400 = VS.Net 2005
// 1310 =        2003
// 1300 =        2002
#if defined(_MSC_VER) && (_MSC_VER < 1400 )
#define __checkReturn
#define __deref_inout_ecount(a)
#define __in_ecount(a)
#define __inout_ecount(a)
#define __inout_ecount_opt(a)
#define __out_ecount(a)
#define __out_ecount_part(a,b)
#define __out_ecount_full(a)
#define __out_ecount_full_opt(a)
#define __deref_out_ecount(a)
#define __in_ecount_opt(a)
#define __in_opt
#define __inout
#define __in
#define __out
#define __out_opt
#define __reserved
#endif

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>


//#define UNISCRIBE_OPENTYPE 0x0100

//#define INTERCEPT_SCRIPTITEMIZE 1

#include <usp10.h>
#include <assert.h>
#include <stdio.h>
#include <string>
//#include "stdafx.h"

#include <GrClient.h> // this should be in GrFeature.h
#include <GrAppData.h> // this should be in font.h and GrFeature.h
#include <GrFeature.h> // this should be in font.h
#include <GrResult.h> // this should be in font.h
#include <Font.h> //this should be in winfont.h
#include <hash_map> // this should be in winfont.h
#include <WinFont.h>
#include <SegmentAux.h> // this should be in segment.h
#include <Segment.h> // this should be in SegmentPainter.h
#include <SegmentPainter.h> // this should be in WinSegmentPainter.h
#include <WinSegmentPainter.h>
#include <ITextSource.h>

#include <math.h>

//#if USPBUILD <= 0400
typedef ULONG OPENTYPE_TAG;

typedef struct opentype_feature_record{
  OPENTYPE_TAG  tagFeature;
  LONG  lParameter;
} OPENTYPE_FEATURE_RECORD;

typedef struct textrange_properties{
	OPENTYPE_FEATURE_RECORD*   potfRecords;
	int cotfRecords;
} TEXTRANGE_PROPERTIES;

typedef struct script_charprop{
	WORD           fCanGlyphAlone : 1;
	WORD           reserved       : 15;
} SCRIPT_CHARPROP;

typedef struct script_glyphprop {
	SCRIPT_VISATTR sva;
	WORD reserved;
} SCRIPT_GLYPHPROP;
//#endif

bool IsGraphiteFont(HDC hdc);


#define WRAP_BEGIN_RETURNING(function_name, function_type, return_type, return_variable_name, error_return_value) 	\
	return_type return_variable_name; \
	HINSTANCE handle; \
	FARPROC function; \
	handle = LoadLibraryA("_usp10.dll"); \
	if(handle == NULL){ \
		return error_return_value; \
	} \
	function = GetProcAddress(handle, #function_name); \
	if(!function){ \
		return_variable_name = error_return_value; \
	} \
	else{ \
		function_type function_name = (function_type) function;

#define WRAP_END_FINAL(error_return_value) \
	} \
	if(!FreeLibrary(handle)){ \
		return error_return_value;  \
	}

#define WRAP_END_FINAL_RETURNING(return_variable_name, error_return_value) \
	WRAP_END_FINAL(error_return_value) \
	return return_variable_name;

#define WRAP_BEGIN(function_name, function_type) 	\
	WRAP_BEGIN_RETURNING(function_name, function_type, HRESULT, hResult, HRESULT_FROM_WIN32(GetLastError()))

#define WRAP_END \
	WRAP_END_FINAL_RETURNING(hResult, HRESULT_FROM_WIN32(GetLastError()))

#define WRAP_END_NO_RETURN \
	WRAP_END_FINAL(HRESULT_FROM_WIN32(GetLastError()))

#define WRAP_END_RETURNING(return_variable_name, error_return_value) \
	WRAP_END_FINAL_RETURNING(return_variable_name, error_return_value)

float round(float f);
