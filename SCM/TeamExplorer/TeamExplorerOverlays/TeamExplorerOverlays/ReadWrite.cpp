// ReadWrite.cpp : Implementation of CReadWrite

#include "stdafx.h"
#include "ReadWrite.h"

extern bool IsReadWrite;

// CReadWrite

STDMETHODIMP CReadWrite::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=2; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CReadWrite::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CReadWrite::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	if(IsReadWrite){
		IsReadWrite = false;
		return S_OK;
	}

	return S_FALSE;
}

