#include "stdafx.h"
#include "Builder.h"

#pragma comment(lib, "libcurl.lib")

// This is an example of an exported variable

// This is an example of an exported function.

// This is the constructor of a class that has been exported.
// see BuildTest.h for the class definition

// DownLoadFile.cpp : Defines the entry point for the console application.
//
string ExeUpLoad(char *pServletURL,string flag,string arg1,string arg2, string arg3, vector<string> directory,vector<string> target)
{
	CURL *curl = NULL;
	CURLcode code;
	CURLFORMcode fromCode;
	string content;
	string log;
	curl_httppost*post = NULL;
	curl_httppost *last =NULL;

	CurlUploadInit(curl,pServletURL, content,post );
	/*
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "flag",CURLFORM_COPYCONTENTS,flag,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg1",CURLFORM_COPYCONTENTS,arg1,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg2",CURLFORM_COPYCONTENTS,arg2,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg3",CURLFORM_COPYCONTENTS,arg3,CURLFORM_END);
	*/
	addFormField(post,last,"flag",flag);
	addFormField(post,last,"arg1",arg1);
	addFormField(post,last,"arg2",arg2);
	addFormField(post,last,"arg3",arg3);
	
	addFormFile(post,last,directory,target);
	
	
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "field",CURLFORM_COPYCONTENTS,"test uplaod",CURLFORM_END);
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "file",CURLFORM_FILE, "ReadMe.txt", CURLFORM_END); 
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "file",CURLFORM_FILE, "log", CURLFORM_END); 


	
	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}

	printf("%s\n",content);
	curl_formfree(post);
	curl_easy_cleanup(curl);
	
	
	curl_global_cleanup(); 

	return content.append(log);
}


string ExeUpLoad(string pServletURL,string repName,string artName,string number,string buildTime,string duration,string result,string sourcePath,string sourceVersion,vector<string> source,vector<string> target,list<DepMessage> depMsgList)
{
	CURL *curl = NULL;
	CURLcode code;
	CURLFORMcode fromCode;
	string content;
	string log;
	curl_httppost*post = NULL;
	curl_httppost *last =NULL;



	CurlUploadInit(curl,pServletURL.c_str(), content,post );

	addFormField(post,last,"RepositoryName",repName);
	addFormField(post,last,"ArtifactName",artName);
	addFormField(post,last,"Number",number);
	addFormField(post,last,"BuildTime",buildTime);
	addFormField(post,last,"Duration",duration);
	addFormField(post,last,"Result",result);
	addFormField(post,last,"SourcePath",sourcePath);
	addFormField(post,last,"SourceVersion",sourceVersion);
	int size = depMsgList.size();
	stringstream newstr;
	newstr<<size;
	string sizestr;
	newstr>>sizestr;
	addFormField(post,last,"DepCount",sizestr);
	int index = 0;
	for (list<DepMessage>::iterator depIter=depMsgList.begin();depIter != depMsgList.end();++depIter)
	{
		//DepMessage depMsg = *depIter;
		char temp[30];
		sprintf(temp,"%s%d","DepFlag_",index);
		addFormField(post,last,temp,depIter->flag);
		sprintf(temp,"%s%d","DepRepository_",index);
		addFormField(post,last,temp,depIter->repName);
		sprintf(temp,"%s%d","DepName_",index);
		addFormField(post,last,temp,depIter->artName);
		sprintf(temp,"%s%d","DepVersion_",index);
		addFormField(post,last,temp,depIter->version);
		sprintf(temp,"%s%d","DepPath_",index);
		addFormField(post,last,temp,depIter->path);
		sprintf(temp,"%s%d","DepLoaction_",index);
		addFormField(post,last,temp,depIter->localPath);

		index ++;
	}

	addFormFile(post,last,source,target);

	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}

	printf("%s\n",content);
	curl_formfree(post);
	curl_easy_cleanup(curl);


	curl_global_cleanup(); 

	return content.append(log);

}


bool CurlUploadInit(CURL *&curl,const char* url, string &content,curl_httppost*post )
{
	CURLcode code;
	string error;
	int timeout = 15;

	code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if(code != CURLE_OK){
		return false;
	} 
	//string content;
	string log = "\n";
	//CurlInit(curl, pServletURL ,content) ;
	curl = curl_easy_init();
	if (curl == NULL)
	{
		printf( "Failed to create CURL connection\n");
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);
	if (code != CURLE_OK)
	{
		printf( "Failed to set error buffer [%d]\n", code );
		return false;
	}
	code = curl_easy_setopt(curl, CURLOPT_HTTPPOST,post); 
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_URL,url);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl,CURLOPT_HEADER,0);
	if (code != CURLE_OK)
	{
		return false;
	}

	code = curl_easy_setopt(curl,CURLOPT_TIMEOUT,timeout);
	/*
	code = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "field=test");
	if (code != CURLE_OK)
	{
		printf("Failed to set Post [%s]\n", error);
		return false;
	}
	*/

	code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	if (code != CURLE_OK)
	{
		printf( "Failed to set write data [%s]\n", error );
		return false;
	}
}

void GetFiles(string path,vector<string> &files)
{
    long   hFile   =   0;  
	struct _finddata_t fileinfo;
  
    string p;  
  
    if((hFile= _findfirst(p.assign(path).append("/*").c_str(),&fileinfo))   !=   -1)  
	{    
        do {
            if((fileinfo.attrib&_A_SUBDIR)) {    
                if   (strcmp(fileinfo.name,".")   !=   0   &&   strcmp(fileinfo.name,"..")   !=   0)    
                    GetFiles(   p.assign(path).append("/").append(fileinfo.name), files);    
            }  else  {    
                files.push_back(   p.assign(path).append("/").append(fileinfo.name)  );  
            }    
        }   while   (_findnext(   hFile,   &fileinfo   )   ==   0);    
  
        _findclose(hFile);    
    }  
}

string addFormFile(curl_httppost *post,curl_httppost *last,vector<string> directory,vector<string> target)
{
	string log;
	vector<string>::iterator targetIter=target.begin();
	for (vector<string>::iterator iter=directory.begin();iter != directory.end();++iter)
	{

		vector<string> files;
		GetFiles(*iter,files);

		for (vector<string>::iterator fileiter=files.begin();fileiter != files.end();++fileiter)
		{
			int index = fileiter->find_last_of("\\");
			string filename = fileiter->substr(index);
			string filepath = *targetIter+"\\"+filename;
			curl_formadd(&post,&last, CURLFORM_COPYNAME, "file",CURLFORM_FILE,fileiter->c_str(),CURLFORM_FILENAME,filepath.c_str(),CURLFORM_END);

			log.append("Upload File: ").append(fileiter->c_str()).append("  To  ").append(filepath.c_str()).append("\n");

		}

		targetIter++;
	}

	return log;
}

string addFormField(curl_httppost *post,curl_httppost *last,string name,string value)
{
	curl_formadd(&post,&last, CURLFORM_COPYNAME, name,CURLFORM_COPYCONTENTS,value,CURLFORM_END);
	string str("Add: ");
	return str.append("Name->").append(name).append("  Value->").append(value);
}

string ExeDownLoad(char * pServletURL, char *pArgument, char *pDestPath)
{
	string stZipFile = pDestPath;
	stZipFile += "\\test1.zip";
	string content;
	string log = "\n";

	FILE *fp = fopen(stZipFile.c_str(), "ab+");
	if(NULL == fp){
		return FALSE;
	}

	if(!GetURLDataByCurl(pServletURL, content, fp, pArgument)){
		return FALSE;
	}

	fflush(fp);
	fclose(fp);


	HZIP hz = OpenZip(stZipFile.c_str(), 0);
	if(!IsZipHandleU(hz)){
		CloseZip(hz);
		remove(stZipFile.c_str());
		return FALSE;
	}

	ZIPENTRY ze;
	ZRESULT zResult = GetZipItem(hz, -1, &ze);
	if(zResult != ZR_OK){
		CloseZip(hz);
		remove(stZipFile.c_str());
		return FALSE;
	}


	int numItems = ze.index;
	zResult = SetUnzipBaseDir(hz, ".");
	if (zResult != ZR_OK){
		CloseZip(hz);
		remove(stZipFile.c_str());
		return FALSE;
	}

	for(int i=0; i<numItems; i++){ 
		GetZipItem(hz, i, &ze);
		zResult = UnzipItem(hz, i, ze.name);
		if (zResult != ZR_OK){
			CloseZip(hz);
			remove(stZipFile.c_str());
			return FALSE;
		}

		log.append("Get File: ").append(ze.name).append("\n");
	}

	CloseZip(hz);
	remove(stZipFile.c_str());

	return content.append(log);
}

bool CurlInit(CURL *&curl, const char* url, string &content, FILE *fp, char *pArgument)
{
	CURLcode code;
	string error;
	curl = curl_easy_init();
	if(curl == NULL){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);
	if(code != CURLE_OK){
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	code = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pArgument);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_URL, url);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, GetContentLengthFunc);
	if(code != CURLE_OK){
		return false;
	}

	long filesize=0;
	code = curl_easy_setopt(curl, CURLOPT_HEADERDATA, &filesize);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
	if(code != CURLE_OK){
		return false;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	if(code != CURLE_OK){
		return false;
	}

	return true;
}

long WriteHead(void *ptr, size_t size, size_t nmemb, void *stream)
{
	string head = (char*)ptr;
	int index = head.find("JSESSIONID", 0);
	if(index > 0){
		string session = head.substr(index+11, 32);
	}

	return size * nmemb;
}

size_t GetContentLengthFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	long len = 0;
	char * str = (char *)ptr;
	if(sscanf(str, "Content-Length: %ld\n", &len)){
		*((long *) stream) = len;
	}

	return size * nmemb;
}

long Writer(void *data, int size, int nmemb, string &content, FILE *fp)
{
	int written = fwrite(data, size, nmemb, fp);
	return written;
}

bool GetURLDataByCurl(const char* URL,  string &content, FILE *fp, char *pArgument)
{
	CURL *curl = NULL;
	CURLcode code;
	string error;

	code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if(code != CURLE_OK){
		return false;
	} 

	if(!CurlInit(curl,URL, content, fp, pArgument)){
		return false;
	}

	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}

	curl_easy_cleanup(curl);

	return true;
}

bool ExeCommand(char *cmd)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi,sizeof(pi));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	BOOL bResult = CreateProcess(NULL,cmd,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
	if(bResult)
	{
		WaitForSingleObject( pi.hProcess, INFINITE );

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}else{
		return false;
	}

	return true;
}
