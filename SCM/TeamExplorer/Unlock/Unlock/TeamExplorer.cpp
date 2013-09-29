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

string CTeamExplorer::UnicodeToANSI(const wstring str)
{
	int iTextLen = WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL );
	char* pElementText = new char[iTextLen + 1];
	memset(( void* )pElementText, 0, sizeof(char)*(iTextLen + 1));

	::WideCharToMultiByte( CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL );

	string strText = pElementText;
	delete[] pElementText;

	return strText;
}

wstring CTeamExplorer::UTF8ToUnicode(const string str)
{
	int unicodeLen = ::MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, NULL, 0 ); 

	wchar_t* pUnicode = new  wchar_t[unicodeLen+1]; 
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
	::MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen ); 

	wstring  rt = ( wchar_t* )pUnicode;
	delete  pUnicode;

	return  rt;
}

string CTeamExplorer::UTF8ToANSI(const string str)
{
	wstring wrt = UTF8ToUnicode(str);
	string srt = UnicodeToANSI(wrt);

	return srt;
}

bool CTeamExplorer::GetNodePointers(TiXmlElement* pRootEle, string &strNodeName, vector<TiXmlElement *> *pNodes)
{
	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()){
		pNodes->push_back(pEle);
	}

	return false;
}

bool CTeamExplorer::GetNodePointer(TiXmlElement* pRootEle, string &strNodeName, TiXmlElement* &Node)
{
	if (strNodeName==pRootEle->Value()){
		Node = pRootEle;
		return true;
	}

	TiXmlElement *pEle = pRootEle;
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement()){
		if(GetNodePointer(pEle, strNodeName, Node)){
			return true;
		}
	}

	return false;
}

bool CTeamExplorer::GetNodesText(string XmlFile, string UrlNode, string OwnerNode, vector<string> *pNodesText)
{
	TiXmlDocument *pDoc = new TiXmlDocument();
	if(NULL == pDoc){
		return false;
	}

	pDoc->Parse(XmlFile.c_str());
	TiXmlElement *pRootEle = pDoc->RootElement();
	if(NULL == pRootEle){
		return false;
	}

	vector<TiXmlElement *> Nodes;
	string entryNode = "entry";
	GetNodePointers(pRootEle, entryNode, &Nodes);

	TiXmlElement *pUrlNode = NULL;
	TiXmlElement *pOwnerNode = NULL;
	for(int i = 0; i < Nodes.size(); i++){
		if(GetNodePointer(Nodes.at(i), OwnerNode, pOwnerNode)){
			if(GetNodePointer(Nodes.at(i), UrlNode, pUrlNode)){
				string tpUrl = pUrlNode->GetText();
				string tpOwner = pOwnerNode->GetText();

				//tpUrl = UTF8ToANSI(tpUrl);
				//tpOwner = UTF8ToANSI(tpOwner);

				if(!strcmp(tpOwner.c_str(), m_UserName.c_str())){
					pNodesText->push_back(tpUrl);
				}
				else if(!strcmp(m_UserName.c_str(), (string("PL\\"+tpOwner)).c_str())){
					pNodesText->push_back(tpUrl);
				}
				else if(!strcmp(m_UserName.c_str(), (string("pl\\"+tpOwner)).c_str())){
					pNodesText->push_back(tpUrl);
				}
			}
		}
	}

	delete(pDoc);

	return true;
}

BOOL CTeamExplorer::Unlock(vector<string> *pUrls)
{
	if(NULL == pUrls){
		return FALSE;
	}

	string unlockCmd = "svn unlock --non-interactive";
	for(int i = 0; i < pUrls->size(); i++){
		unlockCmd += " \"" + pUrls->at(i) + "\"";
	}

	ExeCmd((char *)unlockCmd.c_str());
	
	return TRUE;
}

bool CTeamExplorer::GetLockFileList(char *pUrl, vector<string> *pLockFiles)
{
	string infoCmd = "svn info --non-interactive --xml -R \"";
	infoCmd += pUrl;
	infoCmd += "\"";

	string infoStr = ExeCmd((char *)infoCmd.c_str());

	GetNodesText(infoStr, "url", "owner", pLockFiles);

	return true;
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
