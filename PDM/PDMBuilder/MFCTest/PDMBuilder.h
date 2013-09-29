// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PDMBUILDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PDMBUILDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PDMBUILDER_EXPORTS
#define PDMBUILDER_API __declspec(dllexport)
#else
#define PDMBUILDER_API __declspec(dllimport)
#endif

// This class is exported from the PDMBuilder.dll

PDMBUILDER_API int fnPDMBuilder(void);

PDMBUILDER_API void setWorkSpace(string workspace);

//PDMBUILDER_API bool setConfigXML(string &xmlPath);
PDMBUILDER_API bool setConfigXML(char *xmlPath);

PDMBUILDER_API string checkout(string workspace);

//PDMBUILDER_API string getRelyFiles(string &workspace);
PDMBUILDER_API string getRelyFiles(char *workspace);

PDMBUILDER_API string updateRelyFiles(char *workspace);

PDMBUILDER_API string process();

PDMBUILDER_API string import();

PDMBUILDER_API string publish();