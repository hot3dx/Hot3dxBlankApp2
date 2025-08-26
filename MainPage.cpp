#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::Hot3dxBlankApp2::implementation
{
    // Example: Create a SwapChainPanel object in code
    SwapChainPanel m_swapChainPanel{ nullptr };

    MainPage::MainPage()
    {
        // If you want to create it in code (not XAML)
        m_swapChainPanel = SwapChainPanel();
        // Optionally, set properties
        m_swapChainPanel.Width(1600);
        m_swapChainPanel.Height(900);
        m_swapChainPanel.Visibility(Visibility::Visible);

        // If you want to add it to the visual tree, for example:
        // Content(m_swapChainPanel);
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
    void MainPage::Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        auto button = sender.as<Windows::UI::Xaml::Controls::Button>();
        button.Content(box_value(L"Clicked"));
        auto originalSource = args.OriginalSource();
		// You can add more logic here to handle the button click event
    }
    void MainPage::ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
    {
		// Handle selection change logic here

    }
    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        
            //auto uri = Windows::Foundation::Uri(L"
        
    }
    void MainPage::Footer_Click2(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {

    }
}
