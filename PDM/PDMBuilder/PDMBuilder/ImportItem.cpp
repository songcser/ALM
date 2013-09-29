#include "StdAfx.h"
#include "ImportItem.h"


ImportItem::ImportItem(void)
{
}


ImportItem::~ImportItem(void)
{
}

string ImportItem::GetSource(){
	return source;
}

void ImportItem::SetSource(string source){
	this->source = source;
}

string ImportItem::GetTarget(){
	return target;
}

void ImportItem::SetTarget(string target){
	this->target = target;
}