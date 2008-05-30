#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:UspAllocCache=" USP10DLL ".UspAllocCache")
#endif