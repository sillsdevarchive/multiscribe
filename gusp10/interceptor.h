#pragma once
#ifndef  INTERCEPTOR_
#define  INTERCEPTOR_

#include "udis86.h"

#ifdef _WIN64
#pragma message("64bit not supported")
#else

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#pragma warning(push)
#pragma warning(disable: 4311) //pointer truncation from 'type' to 'type'

#define JMP_SIZE 5
#define MAX_INSTRUCTION_SIZE 30 // the longest instruction size so far is 17 bytes but let's be conservative here
class Interceptor{

public:
	Interceptor(LPCSTR szLibFileName,
			  LPCSTR szOriginalFunctionName,
			  LPVOID InterceptingFunctionAddr)
  {
	  assert(szLibFileName);
	  assert(szOriginalFunctionName);
	assert(InterceptingFunctionAddr);
	  m_InjectedDllHandle=LoadLibraryA(szLibFileName);
	  assert(m_InjectedDllHandle);
	  if(m_InjectedDllHandle)
	  {
	  FARPROC pOriginalFunctionAddr = GetProcAddress(m_InjectedDllHandle,
												 szOriginalFunctionName);
		  Initialize(m_InjectedDllHandle, pOriginalFunctionAddr, InterceptingFunctionAddr);
	  if(pOriginalFunctionAddr){
			InstallInterceptor();
	  }
	  }
  }

	Interceptor(HINSTANCE hLibrary,
			  LPCSTR szOriginalFunctionName,
			  LPVOID InterceptingFunctionAddr)
  {
	  assert(hLibrary);
	  assert(szOriginalFunctionName);
	assert(InterceptingFunctionAddr);
	  if(hLibrary)
	  {
	  FARPROC pOriginalFunctionAddr = GetProcAddress(hLibrary, szOriginalFunctionName);
		  Initialize(NULL, pOriginalFunctionAddr, InterceptingFunctionAddr);
	  if(pOriginalFunctionAddr){
			InstallInterceptor();
	  }
	  }
  }

	Interceptor(LPVOID OriginalFunctionAddr, LPVOID InterceptingFunctionAddr)
  {
	  assert(OriginalFunctionAddr);
	assert(InterceptingFunctionAddr);
	  Initialize(NULL, OriginalFunctionAddr, InterceptingFunctionAddr);
	if(OriginalFunctionAddr){
		InstallInterceptor();
	}
  }

	~Interceptor()
  {
	  if(m_isInstalled){
		  RemoveInterceptor();
	  }

	  if(m_InjectedDllHandle){
		  //don't call this from dllmain it isn't safe
	  //(use constructor that provides handle so it won't get freed automatically)
		  FreeLibrary(m_InjectedDllHandle);
	  }
  }

	bool IsInstalled()
  {
	return m_isInstalled;
  }

	void InstallInterceptor()
  {
	assert(!m_isInstalled);
	  if(m_isInstalled){
		  return;
	  }
	  if(!m_OriginalFunctionAddr || !m_InterceptingFunctionAddr) {
		  return;
	  }

	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, (BYTE*)m_OriginalFunctionAddr, JMP_SIZE + MAX_INSTRUCTION_SIZE);
#ifdef _WIN64
	  ud_set_mode(&ud_obj, 64);
#else
	  ud_set_mode(&ud_obj, 32);
#endif

	  m_countBytes=0;
	  BYTE jumpByteCode[JMP_SIZE];

	  // save enough instructions from original to allow room for a jump

	  // we need at least JMP_SIZE bytes for our jump instruction and its address
	  // disassemble the machine code until we have identified more than JMP_SIZE instructions
	  while(m_countBytes<JMP_SIZE){
	  m_countBytes+=ud_disassemble(&ud_obj);
	  }
	  // copy these into our original prefix area (along with space for a final jump back instruction)
	  // aka trampoline function
	  m_OriginalFunctionByteCodePrefix=(BYTE*) VirtualAlloc(NULL,m_countBytes+JMP_SIZE,MEM_COMMIT,PAGE_EXECUTE_READWRITE);

	  DWORD dwOriginalProtection;
	  VirtualProtect(m_OriginalFunctionAddr, m_countBytes, PAGE_EXECUTE_READWRITE, &dwOriginalProtection); // unlock
	  memcpy(m_OriginalFunctionByteCodePrefix, m_OriginalFunctionAddr, m_countBytes);//save bytes

	  //overwrite original function with unconditional relative jump to our Interceptor function
	  // aka detour

	  //compute relative jump offset
	  DWORD OffsetFromOriginalToInterceptor = (DWORD)m_InterceptingFunctionAddr - (DWORD)m_OriginalFunctionAddr - JMP_SIZE;
	  jumpByteCode[0] = 0xe9; //relative 32-bit jmp instruction; address follows
	  jumpByteCode[1] = (BYTE)(OffsetFromOriginalToInterceptor & 0xff);
	  jumpByteCode[2] = (BYTE)((OffsetFromOriginalToInterceptor >> 8) & 0xff);
	  jumpByteCode[3] = (BYTE)((OffsetFromOriginalToInterceptor >> 16) & 0xff);
	  jumpByteCode[4] = (BYTE)((OffsetFromOriginalToInterceptor >> 24) & 0xff);
	  memcpy(m_OriginalFunctionAddr,jumpByteCode,JMP_SIZE);

	  //pad with noop 0x90
	  if(m_countBytes>JMP_SIZE){
		  memset((BYTE*)m_OriginalFunctionAddr+JMP_SIZE,0x90,m_countBytes-JMP_SIZE);
	  }

	  VirtualProtect(m_OriginalFunctionAddr, m_countBytes, dwOriginalProtection, &dwOriginalProtection);	//restore lock

	  // Add the final jump back instruction to original prefix area
	  // (since we moved the beginning of the original method, this allows it to continue
	  // with the rest of the function as though it had never been moved.

	  DWORD OffsetFromPrefixToOriginal = (DWORD)m_OriginalFunctionAddr - (DWORD)m_OriginalFunctionByteCodePrefix - JMP_SIZE;
	  jumpByteCode[0] = 0xe9; //relative 32-bit jmp instruction; address follows
	  jumpByteCode[1] = (BYTE)(OffsetFromPrefixToOriginal & 0xff);
	  jumpByteCode[2] = (BYTE)((OffsetFromPrefixToOriginal >> 8) & 0xff);
	  jumpByteCode[3] = (BYTE)((OffsetFromPrefixToOriginal >> 16) & 0xff);
	  jumpByteCode[4] = (BYTE)((OffsetFromPrefixToOriginal >> 24) & 0xff);
	  memcpy(m_OriginalFunctionByteCodePrefix+m_countBytes,jumpByteCode,JMP_SIZE);//overwrite with jump

	  m_isInstalled = true;
  }

	void RemoveInterceptor()
  {
	  assert(m_isInstalled);
	  if(!m_isInstalled){
		  return;
	  }

	  DWORD dwOriginalProtection;
	  VirtualProtect(m_OriginalFunctionAddr, m_countBytes, PAGE_EXECUTE_READWRITE, &dwOriginalProtection); // unlock
	  memcpy(m_OriginalFunctionAddr,m_OriginalFunctionByteCodePrefix,m_countBytes);//restore bytes
	  VirtualProtect(m_OriginalFunctionAddr, m_countBytes, dwOriginalProtection, &dwOriginalProtection);	//lock
	  VirtualFree(m_OriginalFunctionByteCodePrefix, m_countBytes+JMP_SIZE, MEM_DECOMMIT);
	  m_OriginalFunctionByteCodePrefix = NULL;
	  m_isInstalled = false;
  }

	LPVOID GetInterceptor()
  {
	  return m_InterceptingFunctionAddr;
  }

	LPVOID GetOriginal()
  {
	  return (m_isInstalled) ?  m_OriginalFunctionByteCodePrefix : m_OriginalFunctionAddr;
  }


private:
	void Initialize(HINSTANCE hLibrary,
				  LPVOID OriginalFunctionAddr,
				  LPVOID InterceptingFunctionAddr)
  {
	  m_InjectedDllHandle = hLibrary;

	  m_OriginalFunctionAddr=OriginalFunctionAddr;
	  m_InterceptingFunctionAddr=InterceptingFunctionAddr;

	  m_isInstalled = false;
  }

	bool m_isInstalled;

	LPVOID m_OriginalFunctionAddr;
	LPVOID m_InterceptingFunctionAddr;

	BYTE* m_OriginalFunctionByteCodePrefix;

	HINSTANCE m_InjectedDllHandle;

	int m_countBytes;
};
#pragma warning(pop)
#endif // _WIN64
#endif // INTERCEPTOR_