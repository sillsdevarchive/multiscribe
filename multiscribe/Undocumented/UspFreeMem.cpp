#include "../stdafx.h"
#ifdef IMPERSONATE_USP10
#pragma comment(linker, "/export:UspFreeMem=" USP10DLL ".UspFreeMem")
#endif