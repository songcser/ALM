// Conflict.cpp : Implementation of CConflict

#include "stdafx.h"
#include "Conflict.h"

extern bool IsConflict;

// CConflict

STDMETHODIMP CConflict::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=4; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CConflict::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CConflict::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	if(IsConflict){
		IsConflict = false;
		return S_OK;
	}

	return S_FALSE;
}

