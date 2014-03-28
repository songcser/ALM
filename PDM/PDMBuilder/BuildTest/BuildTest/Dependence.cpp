#include "StdAfx.h"
#include "Dependence.h"


Dependence::Dependence(void)
{
}


Dependence::~Dependence(void)
{
}

string Dependence::GetServer(){
	return server;
}

void Dependence::SetServer(string server){
	this->server = server;
}

string Dependence::GetFlag(){
	return flag;
}

void Dependence::SetFlag(string flag){
	this->flag = flag;
}

string Dependence::GetRepository()
{
	return repository;
}

void Dependence::SetRepository(string repository){
	this->repository = repository;
}

string Dependence::GetName(){
	return name;
}

void Dependence::SetName(string name){
	this->name = name;
}

string Dependence::GetVersion(){
	return version;
}

void Dependence::SetVersion(string version){
	this->version = version;
}

string Dependence::GetPath(){
	return path;
}

void Dependence::SetPath(string path){
	this->path = path;
}

string Dependence::GetLocalPath(){
	return localPath;
}

void Dependence::SetLocalPath(string localPath){
	this->localPath = localPath;
}