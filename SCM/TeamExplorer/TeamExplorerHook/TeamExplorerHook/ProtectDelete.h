
#ifndef PROTECTDELETE
#define PROTECTDELETE extern "C" __declspec(dllimport)
#endif

PROTECTDELETE BOOL WINAPI ProtectDelete_HookAllApps(BOOL fInstall, DWORD dwThreadId);
