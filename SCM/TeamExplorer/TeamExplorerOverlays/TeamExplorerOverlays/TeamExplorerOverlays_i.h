

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 20 14:42:05 2013
 */
/* Compiler settings for TeamExplorerOverlays.idl:
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

#ifndef __TeamExplorerOverlays_i_h__
#define __TeamExplorerOverlays_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IReadOnly_FWD_DEFINED__
#define __IReadOnly_FWD_DEFINED__
typedef interface IReadOnly IReadOnly;
#endif 	/* __IReadOnly_FWD_DEFINED__ */


#ifndef __IAdd_FWD_DEFINED__
#define __IAdd_FWD_DEFINED__
typedef interface IAdd IAdd;
#endif 	/* __IAdd_FWD_DEFINED__ */


#ifndef __IReadWrite_FWD_DEFINED__
#define __IReadWrite_FWD_DEFINED__
typedef interface IReadWrite IReadWrite;
#endif 	/* __IReadWrite_FWD_DEFINED__ */


#ifndef __IModify_FWD_DEFINED__
#define __IModify_FWD_DEFINED__
typedef interface IModify IModify;
#endif 	/* __IModify_FWD_DEFINED__ */


#ifndef __IConflict_FWD_DEFINED__
#define __IConflict_FWD_DEFINED__
typedef interface IConflict IConflict;
#endif 	/* __IConflict_FWD_DEFINED__ */


#ifndef __IUnversion_FWD_DEFINED__
#define __IUnversion_FWD_DEFINED__
typedef interface IUnversion IUnversion;
#endif 	/* __IUnversion_FWD_DEFINED__ */


#ifndef __ReadOnly_FWD_DEFINED__
#define __ReadOnly_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReadOnly ReadOnly;
#else
typedef struct ReadOnly ReadOnly;
#endif /* __cplusplus */

#endif 	/* __ReadOnly_FWD_DEFINED__ */


#ifndef __Add_FWD_DEFINED__
#define __Add_FWD_DEFINED__

#ifdef __cplusplus
typedef class Add Add;
#else
typedef struct Add Add;
#endif /* __cplusplus */

#endif 	/* __Add_FWD_DEFINED__ */


#ifndef __ReadWrite_FWD_DEFINED__
#define __ReadWrite_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReadWrite ReadWrite;
#else
typedef struct ReadWrite ReadWrite;
#endif /* __cplusplus */

#endif 	/* __ReadWrite_FWD_DEFINED__ */


#ifndef __Modify_FWD_DEFINED__
#define __Modify_FWD_DEFINED__

#ifdef __cplusplus
typedef class Modify Modify;
#else
typedef struct Modify Modify;
#endif /* __cplusplus */

#endif 	/* __Modify_FWD_DEFINED__ */


#ifndef __Conflict_FWD_DEFINED__
#define __Conflict_FWD_DEFINED__

#ifdef __cplusplus
typedef class Conflict Conflict;
#else
typedef struct Conflict Conflict;
#endif /* __cplusplus */

#endif 	/* __Conflict_FWD_DEFINED__ */


#ifndef __Unversion_FWD_DEFINED__
#define __Unversion_FWD_DEFINED__

#ifdef __cplusplus
typedef class Unversion Unversion;
#else
typedef struct Unversion Unversion;
#endif /* __cplusplus */

#endif 	/* __Unversion_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IReadOnly_INTERFACE_DEFINED__
#define __IReadOnly_INTERFACE_DEFINED__

/* interface IReadOnly */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IReadOnly;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("14B56641-6A51-4619-A810-0AD2DC5868BC")
    IReadOnly : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IReadOnlyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadOnly * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadOnly * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadOnly * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadOnly * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadOnly * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadOnly * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadOnly * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IReadOnlyVtbl;

    interface IReadOnly
    {
        CONST_VTBL struct IReadOnlyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadOnly_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadOnly_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadOnly_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadOnly_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadOnly_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadOnly_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadOnly_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReadOnly_INTERFACE_DEFINED__ */


#ifndef __IAdd_INTERFACE_DEFINED__
#define __IAdd_INTERFACE_DEFINED__

/* interface IAdd */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAdd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E0EA5F4F-560E-498A-8E8F-34B1F3938CC4")
    IAdd : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAddVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAdd * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAdd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAdd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAdd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAdd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAdd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAdd * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAddVtbl;

    interface IAdd
    {
        CONST_VTBL struct IAddVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAdd_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAdd_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAdd_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAdd_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAdd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAdd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAdd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAdd_INTERFACE_DEFINED__ */


#ifndef __IReadWrite_INTERFACE_DEFINED__
#define __IReadWrite_INTERFACE_DEFINED__

/* interface IReadWrite */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IReadWrite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64372ACC-923B-4E1F-B9B3-611ECCAD1681")
    IReadWrite : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IReadWriteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadWrite * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadWrite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadWrite * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadWrite * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadWrite * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadWrite * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadWrite * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IReadWriteVtbl;

    interface IReadWrite
    {
        CONST_VTBL struct IReadWriteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadWrite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadWrite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadWrite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadWrite_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadWrite_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadWrite_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadWrite_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReadWrite_INTERFACE_DEFINED__ */


#ifndef __IModify_INTERFACE_DEFINED__
#define __IModify_INTERFACE_DEFINED__

/* interface IModify */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IModify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7EF02D46-8D13-4DB0-97D8-2CA9ACD8141C")
    IModify : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IModifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IModify * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IModify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IModify * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IModify * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IModify * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IModify * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IModify * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IModifyVtbl;

    interface IModify
    {
        CONST_VTBL struct IModifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModify_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IModify_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IModify_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IModify_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IModify_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IModify_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IModify_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IModify_INTERFACE_DEFINED__ */


#ifndef __IConflict_INTERFACE_DEFINED__
#define __IConflict_INTERFACE_DEFINED__

/* interface IConflict */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IConflict;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FE0B7D3A-49CA-4981-B0C3-A8791782B846")
    IConflict : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IConflictVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConflict * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConflict * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConflict * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IConflict * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IConflict * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IConflict * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IConflict * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IConflictVtbl;

    interface IConflict
    {
        CONST_VTBL struct IConflictVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConflict_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IConflict_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IConflict_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IConflict_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IConflict_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IConflict_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IConflict_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IConflict_INTERFACE_DEFINED__ */


#ifndef __IUnversion_INTERFACE_DEFINED__
#define __IUnversion_INTERFACE_DEFINED__

/* interface IUnversion */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUnversion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2EE5CCF-5ECE-4447-B935-B145F5E39076")
    IUnversion : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IUnversionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnversion * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnversion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnversion * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUnversion * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUnversion * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUnversion * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUnversion * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IUnversionVtbl;

    interface IUnversion
    {
        CONST_VTBL struct IUnversionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnversion_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnversion_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnversion_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnversion_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUnversion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUnversion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUnversion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnversion_INTERFACE_DEFINED__ */



#ifndef __TeamExplorerOverlaysLib_LIBRARY_DEFINED__
#define __TeamExplorerOverlaysLib_LIBRARY_DEFINED__

/* library TeamExplorerOverlaysLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TeamExplorerOverlaysLib;

EXTERN_C const CLSID CLSID_ReadOnly;

#ifdef __cplusplus

class DECLSPEC_UUID("9A3FEB2B-8A44-4840-B494-51DD21C256AC")
ReadOnly;
#endif

EXTERN_C const CLSID CLSID_Add;

#ifdef __cplusplus

class DECLSPEC_UUID("60886D45-2842-47FC-915C-711DC3C220C8")
Add;
#endif

EXTERN_C const CLSID CLSID_ReadWrite;

#ifdef __cplusplus

class DECLSPEC_UUID("4B5FE33A-F677-460C-8925-9772D92A4475")
ReadWrite;
#endif

EXTERN_C const CLSID CLSID_Modify;

#ifdef __cplusplus

class DECLSPEC_UUID("90A76876-02C2-4E62-B798-B63B002636F0")
Modify;
#endif

EXTERN_C const CLSID CLSID_Conflict;

#ifdef __cplusplus

class DECLSPEC_UUID("661CC6B0-27F4-4392-A807-454025AC4E55")
Conflict;
#endif

EXTERN_C const CLSID CLSID_Unversion;

#ifdef __cplusplus

class DECLSPEC_UUID("7146F01D-543B-4DDB-BB9A-74E483DE4E27")
Unversion;
#endif
#endif /* __TeamExplorerOverlaysLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


