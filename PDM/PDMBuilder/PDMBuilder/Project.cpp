#include "StdAfx.h"
#include "Project.h"


Project::Project(void)
{

}


Project::~Project(void)
{
	delete depList;
	delete buildStep;
	delete importStep;
}

string Project::GetId(){
	return id;
}

void Project::SetId(string id){
	this->id = id;
}

string Project::GetFileName(){
	return fileName;
}

void Project::SetFileName(string name)
{
	this->fileName = name;
}

string Project::GetName(){
	return name;
}

void Project::SetName(string name){
	this->name = name;
}

SourceCode Project::GetSourceCode(){
	return sourceCode;
}

void Project::SetSourceCode(SourceCode sourceCode){
	this->sourceCode = sourceCode;
}

list<Dependence *> * Project::GetDependences(){
	return depList;
}

void Project::SetDependences(list<Dependence *> *depList){
	this->depList = depList;
}

list<BuildStep *> * Project::GetBuildStep(){
	return buildStep;
}

void Project::SetBuildStep(list<BuildStep *> *buildStep){
	this->buildStep = buildStep;
}

list<ImportStep *> * Project::GetImportStep(){
	return importStep;
}

void Project::SetImportStep(list<ImportStep *> *importStep){
	this->importStep = importStep;
}

Publish Project::GetPublish(){
	return publish;
}

void Project::SetPublish(Publish publish){
	this->publish = publish;
}