// dllmain.h : Declaration of module class.

class CTeamExplorerShellMenuModule : public ATL::CAtlDllModuleT< CTeamExplorerShellMenuModule >
{
public :
	DECLARE_LIBID(LIBID_TeamExplorerShellMenuLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEAMEXPLORERSHELLMENU, "{C08F75E1-13AB-4ACF-A888-07919919BABD}")
};

extern class CTeamExplorerShellMenuModule _AtlModule;
