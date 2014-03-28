#include "StdAfx.h"
#include "Publish.h"


Publish::Publish(void)
{
}


Publish::~Publish(void)
{
}

string Publish::GetUrl(){
	return url;
}

void Publish::SetUrl(string url){
	this->url = url;
}

string Publish::GetCategory(){
	return category;
}

void Publish::SetCategory(string category){
	this->category = category;
}

string Publish::GetComponent(){
	return component;
}

void Publish::SetComponent(string component){
	this->component = component;
}

string Publish::GetVersion(){
	return version;
}

void Publish::SetVersion(string version){
	this->version = version;
}

list<ImportItem *> Publish::GetImportItem(){
	return item;
}

void Publish::SetImportItem(list<ImportItem *> item){
	this->item = item;
}