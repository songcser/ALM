#pragma once
#include "SourceCode.h"
#include "Dependence.h"
#include "BuildStep.h"
#include "ImportStep.h"
#include "Publish.h"
#include <list>


class Project
{
private:
	string id;
	string fileName;
	string name;
	SourceCode sourceCode;
	list<Dependence *> *depList;
	list<BuildStep *> *buildStep;
	list<ImportStep *> *importStep;
	Publish publish;

public:
	Project(void);
	~Project(void);

	string GetId();
	void SetId(string id);

	string GetFileName();
	void SetFileName(string name);

	string GetName();
	void SetName(string name);

	SourceCode GetSourceCode();
	void SetSourceCode(SourceCode sourceCode);

	list<Dependence *> * GetDependences();
	void SetDependences(list<Dependence *> *depList);

	list<BuildStep *> * GetBuildStep();
	void SetBuildStep(list<BuildStep *> *buildStep);

	list<ImportStep *> * GetImportStep();
	void SetImportStep(list<ImportStep *> *importStep);

	Publish GetPublish();
	void SetPublish(Publish publish);
};

