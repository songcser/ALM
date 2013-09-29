#include "StdAfx.h"
#include "SourceCode.h"


SourceCode::SourceCode()
{
}


SourceCode::~SourceCode()
{
}

SourceCode::SourceCode(SourceCode &sourceCode){
	this->url = sourceCode.url;
	this->version = sourceCode.version;
	this->localPath = sourceCode.localPath;
}

string SourceCode::GetUrl()
{
	return url;
}

void SourceCode::SetUrl(string url){
	this->url = url;
}

string SourceCode::GetVersion()
{
	return version;
}

void SourceCode::SetVersion(string version)
{
	this->version = version;
}

string SourceCode::GetLocalPath()
{
	return localPath;
}

void SourceCode::SetLocalPath(string localPath)
{
	this->localPath = localPath;
}