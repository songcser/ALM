
#pragma once

class CAPIHook {
public:
	CAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook, 
		BOOL fExcludeAPIHookMod);

	~CAPIHook();

	operator PROC() { return(m_pfnOrig); }


public:
	static FARPROC WINAPI GetProcAddressRaw(HMODULE hmod, PCSTR pszProcName);

private:
	static PVOID sm_pvMaxAppAddr;
	static CAPIHook* sm_pHead;
	CAPIHook* m_pNext;

	PCSTR m_pszCalleeModName;
	PCSTR m_pszFuncName; 
	PROC  m_pfnOrig;
	PROC  m_pfnHook;
	BOOL  m_fExcludeAPIHookMod;

private:
	static void WINAPI ReplaceIATEntryInAllMods(PCSTR pszCalleeModName, 
		PROC pfnOrig, PROC pfnHook, BOOL fExcludeAPIHookMod);
	static void WINAPI ReplaceIATEntryInOneMod(PCSTR pszCalleeModName, 
		PROC pfnOrig, PROC pfnHook, HMODULE hmodCaller);

private:
	static void    WINAPI FixupNewlyLoadedModule(HMODULE hmod, DWORD dwFlags);
	static HMODULE WINAPI LoadLibraryA(PCSTR  pszModulePath);
	static HMODULE WINAPI LoadLibraryW(PCWSTR pszModulePath);
	static HMODULE WINAPI LoadLibraryExA(PCSTR  pszModulePath, 
		HANDLE hFile, DWORD dwFlags);
	static HMODULE WINAPI LoadLibraryExW(PCWSTR pszModulePath, 
		HANDLE hFile, DWORD dwFlags);
	static FARPROC WINAPI GetProcAddress(HMODULE hmod, PCSTR pszProcName);

private:
	static CAPIHook sm_LoadLibraryA;
	static CAPIHook sm_LoadLibraryW;
	static CAPIHook sm_LoadLibraryExA;
	static CAPIHook sm_LoadLibraryExW;
	static CAPIHook sm_GetProcAddress;
};
