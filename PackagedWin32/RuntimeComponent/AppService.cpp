#include "pch.h"
#include "AppService.h"
#include "AppService.g.cpp"

namespace winrt::RuntimeComponent::implementation
{
	AppService::AppService()
	{
		puts("Waiting for debugger...");
		for (int i = 0; i < 10 && !IsDebuggerPresent(); i++)
		{
			Sleep(5000);
		}
	}

	winrt::IInspectable AppService::Lookup(winrt::hstring key)
	{
		if (key == L"Values")
		{
			return _valueSet;
		}

		return nullptr;
	}

	uint32_t AppService::Size()
	{
		return 2; // Values, Invoke
	}

	bool AppService::HasKey(winrt::hstring key)
	{
		return true;
	}
	void AppService::Remove(winrt::hstring key)
	{
		throw winrt::hresult_not_implemented();
	}

	void AppService::Clear()
	{
		throw winrt::hresult_not_implemented();
	}

	winrt::IMapView<winrt::hstring, winrt::IInspectable> AppService::GetView()
	{
		throw winrt::hresult_not_implemented();
	}

	bool AppService::Insert(winrt::hstring key, winrt::IInspectable value)
	{
		if (key == L"Values")
		{
			_valueSet = value.as<winrt::ValueSet>();
		}
		if (key == L"Invoke")
		{
			Invoke();
		}
		return true;
	}



	winrt::ValueSet AppService::UserInput()
	{
		return _valueSet;
	}

	void AppService::Invoke()
	{
		auto command = unbox_value_or(_valueSet.Lookup(L"Command"), L"");
		auto id = unbox_value_or(_valueSet.Lookup(L"ID"), 0);

		_valueSet.Insert(L"Result", box_value(L"Return value!"));
	}
}
