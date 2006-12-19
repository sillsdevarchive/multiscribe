#include <windows.h>
#include <stdio.h>
//#include "table.h"

#ifndef  hook_
#define  hook_

#define MAX 255
#define JMP_SIZE 5

void disasm(BYTE* iptr0, DWORD* osizeptr);


//license gpl /www.delikon.de
class Surrogate{

public:
	Surrogate(LPCSTR szLibFileName, LPCSTR szOriginalFuncName, LPVOID ReplaceFuncAddr);
	Surrogate(LPVOID OriginalFunctionAddr, LPVOID ReplaceFuncAddr);
	~Surrogate();

	bool IsInstalled();
	void InstallSurrogate();
	void RemoveSurrogate();
	LPVOID GetSurrogate();
	LPVOID GetOrginal();

private:
	void Initialize(LPVOID OriginalFunctionAddr, LPVOID ReplaceFuncAddr);

	bool m_isInstalled;

#if _DEBUG
	char m_OriginalFuncName[MAX+1];
#endif

	LPVOID m_OriginalFuncAddr;
	LPVOID m_ReplaceFuncAddr;

	BYTE* m_OriginalFuncByteCodePrefix;

	HINSTANCE m_InjectedDllHandle;

	int m_countBytes;
};

#endif