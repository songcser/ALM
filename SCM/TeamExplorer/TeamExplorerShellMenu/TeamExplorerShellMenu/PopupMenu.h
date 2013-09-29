// PopupMenu.h : Declaration of the CPopupMenu

#pragma once
#include "resource.h"       // main symbols
#include "TeamExplorerShellMenu_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CPopupMenu
class ATL_NO_VTABLE CPopupMenu :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPopupMenu, &CLSID_PopupMenu>,
	public IDispatchImpl<IPopupMenu, &IID_IPopupMenu, &LIBID_TeamExplorerShellMenuLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CPopupMenu()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POPUPMENU)

BEGIN_COM_MAP(CPopupMenu)
	COM_INTERFACE_ENTRY(IPopupMenu)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_NumFiles = 0;
		return S_OK;
	}

	void FinalRelease()
	{
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(__in_opt PCIDLIST_ABSOLUTE pidlFolder, __in_opt IDataObject *pdtobj, __in_opt HKEY hkeyProgID);
	virtual HRESULT STDMETHODCALLTYPE GetCommandString(THIS_ UINT_PTR idCmd, UINT uType, UINT *pwReserved, LPSTR pszName, UINT cchMax);
	virtual HRESULT STDMETHODCALLTYPE QueryContextMenu(THIS_ HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
	virtual HRESULT STDMETHODCALLTYPE InvokeCommand(__in CMINVOKECOMMANDINFO *pici);

public:
	int m_NumFiles;
	HMODULE m_hInstance;
	HBITMAP m_hPopupMenu;
	HBITMAP m_hAdd;
	HBITMAP m_hSetEnv;
	HBITMAP m_hCheckout;
	HBITMAP m_hUpdate;
	HBITMAP m_hCheckin;
	HBITMAP m_hCancel;
	HBITMAP m_hMerge;
	HBITMAP m_hRevert;
	HBITMAP m_hCommit;
	HBITMAP m_hShowLog;
	HBITMAP m_hDiff;
	HBITMAP m_hCompare;
	HBITMAP m_hDownload;
	vector<string> m_Files;
	vector<string> m_WriteFiles;
	string m_WcPath;

	STDMETHOD(SetEnv)(void);
	STDMETHOD(Checkout)(void);
	STDMETHOD(Update)(void);
	STDMETHOD(Commit)(void);
	STDMETHOD(Checkin)(void);
	STDMETHOD(Cancel)(void);
	STDMETHOD(Add)(void);
	STDMETHOD(Revert)(void);
	STDMETHOD(Merge)(void);
	STDMETHOD(ShowLog)(void);
	STDMETHOD(Diff)(void);
	STDMETHOD(Compare)(void);
	STDMETHOD(UpdateRelyFiles)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(PopupMenu), CPopupMenu)
