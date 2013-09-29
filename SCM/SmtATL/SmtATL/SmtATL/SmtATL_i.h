

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Dec 07 19:40:04 2012
 */
/* Compiler settings for SmtATL.idl:
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

#ifndef __SmtATL_i_h__
#define __SmtATL_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISmtShell_FWD_DEFINED__
#define __ISmtShell_FWD_DEFINED__
typedef interface ISmtShell ISmtShell;
#endif 	/* __ISmtShell_FWD_DEFINED__ */


#ifndef __SmtShell_FWD_DEFINED__
#define __SmtShell_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmtShell SmtShell;
#else
typedef struct SmtShell SmtShell;
#endif /* __cplusplus */

#endif 	/* __SmtShell_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISmtShell_INTERFACE_DEFINED__
#define __ISmtShell_INTERFACE_DEFINED__

/* interface ISmtShell */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISmtShell;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8EC82675-DBFA-4205-9138-C8EFAD044BD1")
    ISmtShell : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtSetEnv( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtCheckout( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtUpdate( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtCommit( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtCheckin( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtCancel( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtAdd( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtRevert( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtMerge( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmtImport( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISmtShellVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISmtShell * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISmtShell * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISmtShell * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISmtShell * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISmtShell * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISmtShell * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISmtShell * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtSetEnv )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtCheckout )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtUpdate )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtCommit )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtCheckin )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtCancel )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtAdd )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtRevert )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtMerge )( 
            ISmtShell * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmtImport )( 
            ISmtShell * This);
        
        END_INTERFACE
    } ISmtShellVtbl;

    interface ISmtShell
    {
        CONST_VTBL struct ISmtShellVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISmtShell_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISmtShell_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISmtShell_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISmtShell_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISmtShell_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISmtShell_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISmtShell_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISmtShell_SmtSetEnv(This)	\
    ( (This)->lpVtbl -> SmtSetEnv(This) ) 

#define ISmtShell_SmtCheckout(This)	\
    ( (This)->lpVtbl -> SmtCheckout(This) ) 

#define ISmtShell_SmtUpdate(This)	\
    ( (This)->lpVtbl -> SmtUpdate(This) ) 

#define ISmtShell_SmtCommit(This)	\
    ( (This)->lpVtbl -> SmtCommit(This) ) 

#define ISmtShell_SmtCheckin(This)	\
    ( (This)->lpVtbl -> SmtCheckin(This) ) 

#define ISmtShell_SmtCancel(This)	\
    ( (This)->lpVtbl -> SmtCancel(This) ) 

#define ISmtShell_SmtAdd(This)	\
    ( (This)->lpVtbl -> SmtAdd(This) ) 

#define ISmtShell_SmtRevert(This)	\
    ( (This)->lpVtbl -> SmtRevert(This) ) 

#define ISmtShell_SmtMerge(This)	\
    ( (This)->lpVtbl -> SmtMerge(This) ) 

#define ISmtShell_SmtImport(This)	\
    ( (This)->lpVtbl -> SmtImport(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISmtShell_INTERFACE_DEFINED__ */



#ifndef __SmtATLLib_LIBRARY_DEFINED__
#define __SmtATLLib_LIBRARY_DEFINED__

/* library SmtATLLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SmtATLLib;

EXTERN_C const CLSID CLSID_SmtShell;

#ifdef __cplusplus

class DECLSPEC_UUID("E79F1E65-D384-4BF1-A55F-6BA86E2D2CB4")
SmtShell;
#endif
#endif /* __SmtATLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


