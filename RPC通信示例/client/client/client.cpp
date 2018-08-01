// client.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"..\..\server\server\rpc_h.h"
#include"..\..\server\server\rpc_c.c"

#pragma comment(lib, "Rpcrt4.lib")


#define RPC_PORT_GUID L"{0AD3C2E4-C14D-48E1-9CAF-502CFD189EE0}"

int main()
{
    RPC_STATUS Status = RPC_S_OK;
    TCHAR * pszStringBinding = NULL;

    Status = RpcStringBindingCompose(
        NULL,
        (RPC_WSTR)L"ncalrpc",
        NULL,
        (RPC_WSTR)RPC_PORT_GUID,
        NULL,
        (RPC_WSTR*)&pszStringBinding);
    if (RPC_S_OK != Status || !pszStringBinding) {
        return 0;
    }
    if (RPC_S_OK != RpcBindingFromStringBinding((RPC_WSTR)pszStringBinding, &RpcService_Binding)) {
        return 0;
    }

    WCHAR a[10] = {};

    RpcTryExcept
    {
        HRESULT lRet = RpcCall(a);
    int a = 0;
    }
    RpcExcept(1)
    {
         printf( "RPC Exception %d\n", RpcExceptionCode() );
    }
    RpcEndExcept

    RpcStringFree((RPC_WSTR*)&pszStringBinding);
    RpcBindingFree(&RpcService_Binding);
    return 0;
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER  midl_user_free(void __RPC_FAR *ptr)
{
    free(ptr);
}

