#pragma once

using namespace Windows::UI::Core;   // CoreWindow, KeyEventArgs
using namespace Windows::Foundation; // TypedEventArgs
using namespace Windows::System;     // Virtual Key
using namespace Windows::UI::Xaml;   // RoutedEventArgs
using namespace Windows::UI::Xaml::Controls;  // Page

ref class MyPage sealed : Page
{
private:
	TextBlock^ textBlock;

public:
	MyPage();
	void OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args);
	void OnButtonClick(Object^ sender, RoutedEventArgs^ args);
};
