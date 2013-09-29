#pragma once
#include <list>
#include "ImportItem.h"
using namespace std;

class ImportStep
{
private:
	string name;
	string url;
	list<ImportItem *> item;	
public:
	ImportStep(void);
	~ImportStep(void);

	string GetName();
	void SetName(string name);

	string GetUrl();
	void SetUrl(string url);

	list<ImportItem *> GetItem();
	void setItem(list<ImportItem *> item);
};

