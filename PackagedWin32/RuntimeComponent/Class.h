#pragma once

#include "Class.g.h"

#include <winrt\Windows.ApplicationModel.Background.h>
#include <winrt\Windows.ApplicationModel.AppService.h>
#include <winrt\Windows.Foundation.Collections.h>


namespace winrt
{
    using namespace winrt::Windows::ApplicationModel::Background;
    using namespace winrt::Windows::ApplicationModel::AppService;
    using namespace winrt::Windows::Foundation::Collections;
}


namespace winrt::RuntimeComponent::implementation
{
    struct Class : ClassT<Class, winrt::Windows::ApplicationModel::Background::IBackgroundTask>
    {
        Class();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Run(winrt::IBackgroundTaskInstance const& taskInstance);

        winrt::BackgroundTaskDeferral _backgroundTaskDeferral{nullptr};
        winrt::AppServiceConnection _appServiceConnection{nullptr};

        void OnRequestReceived(winrt::AppServiceConnection const& sender, winrt::AppServiceRequestReceivedEventArgs const& args);
    };
}

namespace winrt::RuntimeComponent::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
