#pragma once

#include <string>
using namespace std;

class Dependence
{
private:
	string server;
	string flag;
	string repository;
	string name;
	string version;
	string path;
	string localPath;
public:
	Dependence(void);
	~Dependence(void);

	string GetServer();
	void SetServer(string server);

	string GetFlag();
	void SetFlag(string flag);

	string GetRepository();
	void SetRepository(string repository);

	string GetName();
	void SetName(string name);

	string GetVersion();
	void SetVersion(string version);

	string GetPath();
	void SetPath(string path);

	string GetLocalPath();
	void SetLocalPath(string localPath);
};

