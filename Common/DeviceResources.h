#pragma once

#include <winrt/windows.foundation.h>
#include <winrt/windows.ui.core.h>
#include <winrt/windows.graphics.h>
#include <winrt/windows.graphics.display.h>
//#include<winrt::windows::foundation.h>
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::Graphics::Display;

namespace DX
{
	// Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
	interface IDeviceNotify
	{
		virtual void OnDeviceLost() = 0;
		virtual void OnDeviceRestored() = 0;
	};
	// Number of frames that will be queued for rendering. This affects the latency/throughput tradeoff.
	static const UINT c_frameCount = 3;		// Use triple buffering.

	// Controls all the DirectX device resources.
	class DeviceResources
	{
	public:
		DeviceResources(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT);
		void SetSwapChainPanel(winrt::Windows::UI::Xaml::Controls::SwapChainPanel* panel, winrt::Windows::UI::Core::CoreWindow const& window);
		void SetWindow(winrt::Windows::UI::Core::CoreWindow const& window);
		void SetLogicalSize(winrt::Windows::Foundation::Size logicalSize);
		void SetCurrentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void SetDpi(float dpi);
		void ValidateDevice();
		void Present();
		void WaitForGpu();

		// These methods are used to notify the app that the device was lost or created.
		void RegisterDeviceNotify(IDeviceNotify* deviceNotify);

		// The size of the render target, in pixels.
		winrt::Windows::Foundation::Size	GetOutputSize() const				{ return m_outputSize; }

		// The size of the render target, in dips.
		winrt::Windows::Foundation::Size	GetLogicalSize() const				{ return m_logicalSize; }

		float						GetDpi() const						{ return m_effectiveDpi; }
		bool						IsDeviceRemoved() const				{ return m_deviceRemoved; }

		// D3D Accessors.
		ID3D12Device*               GetD3DDevice() const              { return m_D3dDevice.get(); }
		ID3D12Device*				getD3DDevice() const				{ return m_d3dDevice; }
		IDXGISwapChain3*			GetSwapChain() const				{ return m_SwapChain.get(); }
		IDXGISwapChain3*            getswapChain() const                { return m_swapChain; }
		ID3D12Resource*				GetRenderTarget() const			{ return m_RenderTargets[m_currentFrame].get(); }
		ID3D12Resource*             getRenderTarget() const             { return m_renderTargets[m_currentFrame]; }
		ID3D12Resource*				GetDepthStencil() const			{ return m_DepthStencil.get(); }
		ID3D12Resource*             getDepthStencil() const             { return m_depthStencil; }
		ID3D12CommandQueue*			GetCommandQueue() const			{ return m_CommandQueue.get(); }
		ID3D12CommandQueue*         getCommandQueue() const             { return m_commandQueue; }
		ID3D12CommandAllocator*		GetCommandAllocator() const		{ return m_CommandAllocators[m_currentFrame].get(); }
		ID3D12CommandAllocator*     getCommandAllocator() const         { return m_commandAllocators[m_currentFrame]; }
		DXGI_FORMAT					GetBackBufferFormat() const			{ return m_backBufferFormat; }
		DXGI_FORMAT					GetDepthBufferFormat() const		{ return m_depthBufferFormat; }
		D3D12_VIEWPORT				GetScreenViewport() const			{ return m_screenViewport; }
		DirectX::XMFLOAT4X4			GetOrientationTransform3D() const	{ return m_orientationTransform3D; }
		UINT						GetCurrentFrameIndex() const		{ return m_currentFrame; }

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_RtvHeap->GetCPUDescriptorHandleForHeapStart(), m_currentFrame, m_rtvDescriptorSize);
		}
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_DsvHeap->GetCPUDescriptorHandleForHeapStart());
		}

	private:
		void CreateDeviceIndependentResources();
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();
		void UpdateRenderTargetSize();
		void MoveToNextFrame();
		DXGI_MODE_ROTATION ComputeDisplayRotation();
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);

		UINT											m_currentFrame;

		// Direct3D objects.
		winrt::com_ptr<ID3D12Device>			m_D3dDevice;
		ID3D12Device*                           m_d3dDevice;
		winrt::com_ptr<IDXGIFactory4>			m_DxgiFactory;
		IDXGIFactory4*                          m_dxgiFactory;
		winrt::com_ptr<IDXGISwapChain3>			m_SwapChain;
		IDXGISwapChain3*                        m_swapChain;
		winrt::com_ptr<ID3D12Resource>			m_RenderTargets[c_frameCount];
		ID3D12Resource*                         m_renderTargets[c_frameCount];
		winrt::com_ptr<ID3D12Resource>			m_DepthStencil;
		ID3D12Resource*                         m_depthStencil;
		winrt::com_ptr<ID3D12DescriptorHeap>	m_RtvHeap;
		ID3D12DescriptorHeap*                   m_rtvHeap;
		winrt::com_ptr<ID3D12DescriptorHeap>	m_DsvHeap;
		ID3D12DescriptorHeap*                   m_dsvHeap;
		winrt::com_ptr<ID3D12CommandQueue>		m_CommandQueue;
		ID3D12CommandQueue*                     m_commandQueue;
		winrt::com_ptr<ID3D12CommandAllocator>	m_CommandAllocators[c_frameCount];
		ID3D12CommandAllocator*                 m_commandAllocators[c_frameCount];
		DXGI_FORMAT										m_backBufferFormat;
		DXGI_FORMAT										m_depthBufferFormat;
		D3D12_VIEWPORT									m_screenViewport;
		UINT											m_rtvDescriptorSize;
		bool											m_deviceRemoved;

		// CPU/GPU Synchronization.
		winrt::com_ptr<ID3D12Fence>				        m_Fence;
		ID3D12Fence*                                    m_fence;
		UINT64											m_fenceValues[c_frameCount];
		HANDLE											m_fenceEvent;

		// Cached reference to the Window.
		winrt::agile_ref<winrt::Windows::UI::Core::CoreWindow> m_window;

		// Cached reference to the XAML panel.
		winrt::Windows::UI::Xaml::Controls::SwapChainPanel* m_swapChainPanel;


		// Cached device properties.
		winrt::Windows::Foundation::Size						m_d3dRenderTargetSize;
		winrt::Windows::Foundation::Size						m_outputSize;
		winrt::Windows::Foundation::Size						m_logicalSize;
		winrt::Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		winrt::Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;
		float											m_dpi;

		// HDR Support
		DXGI_COLOR_SPACE_TYPE                               m_colorSpace;

		// DeviceResources options (see flags above)
		unsigned int                                        m_options;

		// This is the DPI that will be reported back to the app. It takes into account whether the app supports high resolution screens or not.
		float											m_effectiveDpi;

		// Transforms used for display orientation.
		DirectX::XMFLOAT4X4								m_orientationTransform3D;

		// The IDeviceNotify can be held directly as it owns the DeviceResources.
		IDeviceNotify* m_deviceNotify;
	};
}
