#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:UspAllocTemp=" USP10DLL ".UspAllocTemp")
#endif