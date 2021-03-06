

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 04 19:59:54 2018
 */
/* Compiler settings for C:\Users\rutwi\AppData\Local\Temp\WRLCOMServer.idl-89659557:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=ARM 8.00.0603 
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

#ifndef __WRLCOMServer_h_h__
#define __WRLCOMServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(__cplusplus)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
#endif


/* Forward Declarations */ 

#ifndef ____x_ABI_CWRLCOMServer_CISum_FWD_DEFINED__
#define ____x_ABI_CWRLCOMServer_CISum_FWD_DEFINED__
typedef interface __x_ABI_CWRLCOMServer_CISum __x_ABI_CWRLCOMServer_CISum;

#ifdef __cplusplus
namespace ABI {
    namespace WRLCOMServer {
        interface ISum;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CWRLCOMServer_CISum_FWD_DEFINED__ */


#ifndef ____x_ABI_CWRLCOMServer_CISubtract_FWD_DEFINED__
#define ____x_ABI_CWRLCOMServer_CISubtract_FWD_DEFINED__
typedef interface __x_ABI_CWRLCOMServer_CISubtract __x_ABI_CWRLCOMServer_CISubtract;

#ifdef __cplusplus
namespace ABI {
    namespace WRLCOMServer {
        interface ISubtract;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CWRLCOMServer_CISubtract_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"
#include "Windows.Foundation.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WRLCOMServer_0000_0000 */
/* [local] */ 



#ifdef __cplusplus
namespace ABI {
namespace WRLCOMServer {
class CSumSubtract;
} /*WRLCOMServer*/
}
#endif
#if !defined(____x_ABI_CWRLCOMServer_CISum_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_WRLCOMServer_ISum[] = L"WRLCOMServer.ISum";
#endif /* !defined(____x_ABI_CWRLCOMServer_CISum_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_WRLCOMServer_0000_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CWRLCOMServer_CISum_INTERFACE_DEFINED__
#define ____x_ABI_CWRLCOMServer_CISum_INTERFACE_DEFINED__

/* interface __x_ABI_CWRLCOMServer_CISum */
/* [uuid][object] */ 



/* interface ABI::WRLCOMServer::ISum */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CWRLCOMServer_CISum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace WRLCOMServer {
            
            MIDL_INTERFACE("0be9429f-2c7a-40e8-bb0a-85bcb1749367")
            ISum : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE SumOfTwoIntegers( 
                    /* [in] */ int a,
                    /* [in] */ int b,
                    /* [out][retval] */ int *value) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ISum = __uuidof(ISum);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CWRLCOMServer_CISumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CWRLCOMServer_CISum * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CWRLCOMServer_CISum * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CWRLCOMServer_CISum * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CWRLCOMServer_CISum * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CWRLCOMServer_CISum * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CWRLCOMServer_CISum * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *SumOfTwoIntegers )( 
            __x_ABI_CWRLCOMServer_CISum * This,
            /* [in] */ int a,
            /* [in] */ int b,
            /* [out][retval] */ int *value);
        
        END_INTERFACE
    } __x_ABI_CWRLCOMServer_CISumVtbl;

    interface __x_ABI_CWRLCOMServer_CISum
    {
        CONST_VTBL struct __x_ABI_CWRLCOMServer_CISumVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CWRLCOMServer_CISum_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CWRLCOMServer_CISum_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CWRLCOMServer_CISum_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CWRLCOMServer_CISum_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CWRLCOMServer_CISum_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CWRLCOMServer_CISum_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CWRLCOMServer_CISum_SumOfTwoIntegers(This,a,b,value)	\
    ( (This)->lpVtbl -> SumOfTwoIntegers(This,a,b,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CWRLCOMServer_CISum_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WRLCOMServer_0000_0001 */
/* [local] */ 

#if !defined(____x_ABI_CWRLCOMServer_CISubtract_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_WRLCOMServer_ISubtract[] = L"WRLCOMServer.ISubtract";
#endif /* !defined(____x_ABI_CWRLCOMServer_CISubtract_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_WRLCOMServer_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0001_v0_0_s_ifspec;

#ifndef ____x_ABI_CWRLCOMServer_CISubtract_INTERFACE_DEFINED__
#define ____x_ABI_CWRLCOMServer_CISubtract_INTERFACE_DEFINED__

/* interface __x_ABI_CWRLCOMServer_CISubtract */
/* [uuid][object] */ 



/* interface ABI::WRLCOMServer::ISubtract */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CWRLCOMServer_CISubtract;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace WRLCOMServer {
            
            MIDL_INTERFACE("CD3DFDF1-A779-4E30-B345-5281C40E10F4")
            ISubtract : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE SubtractionOfTwoIntegers( 
                    /* [in] */ int a,
                    /* [in] */ int b,
                    /* [out][retval] */ int *value) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ISubtract = __uuidof(ISubtract);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CWRLCOMServer_CISubtractVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CWRLCOMServer_CISubtract * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CWRLCOMServer_CISubtract * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CWRLCOMServer_CISubtract * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CWRLCOMServer_CISubtract * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CWRLCOMServer_CISubtract * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CWRLCOMServer_CISubtract * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *SubtractionOfTwoIntegers )( 
            __x_ABI_CWRLCOMServer_CISubtract * This,
            /* [in] */ int a,
            /* [in] */ int b,
            /* [out][retval] */ int *value);
        
        END_INTERFACE
    } __x_ABI_CWRLCOMServer_CISubtractVtbl;

    interface __x_ABI_CWRLCOMServer_CISubtract
    {
        CONST_VTBL struct __x_ABI_CWRLCOMServer_CISubtractVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CWRLCOMServer_CISubtract_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CWRLCOMServer_CISubtract_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CWRLCOMServer_CISubtract_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CWRLCOMServer_CISubtract_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CWRLCOMServer_CISubtract_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CWRLCOMServer_CISubtract_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CWRLCOMServer_CISubtract_SubtractionOfTwoIntegers(This,a,b,value)	\
    ( (This)->lpVtbl -> SubtractionOfTwoIntegers(This,a,b,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CWRLCOMServer_CISubtract_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WRLCOMServer_0000_0002 */
/* [local] */ 

#ifndef RUNTIMECLASS_WRLCOMServer_CSumSubtract_DEFINED
#define RUNTIMECLASS_WRLCOMServer_CSumSubtract_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_WRLCOMServer_CSumSubtract[] = L"WRLCOMServer.CSumSubtract";
#endif


/* interface __MIDL_itf_WRLCOMServer_0000_0002 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLCOMServer_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


