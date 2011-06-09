#pragma once

#include "Ten18/Interop/HostControl.h"
#include "Ten18/Interop/HostAssemblyManager.h"
#include "Ten18/Interop/HostAssemblyStore.h"
#include "Ten18/Interop/HostMemoryManager.h"
#include "Ten18/Interop/HostGCManager.h"

namespace Ten18 { namespace Interop {

    class Host
    {
    public:
        
        Host();
        ~Host();

        void Tick();
        
        __declspec(noreturn) void Exit(int exitCode);

    private:
        
        Host(const Host&);
        Host& operator = (const Host&);

        friend class HostControl;
        friend class HostAssemblyManager;
        friend class HostAssemblyStore;
        friend class HostMemoryManager;  

        HostControl         mControl;
        HostAssemblyManager mAssemblyManager;
        HostAssemblyStore   mAssemblyStore;
        HostMemoryManager   mMemoryManager;
        HostGCManager       mHostGCManager;

        // Because a process that hosts the CLR can't actually stop, unload, or otherwise deinitialize
        // the CLR (or its default AppDomain) once loaded, we just let it die with the process (which appears
        // to by as designed by the CLR hosting API). Henceforth, we're not going to bother releasing any of
        // these pointers. And that's why we don't use reference counted smart pointers, and just resort to
        // plain old fashioned raw pointers.
        IAppDomainManagerEx*    mAppDomainManagerEx;
        ICLRMetaHost*           mMetaHost;
        ICLRRuntimeInfo*        mRuntimeInfo;
        ICLRControl*            mClrControl;
        ICLRGCManager*          mGCManager;
        ICLRRuntimeHost*        mRuntimeHost;
    };
}}