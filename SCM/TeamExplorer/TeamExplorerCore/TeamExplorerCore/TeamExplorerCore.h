// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TEAMEXPLORERCORE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TEAMEXPLORERCORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TEAMEXPLORERCORE_EXPORTS
#define TEAMEXPLORERCORE_API __declspec(dllexport)
#else
#define TEAMEXPLORERCORE_API __declspec(dllimport)
#endif

#define FLAG_FILE_NAME "ScmTeamExplorer.dat"

string CutStr(int from, int to, string srcStr);

string ExeCmd(char *pszCmd);

bool GetFatherPath(string sCrtPath, string &sFatherPath);

bool HasConflict(string strRet);

bool HasModify(string strRet);

TEAMEXPLORERCORE_API BOOL IsWorkCopy(vector<string> *sFiles, int iNumFiles, string &sWcPath);

TEAMEXPLORERCORE_API BOOL CouldWrite(vector<string> *sFiles, vector<string> *sWriteFiles, int iNumFiles);

TEAMEXPLORERCORE_API BOOL IsProductOrTags(string sWcPath);

TEAMEXPLORERCORE_API BOOL IsTeamExplorer(string sWcPath);

TEAMEXPLORERCORE_API BOOL IsRealWorkCopy(string sWcPath);

TEAMEXPLORERCORE_API int GetPathStatus(string sPath, int iPathType);

TEAMEXPLORERCORE_API int GetPathStatusForNb(string sPath, int iPathType);

