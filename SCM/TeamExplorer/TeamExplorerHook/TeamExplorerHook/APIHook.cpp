#include "CmnHdr.h"
#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")

#include "APIHook.h"
#include "Toolhelp.h"

PVOID CAPIHook::sm_pvMaxAppAddr = NULL;
const BYTE cPushOpCode = 0x68;

CAPIHook* CAPIHook::sm_pHead = NULL;

CAPIHook::CAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook, 
	BOOL fExcludeAPIHookMod) 
{
	if (sm_pvMaxAppAddr == NULL) {
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		sm_pvMaxAppAddr = si.lpMaximumApplicationAddress;
	}

	m_pNext  = sm_pHead;
	sm_pHead = this;

	m_pszCalleeModName   = pszCalleeModName;
	m_pszFuncName        = pszFuncName;
	m_pfnHook            = pfnHook;
	m_fExcludeAPIHookMod = fExcludeAPIHookMod;
	m_pfnOrig            = GetProcAddressRaw(GetModuleHandleA(pszCalleeModName), 
		m_pszFuncName);
	chASSERT(m_pfnOrig != NULL);

	if (m_pfnOrig > sm_pvMaxAppAddr) {
		PBYTE pb = (PBYTE) m_pfnOrig;
		if (pb[0] == cPushOpCode) {
			PVOID pv = * (PVOID*) &pb[1];
			m_pfnOrig = (PROC) pv;
		}
	}

	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnOrig, m_pfnHook, 
		m_fExcludeAPIHookMod);
}

CAPIHook::~CAPIHook() 
{
	ReplaceIATEntryInAllMods(m_pszCalleeModName, m_pfnHook, m_pfnOrig, 
		m_fExcludeAPIHookMod);

	CAPIHook* p = sm_pHead; 
	if (p == this) {
		sm_pHead = p->m_pNext; 
	} else {

		BOOL fFound = FALSE;

		for (; !fFound && (p->m_pNext != NULL); p = p->m_pNext) {
			if (p->m_pNext == this) { 
				p->m_pNext = p->m_pNext->m_pNext; 
				break; 
			}
		}
		chASSERT(fFound);
	}
}

FARPROC CAPIHook::GetProcAddressRaw(HMODULE hmod, PCSTR pszProcName) 
{

	return(::GetProcAddress(hmod, pszProcName));
}

static HMODULE ModuleFromAddress(PVOID pv) 
{
	MEMORY_BASIC_INFORMATION mbi;
	return((VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
		? (HMODULE) mbi.AllocationBase : NULL);
}

void CAPIHook::ReplaceIATEntryInAllMods(PCSTR pszCalleeModName, 
	PROC pfnCurrent, PROC pfnNew, BOOL fExcludeAPIHookMod) 
{
	HMODULE hmodThisMod = fExcludeAPIHookMod 
		? ModuleFromAddress(ReplaceIATEntryInAllMods) : NULL;

	CToolhelp th(TH32CS_SNAPMODULE, GetCurrentProcessId());

	MODULEENTRY32 me = { sizeof(me) };
	for (BOOL fOk = th.ModuleFirst(&me); fOk; fOk = th.ModuleNext(&me)) {
		if (me.hModule != hmodThisMod) {
			ReplaceIATEntryInOneMod(
				pszCalleeModName, pfnCurrent, pfnNew, me.hModule);
		}
	}
}

void CAPIHook::ReplaceIATEntryInOneMod(PCSTR pszCalleeModName, 
	PROC pfnCurrent, PROC pfnNew, HMODULE hmodCaller) 
{
	ULONG ulSize;
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)
		ImageDirectoryEntryToData(hmodCaller, TRUE, 
		IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

	if (pImportDesc == NULL)
		return;

	for (; pImportDesc->Name; pImportDesc++) {
		PSTR pszModName = (PSTR) ((PBYTE) hmodCaller + pImportDesc->Name);
		if (lstrcmpiA(pszModName, pszCalleeModName) == 0) 
			break;
	}

	if (pImportDesc->Name == 0)
		return;

	PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA) 
		((PBYTE) hmodCaller + pImportDesc->FirstThunk);

	for (; pThunk->u1.Function; pThunk++) {
		PROC* ppfn = (PROC*) &pThunk->u1.Function;

		BOOL fFound = (*ppfn == pfnCurrent);

		if (!fFound && (*ppfn > sm_pvMaxAppAddr)) {
			PBYTE pbInFunc = (PBYTE) *ppfn;
			if (pbInFunc[0] == cPushOpCode) {
				ppfn = (PROC*) &pbInFunc[1];
				fFound = (*ppfn == pfnCurrent);
			}
		}

		if (fFound) {
			WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew, 
				sizeof(pfnNew), NULL);

			return;
		}
	}
}

CAPIHook CAPIHook::sm_LoadLibraryA  ("Kernel32.dll", "LoadLibraryA",   
	(PROC) CAPIHook::LoadLibraryA, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryW  ("Kernel32.dll", "LoadLibraryW",   
	(PROC) CAPIHook::LoadLibraryW, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryExA("Kernel32.dll", "LoadLibraryExA", 
	(PROC) CAPIHook::LoadLibraryExA, TRUE);

CAPIHook CAPIHook::sm_LoadLibraryExW("Kernel32.dll", "LoadLibraryExW", 
	(PROC) CAPIHook::LoadLibraryExW, TRUE);

CAPIHook CAPIHook::sm_GetProcAddress("Kernel32.dll", "GetProcAddress", 
	(PROC) CAPIHook::GetProcAddress, TRUE);

void CAPIHook::FixupNewlyLoadedModule(HMODULE hmod, DWORD dwFlags) 
{
	if ((hmod != NULL) && ((dwFlags & LOAD_LIBRARY_AS_DATAFILE) == 0)) {

		for (CAPIHook* p = sm_pHead; p != NULL; p = p->m_pNext) {
			ReplaceIATEntryInOneMod(p->m_pszCalleeModName, 
				p->m_pfnOrig, p->m_pfnHook, hmod);
		}
	}
}

HMODULE WINAPI CAPIHook::LoadLibraryA(PCSTR pszModulePath) 
{
	HMODULE hmod = ::LoadLibraryA(pszModulePath);
	FixupNewlyLoadedModule(hmod, 0);
	return(hmod);
}

HMODULE WINAPI CAPIHook::LoadLibraryW(PCWSTR pszModulePath) 
{
	HMODULE hmod = ::LoadLibraryW(pszModulePath);
	FixupNewlyLoadedModule(hmod, 0);
	return(hmod);
}

HMODULE WINAPI CAPIHook::LoadLibraryExA(PCSTR pszModulePath, 
	HANDLE hFile, DWORD dwFlags) 
{
	HMODULE hmod = ::LoadLibraryExA(pszModulePath, hFile, dwFlags);
	FixupNewlyLoadedModule(hmod, dwFlags);
	return(hmod);
}

HMODULE WINAPI CAPIHook::LoadLibraryExW(PCWSTR pszModulePath, 
	HANDLE hFile, DWORD dwFlags) 
{
	HMODULE hmod = ::LoadLibraryExW(pszModulePath, hFile, dwFlags);
	FixupNewlyLoadedModule(hmod, dwFlags);
	return(hmod);
}

FARPROC WINAPI CAPIHook::GetProcAddress(HMODULE hmod, PCSTR pszProcName) 
{
	FARPROC pfn = GetProcAddressRaw(hmod, pszProcName);

	CAPIHook* p = sm_pHead;
	for (; (pfn != NULL) && (p != NULL); p = p->m_pNext) {

		if (pfn == p->m_pfnOrig) {
			pfn = p->m_pfnHook;
			break;
		}
	}

	return(pfn);
}
