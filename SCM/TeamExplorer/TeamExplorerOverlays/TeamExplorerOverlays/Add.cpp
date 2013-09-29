// Add.cpp : Implementation of CAdd

#include "stdafx.h"
#include "Add.h"

extern bool IsAdd;

// CAdd
STDMETHODIMP CAdd::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=1; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CAdd::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CAdd::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	if(IsAdd){
		IsAdd = false;
		return S_OK;
	}

	return S_FALSE;
}

