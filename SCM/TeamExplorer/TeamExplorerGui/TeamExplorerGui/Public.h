#pragma once

#ifndef TEAM_EXPLORER_PUBLIC
#define TEAM_EXPLORER_PUBLIC

#define WM_TEAM_EXPLORER_EXIT WM_USER+10

#define FLAG_FILE_NAME "ScmTeamExplorer.dat"
#define CONF_FILE_NAME "ScmConfigure.xml"

string CStringToString(CString SourceStr);

bool GetFatherPath(string sCrtPath, string &sFatherPath);

bool GetFatherURL(string sCrtURL, string &sFatherURL);

int SubstrCount(string sSource, string sSubstr);

bool GetWcPath(string sCrtPath, string &sWcPath);

void RidPercent20(string &sDepURL);

#endif