#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

// if you need native interop checks
//#include <windows.ui.xaml.media.dxinterop.h> 

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Hot3dxBlankApp2::implementation;

namespace winrt::Hot3dxBlankApp2::implementation
{
    
    MainPage::MainPage()
    {
        // create DeviceResources first
        m_deviceResources = std::make_shared<DeviceResources>();

        // create the SwapChainPanel instance (member) and hook Loaded
        m_swapChainPanel = swapChainPanel();
        m_swapChainPanel.Loaded({this, &MainPage::OnSwapChainPanelLoaded});

        // add the panel to the visual tree
        Content(m_swapChainPanel);

        // mark window invisible until ready
        m_windowVisible = false;
    }

    void MainPage::OnSwapChainPanelLoaded(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*args*/)
    {
        // safe to call interop / size dependent initialization now
        auto window = Window::Current();
        m_deviceResources->SetWindow(window.CoreWindow());

        // Give DeviceResources the panel (it should call SetSwapChain / ISwapChainPanelNative inside)
        m_deviceResources->SetSwapChainPanel(&m_swapChainPanel, window.CoreWindow());

        // create/render only after swapchain panel is attached
        m_main = std::make_unique<Hot3dxBlankApp2Main>(m_deviceResources);
        m_main->CreateRenderers(m_deviceResources);

        m_windowVisible = true;

        // Do one frame (or start your render loop)
        m_main->Render();
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
    // For all methods with unreferenced formal parameters, mark them as unreferenced to suppress C4100 warnings.

    void MainPage::Button_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        auto button = sender.as<Windows::UI::Xaml::Controls::Button>();
        button.Content(box_value(L"Clicked"));
        auto originalSource = args.OriginalSource();
        // You can add more logic here to handle the button click event
    }

    void MainPage::ScenarioControl_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& args)
    {
        auto list = sender.as<Windows::UI::Xaml::Controls::Button>();
        if (args.AddedItems().Size() > 0)
        {
            ScenarioControl().SelectedItem(args.AddedItems().GetAt(0));
            auto selectedItem = args.AddedItems().GetAt(0).as<Windows::UI::Xaml::Controls::ListBoxItem>();
            if (selectedItem)
            {
                auto scenarioName = winrt::unbox_value<hstring>(selectedItem.Content());
                if (scenarioName == L"Scenario1")
                {
                    // ScenarioFrame().Navigate(xaml_typename<Hot3dxWinRTUWPXaml::Scenario1>());
                }
                else if (scenarioName == L"Scenario2")
                {
                    //  ScenarioFrame().Navigate(xaml_typename<Hot3dxWinRTUWPXaml::Scenario2>());
                }
                // Add more scenarios as needed
            }
        }
    }

    void MainPage::Footer_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
		auto button = sender.as<Windows::UI::Xaml::Controls::Button>();
		button.Content(box_value(L"Clicked"));
		auto originalSource = args.OriginalSource();

        //auto uri = Windows::Foundation::Uri(L"
    }

    void MainPage::Footer_Click2(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args)
    {
        auto button = sender.as<Windows::UI::Xaml::Controls::Button>();
        button.Content(box_value(L"Clicked"));
        auto originalSource = args.OriginalSource();

        //auto uri = Windows::Foundation::Uri(L"
    }


    void MainPage::OnPointerPressed(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerMoved(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerReleased(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerWheelChanged(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerEntered(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerExited(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
        if (e) {}
        //}
    }
    void MainPage::OnPointerCaptureLost(winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const e)
    {
        //if (sender) { 
            if (e) {}
        //}
    }
    void MainPage::OnKeyDown(Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        if (args) { }
    }
    void MainPage::OnKeyUp(Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        if (args) {}
    }
}
