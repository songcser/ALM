// dllmain.h : Declaration of module class.

class CSmtATLModule : public ATL::CAtlDllModuleT< CSmtATLModule >
{
public :
	DECLARE_LIBID(LIBID_SmtATLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SMTATL, "{2E900F39-0E9B-460D-842D-2E451556B68B}")
};

extern class CSmtATLModule _AtlModule;
