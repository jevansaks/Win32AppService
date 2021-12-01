#include "pch.h"
#include "Class.h"
#include "Class.g.cpp"

namespace winrt::RuntimeComponent::implementation
{
    Class::Class()
    {
    }

    int32_t Class::MyProperty()
    {
        return 42;
    }

    void Class::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Class::Run(winrt::IBackgroundTaskInstance const& taskInstance)
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

    void Class::OnRequestReceived(winrt::AppServiceConnection const& /*sender*/, winrt::AppServiceRequestReceivedEventArgs const& args)
    {
        auto messageDeferral = args.GetDeferral();

        auto message = args.Request().Message();
        auto returnData = winrt::ValueSet();

        auto command = unbox_value_or(message.Lookup(L"Command"), L"");
        auto id = unbox_value_or(message.Lookup(L"ID"), 0);

        returnData.Insert(L"Result", box_value(L"Return value!"));

        args.Request().SendResponseAsync(returnData);

        messageDeferral.Complete();
    }
}
