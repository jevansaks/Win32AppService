#include "pch.h"
#include "AppServiceProxy.h"
#include "AppServiceProxy.g.cpp"

#include "winrt/RuntimeComponent.h"
#include "winrt/windows.ui.xaml.automation.provider.h"
#include "winrt/windows.applicationmodel.appservice.h"
#include "winrt/windows.applicationmodel.activation.h"

#include <windows.h>

#include <wil/com.h>

namespace winrt::RuntimeComponent::implementation
{
    AppServiceProxy::AppServiceProxy()
    {
    }

    int32_t AppServiceProxy::MyProperty()
    {
        return 42;
    }

    void AppServiceProxy::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void AppServiceProxy::Run(winrt::IBackgroundTaskInstance const& taskInstance)
    {
        printf("Hello! %08x\n", taskInstance.InstanceId().Data1);

        // Get a deferral so that the service isn't terminated.
        _backgroundTaskDeferral = taskInstance.GetDeferral();

        // Associate a cancellation handler with the background task.
        taskInstance.Canceled([strongThis = get_strong()](auto&&...) {
            strongThis->_backgroundTaskDeferral.Complete();
        });

        // Retrieve the app service connection and set up a listener for incoming app service requests.
        auto details = taskInstance.TriggerDetails().try_as<winrt::AppServiceTriggerDetails>();
        _appServiceConnection = details.AppServiceConnection();
        _appServiceConnection.RequestReceived([strongThis = get_strong()](auto&& connection, auto&& args){
            strongThis->OnRequestReceived(connection, args);
            });

    }

    struct __declspec(uuid("973166A5-ABC2-4F21-9DC8-5D80AF677DEC")) AppServiceComServer
    {

    };

    void AppServiceProxy::OnRequestReceived(winrt::AppServiceConnection const& /*sender*/, winrt::AppServiceRequestReceivedEventArgs const& args)
    {
        auto messageDeferral = args.GetDeferral();

        auto message = args.Request().Message();

        // TODO: Send to OOP AppService
        //auto appServiceFactory = winrt::get_activation_factory<winrt::RuntimeComponent::AppService>();
        //auto appService = appServiceFactory.ActivateInstance<winrt::RuntimeComponent::AppService>();
        
        auto server = winrt::Windows::Foundation::IUnknown{ wil::CoCreateInstance<::IUnknown>(__uuidof(AppServiceComServer), CLSCTX_LOCAL_SERVER).detach(), winrt::take_ownership_from_abi };

        //auto serverInvoke = server.as<winrt::Windows::UI::Xaml::Automation::Provider::IInvokeProvider>();
        //auto serverValues = server.as<winrt::Windows::ApplicationModel::Activation::IToastNotificationActivatedEventArgs>();

        //auto valueSet = serverValues.UserInput();
        //for (auto pair : message)
        //{
        //    valueSet.Insert(pair.Key(), pair.Value());
        //}

        auto serverMap = server.as<winrt::IMap<winrt::hstring, winrt::Windows::Foundation::IInspectable>>();

        serverMap.Insert(L"Values", message);
        serverMap.Insert(L"Invoke", winrt::box_value(1));

        auto resultValues = serverMap.Lookup(L"Values").as<winrt::ValueSet>();
        auto result = unbox_value<winrt::hstring>(resultValues.Lookup(L"Result"));
        wprintf(L"Result = %s\n", result.c_str());

        args.Request().SendResponseAsync(resultValues);

        return messageDeferral.Complete();
    }
}
