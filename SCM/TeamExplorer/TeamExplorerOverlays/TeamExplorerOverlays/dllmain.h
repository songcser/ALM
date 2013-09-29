// dllmain.h : Declaration of module class.

class CTeamExplorerOverlaysModule : public ATL::CAtlDllModuleT< CTeamExplorerOverlaysModule >
{
public :
	DECLARE_LIBID(LIBID_TeamExplorerOverlaysLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEAMEXPLOREROVERLAYS, "{8BE580C7-053E-42F3-94DC-1AD5B18301C2}")
};

extern class CTeamExplorerOverlaysModule _AtlModule;
