#include "stdafx.h"
#include "Public.h"

int SubstrCount(string sSource, string sSubstr)
{
	if(sSource.length() <= 0){
		return 0;
	}

	int SubstrLen = sSubstr.length();
	if(SubstrLen <= 0){
		return 0;
	}

	int Times = 0, pos = 0;
	while(string::npos != (pos = sSource.find(sSubstr))){
		if(sSource.length()-SubstrLen-pos > 0){
			sSource = sSource.substr(pos+SubstrLen, sSource.length());
			Times++;
		}
		else{
			break;
		}
	}

	return Times;
}

void RidPercent20(string &sDepURL)
{
	int pos = -1;
	while(string::npos != (pos = sDepURL.find("%20"))){
		string tsDepURL = sDepURL;
		sDepURL = tsDepURL.substr(0, pos);
		sDepURL += " ";
		sDepURL += tsDepURL.substr(pos+3, tsDepURL.length());
	}
}

string CStringToString(CString SourceStr)
{
	CStringA TempSourceStr(SourceStr.GetBuffer(0));
	SourceStr.ReleaseBuffer();

	string Name(TempSourceStr.GetBuffer(0));
	TempSourceStr.ReleaseBuffer();

	return Name;
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

bool GetFatherURL(string sCrtURL, string &sFatherURL)
{
	int pos = sCrtURL.rfind('/');
	if(pos == string::npos){
		return false;
	}

	sFatherURL = sCrtURL.substr(0, pos);

	return true;
}

bool GetWcPath(string sCrtPath, string &sWcPath)
{
	string sFatherPath = sCrtPath;
	string sSvnPath;

	while(1){
		sSvnPath = sCrtPath + "\\.svn";
		if(PathFileExists(sSvnPath.c_str())){
			sWcPath = sCrtPath;
			return true;
		}

		if(GetFatherPath(sCrtPath, sFatherPath)){
			sCrtPath = sFatherPath;
		}
		else{
			break;
		}
	}

	return false;
}
