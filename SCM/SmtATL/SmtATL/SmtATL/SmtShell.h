// SmtShell.h : Declaration of the CSmtShell

#pragma once
#include "resource.h"       // main symbols

#include "SmtATL_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CSmtShell
class ATL_NO_VTABLE CSmtShell :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSmtShell, &CLSID_SmtShell>,
	public IDispatchImpl<ISmtShell, &IID_ISmtShell, &LIBID_SmtATLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CSmtShell()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SMTSHELL)


BEGIN_COM_MAP(CSmtShell)
	COM_INTERFACE_ENTRY(ISmtShell)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		memset(m_szFile, 0, sizeof(m_szFile));
		memset(m_EnvPath, 0, sizeof(m_EnvPath));
		memset(m_InCtrNo, 0, sizeof(m_InCtrNo));
		m_InCtrCount = 0;
		m_NumFiles = 0;
		m_RecFileLen = 0;
		m_AddFlag = FALSE;
		m_FathAddFlag = FALSE;
		m_CouldAdd = FALSE;
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	virtual HRESULT STDMETHODCALLTYPE Initialize(__in_opt PCIDLIST_ABSOLUTE pidlFolder, __in_opt IDataObject *pdtobj, __in_opt HKEY hkeyProgID);
	virtual HRESULT STDMETHODCALLTYPE GetCommandString(THIS_ UINT_PTR idCmd, UINT uType, UINT *pwReserved, LPSTR pszName, UINT cchMax);
	virtual HRESULT STDMETHODCALLTYPE QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
	virtual HRESULT STDMETHODCALLTYPE InvokeCommand(__in CMINVOKECOMMANDINFO *pici);

	BOOL IsSamePath(string StatusStr, char *pPath);
	BOOL GetFatherPath(char *pCrtPath, char *pFatherPath);
	BOOL IsWorkEvn(char *pCrtPath, char *pRetPath);
	BOOL IsInCtr();
	BOOL IsFatherInCtr();
	BOOL IsHaveEnvPath();
	BOOL GetRepURL(char *pEnvPath, char *pRepURL);
	BOOL IsProductEnv();
	BOOL IsFatherAdd();
	string ExeCmd(char *pszCmd);

	char m_szFile[150][255];
	int m_InCtrNo[150];
	int m_InCtrCount;
	long m_RecFileLen;
	UINT m_NumFiles;
	BOOL m_AddFlag;
	BOOL m_FathAddFlag;
	BOOL m_CouldAdd;
	char m_EnvPath[255];
	STDMETHOD(SmtSetEnv)(void);
	STDMETHOD(SmtCheckout)(void);
	STDMETHOD(SmtUpdate)(void);
	STDMETHOD(SmtCommit)(void);
	STDMETHOD(SmtCheckin)(void);
	STDMETHOD(SmtCancel)(void);
	STDMETHOD(SmtAdd)(void);
	STDMETHOD(SmtRevert)(void);
	STDMETHOD(SmtMerge)(void);
	STDMETHOD(SmtImport)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(SmtShell), CSmtShell)
