#pragma once
#include "ImportItem.h"
#include <list>

class Publish
{
private:
	string url;
	string category;
	string component;
	string version;
	list<ImportItem *> item;

public:
	Publish(void);
	~Publish(void);

	string GetUrl();
	void SetUrl(string url);

	string GetCategory();
	void SetCategory(string category);

	string GetComponent();
	void SetComponent(string component);

	string GetVersion();
	void SetVersion(string version);

	list<ImportItem *> GetImportItem();
	void SetImportItem(list<ImportItem*> item);
};

