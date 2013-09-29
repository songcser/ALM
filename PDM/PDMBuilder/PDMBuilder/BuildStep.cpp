#include "StdAfx.h"
#include "BuildStep.h"


BuildStep::BuildStep(void)
{
}


BuildStep::~BuildStep(void)
{
}

string BuildStep::GetName(){
	return name;
}

void BuildStep::SetName(string name){
	this->name = name;
}

string BuildStep::GetProgram(){
	return program;
}

void BuildStep::SetProgram(string program){
	this->program = program;
}

string BuildStep::GetOptions(){
	return options;
}

void BuildStep::SetOptions(string options){
	this->options = options;
}