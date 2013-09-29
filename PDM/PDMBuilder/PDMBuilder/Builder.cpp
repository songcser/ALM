#include "stdafx.h"
#include "Builder.h"
#include <Shlwapi.h>

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "Shlwapi.lib")
// This is an example of an exported variable

// This is an example of an exported function.

// This is the constructor of a class that has been exported.
// see BuildTest.h for the class definition

// DownLoadFile.cpp : Defines the entry point for the console application.
//

 FILE *fp;

 //int exitError=0;
 //int exitSuccess = 0;

 bool writeLog(string log,string filePath)
 {
	 FILE *fp;
	 //string filePath = workspace+"\\log";
	 if (fp=fopen(filePath.c_str(),"a+"))
	 {
		 if(EOF==fprintf(fp,"%s",log.c_str()))
		 {
			 fclose(fp);
			 return false;
		 }
		 fclose(fp);
	 }

	 return true;
 }

BOOL CreateAllDirectory(char *dir)
{
	int len = strlen(dir);

	if(dir[len]!='\\')
	{
		dir[len] = '\\';
		dir[len+1] = '\0';
	}

	for (int i=0;i<=len;i++)
	{
		if (dir[i]=='\\')
		{
			dir[i] = '\0';
			if (!PathFileExists(dir))
			{
				if (mkdir(dir))
				{
					return FALSE;
				}
				
			}
			dir[i] = '\\';
		}
	}
	return TRUE;
}
/*
string ExeCmd(char *pszCmd,int &exitCode,char *workspace)
{
	if(NULL == pszCmd){
		return "";
	}

	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, workspace, &sii, &pii))
	{
		int error = GetLastError();
		return "";
	}

	//DWORD rc = WaitForSingleObject(pii.hProcess,6000);
	DWORD rc = MsgWaitForMultipleObjects(1,&pii.hThread,FALSE,100,QS_ALLINPUT);

	if (rc==WAIT_TIMEOUT)
	{
		//printf("%s","timeout");
	}else if (WAIT_FAILED ==rc)
	{
		//printf("%s","failed");
	}


	DWORD code = STILL_ACTIVE;
	//while(code == STILL_ACTIVE)
	//	{
	GetExitCodeProcess(pii.hProcess,&code);
	//	}


	exitCode = code;



	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
	{
		strRet.append(buff, dwRead);
	}
	CloseHandle(hRead);

	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);
	//	CloseHandle(sii.hStdError);
	//	CloseHandle(sii.hStdInput);
	//	CloseHandle(sii.hStdOutput);

	//	printf("%s",strRet.c_str());
	return strRet;
}
*/
string ExeCommand(char *pszCmd,int &exitCode,char *workspace)
{
	if(NULL == pszCmd){
		return "";
	}

	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "";
	}

	STARTUPINFO sii = {sizeof(STARTUPINFO)};
	GetStartupInfo(&sii);
	sii.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sii.wShowWindow = SW_HIDE;
	sii.hStdError = hWrite;
	sii.hStdOutput = hWrite;

	PROCESS_INFORMATION pii;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, workspace, &sii, &pii))
	{
		int error = GetLastError();
		return "";
	}

	//DWORD rc = WaitForSingleObject(pii.hProcess,6000);
	DWORD rc = MsgWaitForMultipleObjects(1,&pii.hThread,FALSE,100,QS_ALLINPUT);

	if (rc==WAIT_TIMEOUT)
	{
		//printf("%s","timeout");
	}else if (WAIT_FAILED ==rc)
	{
		//printf("%s","failed");
	}
	 

	DWORD code = STILL_ACTIVE;
	//while(code == STILL_ACTIVE)
//	{
		GetExitCodeProcess(pii.hProcess,&code);
//	}
	
	
	exitCode = code;

	

	CloseHandle(hWrite);

	string strRet;
	char buff[1024] = {0};
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
	{
		strRet.append(buff, dwRead);
	}
	CloseHandle(hRead);

	CloseHandle(pii.hProcess);
	CloseHandle(pii.hThread);
//	CloseHandle(sii.hStdError);
//	CloseHandle(sii.hStdInput);
//	CloseHandle(sii.hStdOutput);

//	printf("%s",strRet.c_str());
	return strRet;
}

string ExeComponentUpLoad(char *pServletURL,string flag,string arg1,string arg2, string arg3, vector<string> directory,vector<string> target)
{
	CURL *curl = NULL;
	CURLcode code;
//	CURLFORMcode fromCode;
	string content;
	string log("\n<--------------------------------Upload Component Library---------------------------->\n");
	curl_httppost *post = NULL;
	curl_httppost *last =NULL;

	
	/*
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "flag",CURLFORM_COPYCONTENTS,flag,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg1",CURLFORM_COPYCONTENTS,arg1,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg2",CURLFORM_COPYCONTENTS,arg2,CURLFORM_END);
	curl_formadd(&post,&last, CURLFORM_COPYNAME, "arg3",CURLFORM_COPYCONTENTS,arg3,CURLFORM_END);
	*/

	log += addFormField(&post,&last,"flag",flag);
	log += addFormField(&post,&last,"arg1",arg1);
	log += addFormField(&post,&last,"arg2",arg2);
	log += addFormField(&post,&last,"arg3",arg3);
	
	log += addFormFile(&post,&last,directory,target,log);
	
	
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "field",CURLFORM_COPYCONTENTS,"test uplaod",CURLFORM_END);
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "file",CURLFORM_FILE, "ReadMe.txt", CURLFORM_END); 
	//fromCode = curl_formadd(&post,&last, CURLFORM_COPYNAME, "file",CURLFORM_FILE, "log", CURLFORM_END); 

	CurlUploadInit(curl,pServletURL, content,post );
	
	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}

	//printf("%s\n",content);
	curl_formfree(post);
	curl_easy_cleanup(curl);
	
	
	curl_global_cleanup(); 

	//return content.append(log);
	return log;
}

string ExeUpLoad(string pServletURL,string repName,string artName,string number,string buildTime,string duration,string result,string sourcePath,string sourceVersion,string environment,vector<string> source,vector<string> target,list<DepMessage> depMsgList)
{
	CURL *curl = NULL;
	CURLcode code;
	CURLFORMcode fromCode;
	string content;
	string log("\n<--------------------------------Upload Build Library---------------------------->\n");
	curl_httppost *post = NULL;
	curl_httppost *last =NULL;

	

	log += addFormField(&post,&last,"RepositoryName",repName);
	log += addFormField(&post,&last,"ArtifactName",artName);
	log += addFormField(&post,&last,"Number",number);
	log += addFormField(&post,&last,"BuildTime",buildTime);
	log += addFormField(&post,&last,"Duration",duration);
	log += addFormField(&post,&last,"Result",result);
	log += addFormField(&post,&last,"SourcePath",sourcePath);
	log += addFormField(&post,&last,"SourceVersion",sourceVersion);
	log += addFormField(&post,&last,"Environment",environment);

	int size = depMsgList.size();
	stringstream newstr;
	newstr<<size;
	string sizestr;
	newstr>>sizestr;
	log += addFormField(&post,&last,"DepCount",sizestr);
	int index = 0;
	for (list<DepMessage>::iterator depIter=depMsgList.begin();depIter != depMsgList.end();++depIter)
	{
		//DepMessage depMsg = *depIter;
		char temp[30];
		sprintf(temp,"%s%d","DepFlag_",index);
		log += addFormField(&post,&last,temp,depIter->flag);
		sprintf(temp,"%s%d","DepRepository_",index);
		log += addFormField(&post,&last,temp,depIter->repName);
		sprintf(temp,"%s%d","DepName_",index);
		log += addFormField(&post,&last,temp,depIter->artName);
		sprintf(temp,"%s%d","DepVersion_",index);
		log += addFormField(&post,&last,temp,depIter->version);
		sprintf(temp,"%s%d","DepPath_",index);
		log += addFormField(&post,&last,temp,depIter->path);
		sprintf(temp,"%s%d","DepLocation_",index);
		log += addFormField(&post,&last,temp,depIter->localPath);

		index ++;
	}

	log += addFormFile(&post,&last,source,target,log);


	CurlUploadInit(curl,pServletURL.c_str(), content,post );

	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}


	//printf("%s\n",content);
	curl_formfree(post);
	curl_easy_cleanup(curl);


	curl_global_cleanup(); 

	//return content.append(log);
	return log;

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
	return true;
}

void DeleteFile (string &path)//path为绝对路径
{
	if (GetFileAttributes(path.c_str())!=FILE_ATTRIBUTE_DIRECTORY)
	{
		string dele = "del \""+path+"\"";
		system(dele.c_str());
		return;
	}
	string DirName = path ;
	string Dot1(".");
	string Dot2("..");
	WIN32_FIND_DATA FindData ;//文件搜索结构
	HANDLE Find ;//句柄 
	string DirFindName = DirName+"\\*.*";
	Find = FindFirstFile(DirFindName.c_str() , &FindData);
	FindNextFile(Find,&FindData);
	if ( Find == INVALID_HANDLE_VALUE )//无效句柄
	{
		FindClose(Find);
		cout <<" handle error"<<endl;
		//exit( 0 );
		return;
	}
	while (1)
	{
		if (!FindNextFile(Find,&FindData))//搜索下一个文件
			break;
		//string strTmpName = DirName + FindData.cFileName ;
		if ( Dot1 != FindData.cFileName || Dot2 != FindData.cFileName )
		{
			if ( FindData.dwFileAttributes == 16 )//找到的是文件夹
			{
				string NewDirName = DirName + "\\" + FindData.cFileName  ;
				DeleteFile(NewDirName);//递归查找
			}
			else
			{
				string strImg = DirName + "\\" + FindData.cFileName ;
				string dele = "del \"" + strImg+"\"" ;
				system(dele.c_str()) ;
			}
		}
		
	}
	FindClose(Find);
	RemoveDirectory(path.c_str());
}

void GetFiles(string path,vector<string> &files)
{
	string p;  
	string str;
	
	if (path.find("*")==string::npos&&!PathFileExists(path.c_str()))
	{
		return;
	}
	if (GetFileAttributes(path.c_str())!=FILE_ATTRIBUTE_DIRECTORY)
	{
		int index = path.rfind("\\");
		string name = path.substr(index);
		
		int ind = name.find("*");
		if (ind>0)
		{
			p.assign(path);
			path = path.substr(0,index);
		}else
		{
			files.push_back(path);
			return;
		}
	}else{
		p.assign(path).append("\\*");
	}
    long   hFile   =   0;  
	struct _finddata_t fileinfo;
  
  
    if((hFile= _findfirst(p.c_str(),&fileinfo))   !=   -1)  
	{    
        do {
            if((fileinfo.attrib&_A_SUBDIR)) {    
                if   (strcmp(fileinfo.name,".")   !=   0   &&   strcmp(fileinfo.name,"..")   !=   0)    
                    GetFiles(p.assign(path).append("\\").append(fileinfo.name), files);    
            }  else  {    
                files.push_back(path.append("\\").append(fileinfo.name)  );  
            }    
        }   while   (_findnext(hFile,&fileinfo)   ==   0);    
  
        _findclose(hFile);    
    }  
}

string addFormFile(curl_httppost **post,curl_httppost **last,vector<string> directory,vector<string> target,string &log)
{
	//string log;
	vector<string>::iterator targetIter=target.begin();
	for (vector<string>::iterator iter=directory.begin();iter != directory.end();++iter)
	{

		vector<string> files;
		GetFiles(*iter,files);

		for (vector<string>::iterator fileiter=files.begin();fileiter != files.end();++fileiter)
		{
			string file = *fileiter;
			file = changeSeparator(file);
			int index = file.find_last_of("\\");
			string filename = file.substr(index+1);
			string filepath = *targetIter+"\\"+filename;
			filepath = changeSeparator(filepath);
			if (*targetIter==".")
			{
				if (filename=="log")
				{
					writeLog(log,file);
				}
				filepath = filename;
			}
			//string filepath = *targetIter+filename;
			curl_formadd(post,last, CURLFORM_COPYNAME, "file",CURLFORM_FILE,file.c_str(),CURLFORM_FILENAME,filepath.c_str(),CURLFORM_END);

			log += "[Log-->] Upload File: " + file + " ---> " + filepath + "\n";
			//log.append("Upload File: ").append(file.c_str()).append("  To  ").append(filepath.c_str()).append("\n");

		}

		targetIter++;
	}

	return log;
}

string addFormField(curl_httppost **post,curl_httppost **last,string name,string text)
{
	curl_formadd(post,last, CURLFORM_COPYNAME, name.c_str(),CURLFORM_COPYCONTENTS,text.c_str(),CURLFORM_END);
	string str = "[Log-->] Send Message: "+name+" ---> "+text + "\n";
	//return str.append("Name->").append(name).append("  Value->").append(text);
	return str;
}

string ExeDownLoad(char * pServletURL, char *pArgument, char *pDestPath)
{
	string stZipFile = pDestPath;
	stZipFile += "\\test1.zip";
	string content;
	string log("\n");
	char cmd[500];
	memset(cmd,0,500);

	if(!PathFileExists(pDestPath))
	{
		if (!CreateAllDirectory(pDestPath))
		{
			return "create directory error";
		}
		
	}

	fp = fopen(stZipFile.c_str(), "wb+");
	if(NULL == fp){
		return "open file error";
	}

	if(!GetURLDataByCurl(pServletURL, content, pArgument)){
		return "get url data error";
	}

	fflush(fp);
	fclose(fp);

	sprintf(cmd,"7z x \"%s\" -y -o\"%s\"",stZipFile.c_str(),pDestPath);
	int exitCode;
	log += ExeCommand(cmd,exitCode,NULL);
	/*
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
	*/
//	string zipFile("\"");
//	zipFile.append(stZipFile).append("\"");
	//remove(stZipFile.c_str());
	
	return log;//content.append(log);
}

bool CurlInit(CURL *&curl, const char* url, string &content, char *pArgument)
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

long Writer(void *data, int size, int nmemb, string &content)
{
	int written = fwrite(data, size, nmemb, fp);
	return written;
}

bool GetURLDataByCurl(const char* URL,  string &content, char *pArgument)
{
	CURL *curl = NULL;
	CURLcode code;
	string error;

	code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if(code != CURLE_OK){
		return false;
	} 

	if(!CurlInit(curl,URL, content, pArgument)){
		return false;
	}

	code = curl_easy_perform(curl);
	if(code != CURLE_OK){
		return false;
	}

	curl_easy_cleanup(curl);

	curl_global_cleanup(); 
	return true;
}
/*
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
*/


string changeSeparator(string path)
{
	int tIndex = string::npos;
	while((tIndex = path.find('/')) != string::npos){
		path = path.replace(tIndex, 1, "\\");
	}

	return path;
}