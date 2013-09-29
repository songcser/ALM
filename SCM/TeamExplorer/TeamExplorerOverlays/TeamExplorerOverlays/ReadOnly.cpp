// ReadOnly.cpp : Implementation of CReadOnly

#include "stdafx.h"
#include "ReadOnly.h"
#include "Public.h"
#include "TeamExplorerCore.h"
#pragma comment(lib, "TeamExplorerCore.lib")

// CReadOnly
STDMETHODIMP CReadOnly::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
	GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
	*pIndex=0; 
	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;

	return S_OK;
}

STDMETHODIMP CReadOnly::GetPriority(int* pPriority)
{
	*pPriority=0;

	return S_OK;
}

STDMETHODIMP CReadOnly::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
	wchar_t *s = _wcsdup(pwszPath);

	char cCrtPath[1024];
	memset(cCrtPath, 0, sizeof(cCrtPath));
	w2c(cCrtPath, s, 2*wcslen(pwszPath)+1);

	string sCrtPath(cCrtPath), sSvnPath, sFathPath, sPath;
	sPath = sCrtPath;

	sSvnPath = sCrtPath + "\\.svn";
	if(PathFileExists(sSvnPath.c_str())){
		int iStatus = -1;

		if(!IsRealWorkCopy(sCrtPath)){
			return S_FALSE;
		}

		if(IsTeamExplorer(sCrtPath)){
			iStatus = GetPathStatus(sPath, 1);

			if(-1 == iStatus){
				return S_FALSE;
			}

			SetPathStatus(iStatus);
		}
		else{
			iStatus = GetPathStatusForNb(sPath, 1);

			if(-1 == iStatus){
				return S_FALSE;
			}

			SetPathStatusForNb(iStatus);
		}
	}
	else{
		if(sPath.npos != sPath.find(".svn")){
			return S_FALSE;
		}
		else{
			int iStatus = -1;
			while(GetFatherPath(sCrtPath, sFathPath)){
				sSvnPath = sFathPath + "\\.svn";
				if(PathFileExists(sSvnPath.c_str())){
					if(!IsRealWorkCopy(sFathPath)){
						return S_FALSE;
					}

					if(IsTeamExplorer(sFathPath)){
						if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(sPath.c_str())){
							iStatus = GetPathStatus(sPath, 0);
						}
						else{
							iStatus = GetPathStatus(sPath, 1);
						}

						if(-1 == iStatus){
							return S_FALSE;
						}

						SetPathStatus(iStatus);
					}
					else{
						if(FILE_ATTRIBUTE_DIRECTORY != GetFileAttributes(sPath.c_str())){
							iStatus = GetPathStatusForNb(sPath, 0);
						}
						else{
							iStatus = GetPathStatusForNb(sPath, 1);
						}

						if(-1 == iStatus){
							return S_FALSE;
						}

						SetPathStatusForNb(iStatus);
					}
					break;
				}
				sCrtPath = sFathPath;
				sFathPath = "";
			}
		}
	}

	free(s);

	if(IsReadOnly){
		IsReadOnly = false;
		return S_OK;
	}

	return S_FALSE;
}

bool CReadOnly::w2c(char *pcstr,const wchar_t *pwstr, size_t len)
{
	int nlength=wcslen(pwstr);

	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL);    

	if(nbytes>len){
		nbytes=len;
	}

	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);

	return true;
}

bool CReadOnly::GetFatherPath(string sCrtPath, string &sFatherPath)
{
	int pos = sCrtPath.rfind('\\');
	if(pos == string::npos){
		return false;
	}

	sFatherPath = sCrtPath.substr(0, pos);

	return true;
}

void CReadOnly::SetPathStatusForNb(int iStatus)
{
	if(0 == iStatus){
		IsReadWrite = true;
	}
	else if(3 == iStatus){
		IsModify = true;
	}
	else if(5 == iStatus){
		IsAdd = true;
	}
}

void CReadOnly::SetPathStatus(int iStatus)
{
	if(0 == iStatus){
		IsReadOnly = true;
	}
	else if(1 == iStatus){
		IsAdd = true;
	}
	else if(2 == iStatus){
		IsReadWrite = true;
	}
	else if(3 == iStatus){
		IsModify = true;
	}
	else if(4 == iStatus){
		IsConflict = true;
	}
	else if(5 == iStatus){
		IsUnversion = true;
	}
}
