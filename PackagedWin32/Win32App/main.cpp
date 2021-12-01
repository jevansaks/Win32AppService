#include "pch.h"
#include "windows.h"
#include "winrt\RuntimeComponent.h"

using namespace winrt;
using namespace Windows::Foundation;

int main()
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    winrt::RuntimeComponent::Class c;
    printf("Hello, %ls! %d\n", uri.AbsoluteUri().c_str(), c.MyProperty());
}
