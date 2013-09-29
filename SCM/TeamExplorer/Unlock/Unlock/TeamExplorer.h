#pragma once

#define CONFIG_FILE "TeamExplorer.dat"
#define SERVER_FILE "Server.dat"

#include "tinystr.h"
#include "tinyxml.h"

class CTeamExplorer
{
private:
	string ExeCmd(char *pszCmd);
	BOOL Split(string source, string delimiter, vector<string> *pRetList);

	string UnicodeToANSI(const wstring str);
	wstring UTF8ToUnicode(const string str);
	string UTF8ToANSI(const string str);

	bool GetNodePointers(TiXmlElement* pRootEle, string &strNodeName, vector<TiXmlElement *> *pNodes);
	bool GetNodePointer(TiXmlElement* pRootEle, string &strNodeName, TiXmlElement* &Node);
	bool GetNodesText(string XmlFile, string UrlNode, string OwnerNode, vector<string> *pNodesText);

public:
	CTeamExplorer(void);
	~CTeamExplorer(void);

	BOOL GetConfigPath(char *pConfigPath);
	BOOL GetServerURL(char *pConfigPath, char *pServerURL);
	BOOL GetUserInfo(char *pConfigPath);
	void GetDepInfo(char *pServerURL);

	BOOL GetDirTree(char *pUrl);
	bool GetLockFileList(char *pUrl, vector<string> *pLockFiles);

	BOOL Unlock(vector<string> *pUrls);

	string m_UserName;
	string m_Password;
	string m_DepBuffer;

	vector<string> m_ListRep;
	vector<string> m_ListTrunk;
	vector<string> m_ListBranches;
	vector<string> m_ListSubpro;
};

