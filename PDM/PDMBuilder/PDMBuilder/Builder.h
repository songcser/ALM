#pragma once

typedef struct DepMessage
{
	string flag;
	string repName;
	string artName;
	string version;
	string path;
	string localPath;
};

bool writeLog(string log,string workspace);

void DeleteFile (string &path);

string ExeDownLoad(char * pServletURL, char *pArgument, char *pDestPath);

string ExeComponentUpLoad(char *pServletURL,string flag,string arg1,string arg2, string arg3, vector<string> pDirectory,vector<string> target);

string ExeUpLoad(string url,string repName,string artName,string number,string buildTime,string duration,string result,string sourcePath,string sourceVersion,string environment,vector<string> source,vector<string> target,list<DepMessage> depMsg);

string ExeUploadMessage(string url,string repName,string artName,string number,string buildTime,string duration,string result,string sourcePath,string sourceVersion,list<DepMessage> depMsg);

bool CurlUploadInit(CURL *&curl,const char* url, string &content, curl_httppost *last);

string addFormFile(curl_httppost **post,curl_httppost **last,vector<string> directory,vector<string> target,string &log);

string addFormField(curl_httppost **post,curl_httppost **last,string name,string value);

long Writer(void *data, int size, int nmemb, string &content);

bool  CurlInit(CURL *&curl, const char* url, string &content, char *pArgument);

bool  GetURLDataByCurl(const char* URL, string &content,char *pArgument);

long WriteHead(void *ptr, size_t size, size_t nmemb, void *stream);

size_t GetContentLengthFunc(void *ptr, size_t size, size_t nmemb, void *stream);

void GetFiles(string path,vector<string> &fils);

string ExeCommand(char *pszCmd,int &exitCode,char *workspace);

//string ExeCmd(char *pszCmd,int &exitCode,char *workspace);

BOOL CreateAllDirectory(char *dir);

string changeSeparator(string path);