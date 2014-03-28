#pragma once
#include <string>
using namespace std;

class BuildStep
{
private:
	string name;
	string program;
	string options;
public:
	BuildStep(void);
	~BuildStep(void);

	string GetName();
	void SetName(string name);

	string GetProgram();
	void SetProgram(string program);

	string GetOptions();
	void SetOptions(string name);
};

