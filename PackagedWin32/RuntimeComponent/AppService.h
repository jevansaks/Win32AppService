#pragma once
#include "AppService.g.h"

#include "winrt/windows.foundation.collections.h"
#include "winrt/windows.ui.xaml.automation.provider.h"
#include "winrt/windows.applicationmodel.appservice.h"
#include "winrt/windows.applicationmodel.activation.h"

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::ApplicationModel::AppService;
    using namespace winrt::Windows::ApplicationModel::Activation;
}

namespace winrt::RuntimeComponent::implementation
{
    struct AppService : AppServiceT<AppService>
    {
        AppService();

        // IMap
        winrt::IInspectable Lookup(winrt::hstring key);
        uint32_t Size();
        bool HasKey(winrt::hstring key);
        void Remove(winrt::hstring key);
        void Clear();
        winrt::IMapView<winrt::hstring, winrt::IInspectable> GetView();
        bool Insert(winrt::hstring key, winrt::IInspectable value);

        winrt::IIterator<winrt::IKeyValuePair<winrt::hstring, winrt::IInspectable>> First() { throw winrt::hresult_not_implemented(); };

        void Invoke();

        
        //winrt::ValueSet ReceiveAppServiceMessage(winrt::ValueSet const& message);
        winrt::ValueSet UserInput();
        winrt::hstring Argument() { return {}; }

        winrt::ActivationKind Kind() { return {}; }
        winrt::ApplicationExecutionState PreviousExecutionState()  { return {}; }
        winrt::SplashScreen SplashScreen() { return nullptr; }

        winrt::ValueSet _valueSet;
    };
}
namespace winrt::RuntimeComponent::factory_implementation
{
    struct AppService : AppServiceT<AppService, implementation::AppService>
    {
    };
}
