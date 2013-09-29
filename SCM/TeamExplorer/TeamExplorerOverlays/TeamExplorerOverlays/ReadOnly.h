// ReadOnly.h : Declaration of the CReadOnly

#pragma once
#include "resource.h"       // main symbols
#include "TeamExplorerOverlays_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CReadOnly
class ATL_NO_VTABLE CReadOnly :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReadOnly, &CLSID_ReadOnly>,
	public IShellIconOverlayIdentifier, 
	public IDispatchImpl<IReadOnly, &IID_IReadOnly, &LIBID_TeamExplorerOverlaysLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CReadOnly()
	{
	}

	bool w2c(char *pcstr,const wchar_t *pwstr, size_t len);
	bool GetFatherPath(string sCrtPath, string &sFatherPath);
	void SetPathStatus(int iStatus);
	void SetPathStatusForNb(int iStatus);

	STDMETHOD(GetOverlayInfo)(LPWSTR pwszIconFile, int cchMax,int *pIndex,DWORD* pdwFlags);
	STDMETHOD(GetPriority)(int* pPriority);
	STDMETHOD(IsMemberOf)(LPCWSTR pwszPath,DWORD dwAttrib);

DECLARE_REGISTRY_RESOURCEID(IDR_READONLY)

BEGIN_COM_MAP(CReadOnly)
	COM_INTERFACE_ENTRY(IReadOnly)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

};

OBJECT_ENTRY_AUTO(__uuidof(ReadOnly), CReadOnly)
