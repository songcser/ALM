#pragma once
#include <string>
using namespace std;

class  SourceCode
{
private:
	string url;
	string version;
	string localPath;
public:
	SourceCode(void);
	~SourceCode(void);

	SourceCode(SourceCode &sourceCode);

	string GetUrl();
	void SetUrl(string url);

	string GetVersion();
	void SetVersion(string version);

	string GetLocalPath();
	void SetLocalPath(string);
};

