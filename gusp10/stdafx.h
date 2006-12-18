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

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>


#define UNISCRIBE_OPENTYPE 0x0100

// TODO: reference additional headers your program requires here
#include <usp10.h>
#include <assert.h>
#include <stdio.h>
#include "stdafx.h"

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
