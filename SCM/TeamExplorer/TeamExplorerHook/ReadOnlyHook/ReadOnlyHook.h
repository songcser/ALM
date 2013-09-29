// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the READONLYHOOK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// READONLYHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef READONLYHOOK_EXPORTS
#define READONLYHOOK_API __declspec(dllexport)
#else
#define READONLYHOOK_API __declspec(dllimport)
#endif

READONLYHOOK_API LRESULT WINAPI InstallHookProc(BOOL bInstall);
