#include "pch.h"
#include "windows.h"
#include "winrt\RuntimeComponent.h"

#include <wil\com.h>

#include <winrt\windows.applicationmodel.core.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Core;

struct Server : implements<Server, IGetActivationFactory, ::IClassFactory>
{
    auto GetActivationFactory(hstring const& classId)
    {
        winrt::Windows::Foundation::IActivationFactory factory;
        //if (classId == L"RuntimeComponent.AppService")
        //{
        //    int32_t (*getActivationFactory) (void* classId, void** factory);
        //    HMODULE hmod = LoadLibraryW(L"RuntimeComponent.dll");
        //    getActivationFactory = reinterpret_cast<decltype(getActivationFactory)>(GetProcAddress(hmod, "DllGetActivationFactory"));
        //    getActivationFactory(*(void**)(&classId), winrt::put_abi(factory));
        //}

        if (!factory)
        {
            throw hresult_class_not_available(classId);
        }

        return factory;
    }

    HRESULT STDMETHODCALLTYPE CreateInstance(
        _In_opt_ ::IUnknown* pUnkOuter,
        _In_  REFIID riid,
        _COM_Outptr_  void** ppvObject) override
    {
        try
        {
            auto result = winrt::RuntimeComponent::AppService();
            *ppvObject = winrt::detach_abi(result);
            return S_OK;
        }
        catch (...) { return to_hresult(); }
    }

    HRESULT STDMETHODCALLTYPE LockServer(
        /* [in] */ BOOL fLock) override
    {
        throw winrt::hresult_not_implemented();
    }

};

struct __declspec(uuid("973166A5-ABC2-4F21-9DC8-5D80AF677DEC")) AppServiceComServer
{

};

int wmain(int argc, wchar_t** argv)
{
    if (argc >= 1)
    {
        try
        {
            puts("Server running");
            init_apartment();
            auto server = make<Server>();
            //CoreApplication::RunWithActivationFactories(make<Server>());

            //auto appService = winrt::RuntimeComponent::AppService();

            DWORD dwRegister;
            if (FAILED(CoRegisterClassObject(__uuidof(AppServiceComServer), (LPUNKNOWN)winrt::get_abi(server), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwRegister)))
            {
                puts("Server registration failed");
            }

            MSG msg;
            while (GetMessage(&msg, NULL, NULL, NULL))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            puts("Server stopped");
        }
        catch (hresult_error const& e)
        {
            printf("Server error: %ls\n", e.message().c_str());
        }
    }
    
    // Keep resident just for debugging.
    ::Sleep(60 * 60 * 10);
}
