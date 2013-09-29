#include "StdAfx.h"
#include "TeamExplorer.h"

CTeamExplorer::CTeamExplorer(void)
{
	m_DepBuffer = "";
	m_UserName = "";
	m_Password = "";
}

CTeamExplorer::~CTeamExplorer(void)
{
}

BOOL CTeamExplorer::Split(string source, string delimiter, vector<string> *pRetList)
{
	if(NULL == pRetList){
		return FALSE;
	}

	while(1){
		int index = source.find(delimiter);
		if(index > 0){
			string tpStr = source.substr(0, index);
			pRetList->push_back(tpStr);

			if(index+2 < source.length()){
				source = source.substr(index+2, source.length());
			}
			else{
				break;
			}
		}
		else if(0 == index){
			if(index+2 < source.length()){
				source = source.substr(index+2, source.length());
			}
			else{
				break;
			}
		}
		else if(index < 0){
			break;
		}
	}

	return TRUE;
}

string CTeamExplorer::ExeCmd(char *pszCmd)
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

BOOL CTeamExplorer::GetDirTree(char *pUrl)
{
	if(NULL == pUrl){
		return FALSE;
	}

	m_ListRep.clear();
	m_ListTrunk.clear();
	m_ListBranches.clear();
	m_ListSubpro.clear();

	string basePath = pUrl;
	string listCmd = "svn list --non-interactive \"";

	string destPath = basePath;
	string listFullCmd = listCmd + destPath + "\"";
	string retMsg = ExeCmd((char *)listFullCmd.c_str());
	if(0 == retMsg.find("svn: ")){
		return FALSE;
	}
	else{
		Split(retMsg, "\r\n", &m_ListRep);
	}

	destPath = basePath + "/trunk";
	listFullCmd = listCmd + destPath + "\"";
	retMsg = ExeCmd((char *)listFullCmd.c_str());
	if(0 != retMsg.find("svn: ")){
		Split(retMsg, "\r\n", &m_ListTrunk);
	}

	destPath = basePath + "/branches";
	listFullCmd = listCmd + destPath + "\"";
	retMsg = ExeCmd((char *)listFullCmd.c_str());
	if(0 != retMsg.find("svn: ")){
		Split(retMsg, "\r\n", &m_ListBranches);
	}

	for(int i = 0; i < m_ListBranches.size(); i++){
		destPath = basePath + "/branches/" + m_ListBranches.at(i);
		listFullCmd = listCmd + destPath + "\"";
		retMsg = ExeCmd((char *)listFullCmd.c_str());
		if(0 != retMsg.find("svn: ")){
			Split(retMsg, "\r\n", &m_ListSubpro);
		}
		m_ListSubpro.push_back("|");
	}

	return TRUE;
}

BOOL CTeamExplorer::GetConfigPath(char *pConfigPath)
{
	if(NULL == pConfigPath){
		return FALSE;
	}

	string sConfigPath = "C:";
	sConfigPath += getenv("homepath");
	sConfigPath += "\\Application Data\\Subversion";

	memcpy(pConfigPath, sConfigPath.c_str(), sConfigPath.length());

	return TRUE;
}

BOOL CTeamExplorer::GetServerURL(char *pConfigPath, char *pServerURL)
{
	if(NULL == pConfigPath || NULL == pServerURL){
		return FALSE;
	}

	string sServerFile = pConfigPath;
	sServerFile += "\\auth\\svn.simple\\";
	sServerFile += SERVER_FILE;

	if(PathFileExists(sServerFile.c_str())){
		FILE *fp = fopen(sServerFile.c_str(), "rb+");
		if(NULL == fp){
			return FALSE;
		}

		fread(pServerURL, 1, 255, fp);
		fclose(fp);
	}
	else{
		return FALSE;
	}

	return TRUE;
}

BOOL CTeamExplorer::GetUserInfo(char *pConfigPath)
{
	if(NULL == pConfigPath){
		return FALSE;
	}

	string configPath = pConfigPath;
	configPath += "\\auth\\svn.simple\\";
	configPath += CONFIG_FILE;

	FILE *fp = fopen(configPath.c_str(), "rb+");
	if(NULL == fp){
		return FALSE;
	}

	char tUserName[255];
	char tPassword[255];

	memset(tUserName, 0, sizeof(tUserName));
	memset(tPassword, 0, sizeof(tPassword));

	fseek(fp, 255, SEEK_SET);
	fread(tUserName, 1, sizeof(tUserName), fp);
	fread(tPassword, 1, sizeof(tPassword), fp);

	fclose(fp);

	string tsUserName(tUserName);
	string tsPassword(tPassword);

	m_UserName = tsUserName;
	m_Password = tsPassword;

	return TRUE;
}

void CTeamExplorer::GetDepInfo(char *pServerURL)
{
	if(NULL == pServerURL){
		m_DepBuffer = "";
		return;
	}

	CString strFileURLInServer(pServerURL);

	ASSERT(strFileURLInServer != "");

	string strBuffer;

	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;

	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,nTimeOut);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES,1);
	char *pszBuffer = NULL;

	try{
		InternetSetOption(session,INTERNET_OPTION_RESET_URLCACHE_SESSION,NULL,0);
		AfxParseURL(strFileURLInServer,dwType,strServer,strObject,wPort);
		pHttpConnection = session.GetHttpConnection(strServer,wPort, m_UserName.c_str(), m_Password.c_str());
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject);
		if (pHttpFile->SendRequest() == FALSE){
			m_DepBuffer = "";
			return;
		}

		DWORD dwStateCode;

		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK){
			char szInfoBuffer[1000];
			DWORD dwFileSize = 0;
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,(void *)szInfoBuffer,&dwInfoBufferSize,NULL);

			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024;
			pszBuffer = new char[BUFFER_LENGTH];
			DWORD dwWrite, dwTotalWrite = 0;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer,BUFFER_LENGTH);
			while(nRead>0){
				dwTotalWrite += nRead;
				strBuffer += pszBuffer;
				nRead = pHttpFile->Read(pszBuffer,BUFFER_LENGTH);
			}
			int length = strBuffer.length();
			strBuffer.erase(dwTotalWrite,length-dwTotalWrite);
			delete[] pszBuffer;
			pszBuffer = NULL;
		}
		else{
			delete[] pszBuffer;
			pszBuffer = NULL;
			if (pHttpFile != NULL){
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if (pHttpConnection != NULL){
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			m_DepBuffer = "";
			return ;
		}
	}
	catch (...){
		delete[]pszBuffer;
		pszBuffer = NULL;
		if(pHttpFile != NULL){
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if(pHttpConnection != NULL){
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		m_DepBuffer = "";
		return;
	}

	if (pHttpFile != NULL){
		pHttpFile->Close();
		delete pHttpFile;
		pHttpFile = NULL;
	}

	if (pHttpConnection != NULL){
		pHttpConnection->Close();
		delete pHttpConnection;
		pHttpConnection = NULL;
	}

	session.Close();

	m_DepBuffer = strBuffer;
}

string CTeamExplorer::Export(string sSourceUrl, string sDestPath)
{
	string ExportCmd = "svn export --non-interactive \"" + sSourceUrl + "\" \"" + sDestPath + "\"";
	string strRet = ExeCmd((char *)ExportCmd.c_str());

	return strRet;
}