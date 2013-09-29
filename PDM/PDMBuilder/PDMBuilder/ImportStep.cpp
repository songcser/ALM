#include "StdAfx.h"
#include "ImportStep.h"


ImportStep::ImportStep(void)
{
}


ImportStep::~ImportStep(void)
{
}

string ImportStep::GetName(){
	return name;
}

void ImportStep::SetName(string name){
	this->name = name;
}

string ImportStep::GetUrl(){
	return url;
}

void ImportStep::SetUrl(string url){
	this->url = url;
}

list<ImportItem *> ImportStep::GetItem(){
	return item;
}

void ImportStep::setItem(list<ImportItem *> item){
	this->item = item;
}