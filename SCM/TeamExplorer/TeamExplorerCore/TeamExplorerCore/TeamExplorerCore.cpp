// TeamExplorerCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TeamExplorerCore.h"

string CutStr(int from, int to, string srcStr)
{
	string strRet = "";

	if(from < 0 || to > srcStr.length() || to - from >= 1024){
		return strRet;
	}

	char cRet[1024];
	memset(cRet, 0, sizeof(cRet));

	int j = 0;
	for(int i = from; i < to; i++){
		cRet[j] = srcStr[i];
		j++;
	}

	strRet += cRet;

	return strRet;
}

string ExeCmd(char *pszCmd)
{
	if(NULL == pszCmd){
		return "";
	}

	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)){
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &sii, &pii)){
		return "";
	}

	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL)){
		strRet.append(buff, dwRead);
	}

	CloseHandle(hRead);
	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);

	return strRet;
}

bool GetFatherPath(string sCrtPath, string &sFatherPath)
{
	int pos = sCrtPath.rfind('\\');
	if(pos == string::npos){
		return false;
	}

	sFatherPath = sCrtPath.substr(0, pos);

	return true;
}

bool HasConflict(string strRet)
{
	int index = -1;
	while(1){
		index = strRet.find("\r\n");
		if(index <= 0){
			break;
		}

		string tpStr = strRet.substr(0, index);
		
		int tIndex2 = tpStr.find("C");
		int tIndex1 = tpStr.find("K  ");
		if(tIndex2 < 8 && tIndex2 >= 0 && tIndex1 < 8 && tIndex1 >= 0){
			return true;
		}

		if(index+2 >= strRet.length()){
			break;
		}

		strRet = strRet.substr(index+2, strRet.length());
	}

	return false;
}

bool HasModify(string strRet)
{
	int index = -1;
	while(1){
		index = strRet.find("\r\n");
		if(index <= 0){
			break;
		}

		string tpStr = strRet.substr(0, index);

		int tIndex = tpStr.find("M");
		int tIndex1 = tpStr.find("K  ");
		if(tIndex < 8 && tIndex >= 0 && tIndex1 < 8 && tIndex1 >= 0){
			return true;
		}

		if(index+2 >= strRet.length()){
			break;
		}

		strRet = strRet.substr(index+2, strRet.length());
	}

	return false;
}

TEAMEXPLORERCORE_API BOOL IsWorkCopy(vector<string> *sFiles, int iNumFiles, string &sWcPath)
{
	string sFathPath, sSvnPath, sCrtPath, sFile;

	for(int i = 0; i < iNumFiles; i++){
		sFile = sFiles->at(i);
		sCrtPath = sFile;
		while(1){
			sSvnPath = sCrtPath + "\\.svn";
			if(PathFileExists(sSvnPath.c_str())){
				sWcPath = sCrtPath;
				break;
			}
			else{
				if(!GetFatherPath(sCrtPath, sFathPath)){
					return FALSE;
				}
			}
			sCrtPath = sFathPath;
			sFathPath = "";
		}
	}

	if(iNumFiles >= 2){
		sSvnPath = sFiles->at(0) + "\\.svn";
		if(PathFileExists(sSvnPath.c_str())){
			return FALSE;
		}
	}

	string strRet;
	string SvnCmd = "svn status --non-interactive \"";
	SvnCmd += sWcPath;
	SvnCmd += "\"";
	strRet = ExeCmd((char *)SvnCmd.c_str());

	if(strRet.find("W155007:") != strRet.npos){
		return FALSE;
	}

	return TRUE;
}

TEAMEXPLORERCORE_API BOOL CouldWrite(vector<string> *sFiles, vector<string> *sWriteFiles, int iNumFiles)
{
	string sStatusCmd, sFile, strRet;
	BOOL WriteFlag = FALSE;

	for(int i = 0; i < iNumFiles; i++){
		sFile = sFiles->at(i);
		sStatusCmd = "svn status --non-interactive \"";
		sStatusCmd += sFile;
		sStatusCmd += "\"";
		strRet = ExeCmd((char*)sStatusCmd.c_str());
		if(strRet.npos != strRet.find("K  ") || strRet.npos != strRet.find("A       ") || strRet.npos != strRet.find("A  +    ")){
			WriteFlag = TRUE;
			sWriteFiles->push_back(sFile);
		}
	}

	if(WriteFlag){
		return TRUE;
	}

	return FALSE;
}

TEAMEXPLORERCORE_API BOOL IsProductOrTags(string sWcPath)
{
	string sFlagFile = sWcPath;
	sFlagFile += "\\.svn\\";
	sFlagFile += FLAG_FILE_NAME;

	if(PathFileExists(sFlagFile.c_str())){
		return FALSE;
	}

	return TRUE;
}

TEAMEXPLORERCORE_API BOOL IsTeamExplorer(string sWcPath)
{
	string filePath = sWcPath + "\\.svn\\nb.dat";
	if(PathFileExists((char *)filePath.c_str())){
		return FALSE;
	}

	return TRUE;
}

TEAMEXPLORERCORE_API BOOL IsRealWorkCopy(string sWcPath)
{
	string strRet;
	string SvnCmd = "svn status --non-interactive \"";
	SvnCmd += sWcPath;
	SvnCmd += "\"";
	strRet = ExeCmd((char *)SvnCmd.c_str());

	if(strRet.find("W155007:") != strRet.npos){
		return FALSE;
	}

	return TRUE;
}

TEAMEXPLORERCORE_API int GetPathStatus(string sPath, int iPathType)
{
	string strRet;
	string SvnCmd = "svn status --non-interactive \"";
	SvnCmd += sPath;
	SvnCmd += "\"";
	strRet = ExeCmd((char *)SvnCmd.c_str());

	if(strRet.find("E020024:") != strRet.npos){
		return -1;
	}

	int pos = 0;

	if(0 == iPathType){
		if(2 >= strRet.length()){
			return 0;
		}
		else if(strRet.npos != strRet.find("     K  ")){
			return 2;
		}
		else if(HasConflict(strRet)){
			return 4;
		}
		else if(HasModify(strRet)){
			return 3;
		}
		else if(strRet.npos != strRet.find("?       ")){
			return 5;
		}
		else if(strRet.npos != strRet.find("A       ") || strRet.npos != strRet.find("A  +    ")){
			return 1;
		}
		else if(strRet.npos != (pos = strRet.find("svn: "))){
			if(0 == pos){
				return 5;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else if(1 == iPathType){
		if(2 >= strRet.length()){
			return 0;
		}
		else if(HasConflict(strRet)){
			return 4;
		}
		else if(HasModify(strRet)){
			return 3;
		}
		else if(strRet.npos != strRet.find("     K  ")){
			return 2;
		}
		else if(strRet.npos != (pos = strRet.find("A       ")) || strRet.npos != (pos = strRet.find("A  +    "))){
			if(0 == pos){
				int tmpPos = strRet.find("\r");
				string subStr = CutStr(8, tmpPos, strRet);
				if(sPath == subStr){
					return 1;
				}
				else{
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		else if(strRet.npos != (pos = strRet.find("?       "))){
			if(0 == pos){
				int tmpPos = strRet.find("\r");
				string subStr = CutStr(8, tmpPos, strRet);
				if(sPath == subStr){
					return 5;
				}
				else{
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		else if(strRet.npos != (pos = strRet.find("svn: "))){
			if(0 == pos){
				return 5;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		return -1;
	}

	return -1;
}

TEAMEXPLORERCORE_API int GetPathStatusForNb(string sPath, int iPathType)
{
	string strRet;
	string SvnCmd = "svn status --non-interactive \"";
	SvnCmd += sPath;
	SvnCmd += "\"";
	strRet = ExeCmd((char *)SvnCmd.c_str());

	if(strRet.find("E020024:") != strRet.npos){
		return -1;
	}

	int pos = 0;

	if(0 == iPathType){
		if(2 >= strRet.length()){
			return 0;
		}
		else if(strRet.npos != strRet.find("M       ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("?       ")){
			return 5;
		}
		else if(strRet.npos != strRet.find("A       ") || strRet.npos != strRet.find("A  +    ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("CM      ") || strRet.npos != strRet.find("C       ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("M    K  ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("CM   K  ") || strRet.npos != strRet.find("C    K  ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("D       ")){
			return 3;
		}
		else if(strRet.npos != (pos = strRet.find("svn: "))){
			if(0 == pos){
				return 5;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else if(1 == iPathType){
		if(2 >= strRet.length()){
			return 0;
		}
		else if(strRet.npos != strRet.find("M       ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("A       ") || strRet.npos != strRet.find("A  +    ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("CM      ") || strRet.npos != strRet.find("C       ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("M    K  ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("CM   K  ") || strRet.npos != strRet.find("C    K  ")){
			return 3;
		}
		else if(strRet.npos != strRet.find("D       ")){
			return 3;
		}
		else if(strRet.npos != (pos = strRet.find("?       "))){
			if(0 == pos){
				int tmpPos = strRet.find("\r");
				string subStr = CutStr(8, tmpPos, strRet);
				if(sPath == subStr){
					return 5;
				}
				else{
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		else if(strRet.npos != (pos = strRet.find("svn: "))){
			if(0 == pos){
				return 5;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		return -1;
	}

	return -1;
}