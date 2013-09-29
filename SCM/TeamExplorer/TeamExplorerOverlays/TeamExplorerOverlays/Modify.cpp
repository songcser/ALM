// Modify.cpp : Implementation of CModify

#include "stdafx.h"
#include "Modify.h"

extern bool IsModify;

// CModify
STDMETHODIMP CModify::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=3; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CModify::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CModify::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	if(IsModify){
		IsModify = false;
		return S_OK;
	}

	return S_FALSE;
}

