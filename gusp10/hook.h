#include <windows.h>
#include <stdio.h>
//#include "table.h"

#ifndef  hook_
#define  hook_

#define MAX 255
#define JMP_SIZE 5

void disasm(BYTE* iptr0, DWORD* osizeptr);


//license gpl /www.delikon.de
class Interceptor{

public:
	Interceptor(LPCSTR szLibFileName, LPCSTR szOriginalFuncName, LPVOID InterceptingFuncAddr);
	Interceptor(HINSTANCE hLibrary, LPCSTR szOriginalFuncName, LPVOID InterceptingFuncAddr);
	Interceptor(LPVOID OriginalFunctionAddr, LPVOID InterceptingFuncAddr);
	~Interceptor();

	bool IsInstalled();
	void InstallInterceptor();
	void RemoveInterceptor();
	LPVOID GetInterceptor();
	LPVOID GetOriginal();

private:
	void Initialize(HINSTANCE hLibrary, LPVOID OriginalFunctionAddr, LPVOID InterceptingFuncAddr);

	bool m_isInstalled;

#if _DEBUG
	char m_OriginalFuncName[MAX+1];
#endif

	LPVOID m_OriginalFuncAddr;
	LPVOID m_InterceptingFuncAddr;

	BYTE* m_OriginalFuncByteCodePrefix;

	HINSTANCE m_InjectedDllHandle;

	int m_countBytes;
};

#endif