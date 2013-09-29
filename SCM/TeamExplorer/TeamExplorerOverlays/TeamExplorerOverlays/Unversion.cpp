// Unversion.cpp : Implementation of CUnversion

#include "stdafx.h"
#include "Unversion.h"

extern bool IsUnversion;

// CUnversion
STDMETHODIMP CUnversion::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=5; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CUnversion::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CUnversion::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	if(IsUnversion){
		IsUnversion = false;
		return S_OK;
	}

	return S_FALSE;
}

