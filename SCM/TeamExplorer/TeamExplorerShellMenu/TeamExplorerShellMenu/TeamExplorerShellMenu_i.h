

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Jun 09 09:55:55 2013
 */
/* Compiler settings for TeamExplorerShellMenu.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TeamExplorerShellMenu_i_h__
#define __TeamExplorerShellMenu_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPopupMenu_FWD_DEFINED__
#define __IPopupMenu_FWD_DEFINED__
typedef interface IPopupMenu IPopupMenu;
#endif 	/* __IPopupMenu_FWD_DEFINED__ */


#ifndef __PopupMenu_FWD_DEFINED__
#define __PopupMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class PopupMenu PopupMenu;
#else
typedef struct PopupMenu PopupMenu;
#endif /* __cplusplus */

#endif 	/* __PopupMenu_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPopupMenu_INTERFACE_DEFINED__
#define __IPopupMenu_INTERFACE_DEFINED__

/* interface IPopupMenu */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPopupMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3632FAD-57F2-4185-9C88-1B89671775DD")
    IPopupMenu : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetEnv( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Checkout( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Checkin( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Revert( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Merge( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowLog( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Diff( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPopupMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPopupMenu * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPopupMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPopupMenu * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPopupMenu * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPopupMenu * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPopupMenu * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPopupMenu * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetEnv )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Checkout )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Checkin )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Revert )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowLog )( 
            IPopupMenu * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Diff )( 
            IPopupMenu * This);
        
        END_INTERFACE
    } IPopupMenuVtbl;

    interface IPopupMenu
    {
        CONST_VTBL struct IPopupMenuVtbl *lpVtbl;
		[] HRESULT Compare(void);
		[] HRESULT UpdateRelyFiles(void);
	};

    

#ifdef COBJMACROS


#define IPopupMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPopupMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPopupMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPopupMenu_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPopupMenu_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPopupMenu_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPopupMenu_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPopupMenu_SetEnv(This)	\
    ( (This)->lpVtbl -> SetEnv(This) ) 

#define IPopupMenu_Checkout(This)	\
    ( (This)->lpVtbl -> Checkout(This) ) 

#define IPopupMenu_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IPopupMenu_Commit(This)	\
    ( (This)->lpVtbl -> Commit(This) ) 

#define IPopupMenu_Checkin(This)	\
    ( (This)->lpVtbl -> Checkin(This) ) 

#define IPopupMenu_Cancel(This)	\
    ( (This)->lpVtbl -> Cancel(This) ) 

#define IPopupMenu_Add(This)	\
    ( (This)->lpVtbl -> Add(This) ) 

#define IPopupMenu_Revert(This)	\
    ( (This)->lpVtbl -> Revert(This) ) 

#define IPopupMenu_Merge(This)	\
    ( (This)->lpVtbl -> Merge(This) ) 

#define IPopupMenu_ShowLog(This)	\
    ( (This)->lpVtbl -> ShowLog(This) ) 

#define IPopupMenu_Diff(This)	\
    ( (This)->lpVtbl -> Diff(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPopupMenu_INTERFACE_DEFINED__ */



#ifndef __TeamExplorerShellMenuLib_LIBRARY_DEFINED__
#define __TeamExplorerShellMenuLib_LIBRARY_DEFINED__

/* library TeamExplorerShellMenuLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TeamExplorerShellMenuLib;

EXTERN_C const CLSID CLSID_PopupMenu;

#ifdef __cplusplus

class DECLSPEC_UUID("A53268F8-176C-4C49-AB0C-7813F69361FF")
PopupMenu;
#endif
#endif /* __TeamExplorerShellMenuLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


