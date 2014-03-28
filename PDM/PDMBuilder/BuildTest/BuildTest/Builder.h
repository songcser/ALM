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

string ExeDownLoad(char * pServletURL, char *pArgument, char *pDestPath);

string ExeUpLoad(char *pServletURL,string flag,string arg1,string arg2, string arg3, vector<string> pDirectory,vector<string> target);

string ExeUpLoad(string url,string repName,string artName,string number,string buildTime,string duration,string result,string sourcePath,string sourceVersion,vector<string> source,vector<string> target,list<DepMessage> depMsg);

bool CurlUploadInit(CURL *&curl,const char* url, string &content, curl_httppost *last);
string addFormFile(curl_httppost *post,curl_httppost *last,vector<string> directory,vector<string> target);

string addFormField(curl_httppost *post,curl_httppost *last,string name,string value);

long Writer(void *data, int size, int nmemb, string &content, FILE *fp);
bool  CurlInit(CURL *&curl, const char* url, string &content, FILE *fp, char *pArgument);
bool  GetURLDataByCurl(const char* URL, string &content, FILE *fp, char *pArgument);
long WriteHead(void *ptr, size_t size, size_t nmemb, void *stream);
size_t GetContentLengthFunc(void *ptr, size_t size, size_t nmemb, void *stream);
void GetFiles(string path,vector<string> &fils);
bool ExeCommand(char *cmd);
