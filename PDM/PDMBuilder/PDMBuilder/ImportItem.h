#pragma once
class ImportItem
{
private:
	string source;
	string target;
public:
	ImportItem(void);
	~ImportItem(void);

	string GetSource();
	void SetSource(string source);

	string GetTarget();
	void SetTarget(string target);
};

