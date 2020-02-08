#include "Direct3DManager.h"
#include "D3DHelper.hpp"
#include "GameScenes/SceneManager.h"

#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"

Direct3DManager& Direct3DManager::Instance() {
    static Direct3DManager d3dmManager;
    return d3dmManager;
}

bool Direct3DManager::_InitDepthStencilView(UINT uWidth, UINT uHeight, bool bEnable4xMsaa) {
    D3D11_TEXTURE2D_DESC dtdDepthStencilDesc;
    dtdDepthStencilDesc.Width = uWidth;
    dtdDepthStencilDesc.Height = uHeight;
    dtdDepthStencilDesc.MipLevels = 1;
    dtdDepthStencilDesc.ArraySize = 1;
    dtdDepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    UINT uM4xMsaaQuality;

    auto hr = m_pDevice->CheckMultisampleQualityLevels(
        DXGI_FORMAT_R8G8B8A8_UNORM,
        4,
        &uM4xMsaaQuality
    );

    if (uM4xMsaaQuality <= 0) {
        return false;
    }

    if (bEnable4xMsaa) {
        dtdDepthStencilDesc.SampleDesc.Count = 4;
        dtdDepthStencilDesc.SampleDesc.Quality = uM4xMsaaQuality - 1;
    }
    else {
        dtdDepthStencilDesc.SampleDesc.Count = 1;
        dtdDepthStencilDesc.SampleDesc.Quality = 0;
    }

    dtdDepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    dtdDepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    dtdDepthStencilDesc.CPUAccessFlags = 0;
    dtdDepthStencilDesc.MiscFlags = 0;

    hr = m_pDevice->CreateTexture2D(
        &dtdDepthStencilDesc,
        nullptr,
        &m_pDepthStencilBuffer
    );
    if (FAILED(hr)) {
        return false;
    }

    hr = m_pDevice->CreateDepthStencilView(
        m_pDepthStencilBuffer,
        0,
        &m_pDepthStencilView
    );

    return true;
}

bool Direct3DManager::_InitRenderTargetView() {
    ID3D11Texture2D* pBackBuffer = nullptr;

    auto hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr)) {
        D3DHelper::SafeRelease(pBackBuffer);
        return false;
    }

    hr = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    if (FAILED(hr)) {
        D3DHelper::SafeRelease(pBackBuffer);
        return false;
    }

    D3DHelper::SafeRelease(pBackBuffer);
    return true;
}

bool Direct3DManager::_InitSwapChain(UINT uWidth, UINT uHeight, bool bEnable4xMsaa) {
    UINT uM4xMsaaQuality;

    auto hr = m_pDevice->CheckMultisampleQualityLevels(
        DXGI_FORMAT_R8G8B8A8_UNORM,
        4,
        &uM4xMsaaQuality
    );

    if (uM4xMsaaQuality <= 0) {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC dscdDesc;
    dscdDesc.BufferDesc.Width = uWidth;
    dscdDesc.BufferDesc.Height = uHeight;
    dscdDesc.BufferDesc.RefreshRate.Numerator = 60;
    dscdDesc.BufferDesc.RefreshRate.Denominator = 1;
    dscdDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    dscdDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    dscdDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    if (bEnable4xMsaa) {
        dscdDesc.SampleDesc.Count = 4;
        dscdDesc.SampleDesc.Quality = uM4xMsaaQuality - 1;
    } else {
        dscdDesc.SampleDesc.Count = 1;
        dscdDesc.SampleDesc.Quality = 0;
    }
    
    dscdDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dscdDesc.BufferCount = 1;
    dscdDesc.OutputWindow = m_hWND;
    dscdDesc.Windowed = true;
    dscdDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    dscdDesc.Flags = 0;

    IDXGIDevice* pDxgiDevice = nullptr;
    IDXGIAdapter* pDxgiAdapter = nullptr;
    IDXGIFactory* pDxgiFactory = nullptr;

    hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDxgiDevice));
    if (FAILED(hr)) {
        goto faild_exit;
    }

    hr = pDxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDxgiAdapter));
    if (FAILED(hr)) {
        goto faild_exit;
    }

    hr = pDxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDxgiFactory));
    if (FAILED(hr)) {
        goto faild_exit;
    }

    hr = pDxgiFactory->CreateSwapChain(
        m_pDevice,
        &dscdDesc,
        &m_pSwapChain
    );
    if (FAILED(hr)) {
        goto faild_exit;
    }

    D3DHelper::SafeRelease(pDxgiDevice);
    D3DHelper::SafeRelease(pDxgiAdapter);
    D3DHelper::SafeRelease(pDxgiFactory);
    return true;

faild_exit:
    D3DHelper::SafeRelease(pDxgiDevice);
    D3DHelper::SafeRelease(pDxgiAdapter);
    D3DHelper::SafeRelease(pDxgiFactory);
    return false;
}

LRESULT Direct3DManager::_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
        case WM_CREATE: {
            int nScrWidth, nScrHeight;
			RECT rtRect;

			nScrWidth = GetSystemMetrics(SM_CXSCREEN);
			nScrHeight = GetSystemMetrics(SM_CYSCREEN);

			GetWindowRect(hwnd, &rtRect);

			rtRect.left = (nScrWidth-rtRect.right)/2;
			rtRect.top = (nScrHeight-rtRect.bottom)/2;

			SetWindowPos(hwnd, HWND_TOP, rtRect.left, rtRect.top, rtRect.right, rtRect.bottom, SWP_SHOWWINDOW);
        }
        break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
}

bool Direct3DManager::_InitWindow(HINSTANCE hInstance, UINT uWidth, UINT uHeight) {
    m_uWidth = uWidth;
    m_uHeight = uHeight;

    WNDCLASSEX wndClass = { 0 };
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = _WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = "IrisAppWindow";

    if (!RegisterClassEx(&wndClass)) {
        return false;
    }

    RECT rcArea = { 0, 0, static_cast<long>(uWidth), static_cast<long>(uHeight) };
    AdjustWindowRect(&rcArea, WS_OVERLAPPEDWINDOW, false);

    const HWND hHwnd = CreateWindowW(L"IrisAppWindow",
        L"DirectX 11 Demo",
        WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        0,
        0,
        rcArea.right - rcArea.left,
        rcArea.bottom - rcArea.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hHwnd) {
        return false;
    }

    m_hWND = hHwnd;

    return true;
}

bool Direct3DManager::Initialize(HINSTANCE hInstance,UINT uWidth, UINT uHeight, bool bEnable4xMsaa) {
    if (!_InitWindow(hInstance, uWidth, uHeight)) {
        goto failed_exit;
    }
    m_hInstance = hInstance;

    UINT uCreateDeviceFlags = 0;

#ifndef NDEBUG
    uCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

    D3D_FEATURE_LEVEL dflLevel;

    auto hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        uCreateDeviceFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &m_pDevice,
        &dflLevel,
        &m_pDeviceContext
    );
    
    if (FAILED(hr)) {
        goto failed_exit;
    }

    if (dflLevel != D3D_FEATURE_LEVEL_11_0) {
        goto failed_exit;
    }

    if (!_InitSwapChain(uWidth, uHeight, bEnable4xMsaa)) {
        goto failed_exit;
    }

    if (!_InitRenderTargetView()) {
        goto failed_exit;
    }

    if (!_InitDepthStencilView(uWidth, uHeight, bEnable4xMsaa)) {
        goto failed_exit;
    }

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

    D3D11_VIEWPORT vpViewport;
    vpViewport.TopLeftX = 0;
    vpViewport.TopLeftY = 0;
    vpViewport.Width = static_cast<float>(uWidth);
    vpViewport.Height = static_cast<float>(uHeight);
    vpViewport.MinDepth = 0.0f;
    vpViewport.MaxDepth = 1.0f;

    m_pDeviceContext->RSSetViewports(1, &vpViewport);

    m_eState = ApplicationState::Running;

    // RenderCommandQueue
    RenderCommandQueueManager::Instance().Initialize();

    return true;

failed_exit:
    m_eState = ApplicationState::Quite;
    return false;
}

void Direct3DManager::_Render() {
    const DirectX::XMVECTORF32 f4Color = { 0.0f, 0.0f, 1.0f, 1.0f};

    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&f4Color));
    m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    SceneManager::Instance().Render();
    RenderCommandQueueManager::Instance().Render();

    m_pSwapChain->Present(1, 0);
}

void Direct3DManager::StartWindow(int nShowCmd) {
    ShowWindow(m_hWND, nShowCmd);
}

void Direct3DManager::Update() {
    MSG msg = { 0 };
    if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);

        if (msg.message == WM_QUIT) {
            m_eState = ApplicationState::Quite;
            return;
        }
    }
    else {
        _Render();
    }
}

bool Direct3DManager::CreateBuffer(const D3D11_BUFFER_DESC& dscBufferDesc, ID3D11Buffer*& pBuffer) {
    auto result = m_pDevice->CreateBuffer(&dscBufferDesc, nullptr, &pBuffer);

    if (FAILED(result)) {
        pBuffer = nullptr;
        return false;
    }
    return true;
}

bool Direct3DManager::CreateBuffer(
    const D3D11_BUFFER_DESC& dscBufferDesc,
    const D3D11_SUBRESOURCE_DATA& ssInitData,
    ID3D11Buffer*& pBuffer) {
    auto result = m_pDevice->CreateBuffer(&dscBufferDesc, &ssInitData, &pBuffer);

    if (FAILED(result)) {
        pBuffer = nullptr;
        return false;
    }
    return true;
}

void Direct3DManager::SetPixelShader(std::shared_ptr<PixelShaderBase> pPixelShader) {
    m_pPixelShader = pPixelShader;
}

void Direct3DManager::SetVertexShader(std::shared_ptr<VertexShaderBase> pVertexShader) {
    m_pVertexShader = pVertexShader;
}

bool Direct3DManager::CreateInputLayout(
    const D3D11_INPUT_ELEMENT_DESC* arrInputLayoutDescArr,
    UINT uDescArrSize,
    ID3DBlob* pBuffer,
    ID3D11InputLayout*& pInputLayout){

    auto result = m_pDevice->CreateInputLayout(arrInputLayoutDescArr,
        uDescArrSize,
        pBuffer->GetBufferPointer(),
        pBuffer->GetBufferSize(),
        &pInputLayout);
    
    if (FAILED(result)) {
        pInputLayout = nullptr;
        return false;
    }

    return true;
}

bool Direct3DManager::DrawObjectWithShader(
    ID3D11Buffer* pVertexBuffer,
    ID3D11Buffer* pIndexedBuffer,
    UINT nStride,
    UINT nIndexCount) {

    m_pDeviceContext->VSSetShader(m_pVertexShader->GetVertexShader(), nullptr, 0);
    m_pDeviceContext->PSSetShader(m_pPixelShader->GetPixelShader(), nullptr, 0);

    UINT nOffset = 0;
    m_pDeviceContext->IASetInputLayout(m_pVertexShader->GetInputLayout());
    m_pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &nStride, &nOffset);
    m_pDeviceContext->IASetIndexBuffer(pIndexedBuffer, DXGI_FORMAT_R32_UINT, 0);
    m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // fCallBack(m_pVertexShader, m_pPixelShader);

    m_pDeviceContext->DrawIndexed(nIndexCount, 0, 0);

    return true;
}

bool Direct3DManager::CreatePixelShader(ID3DBlob* pBlob, ID3D11PixelShader*& pPixelShader) {
    auto result = m_pDevice->CreatePixelShader(
        pBlob->GetBufferPointer(), 
        pBlob->GetBufferSize(),
        nullptr,
        &pPixelShader);

    if (FAILED(result)) {
        return false;
    }
    return true;
}

bool Direct3DManager::CreateVertexShader(ID3DBlob* pBlob, ID3D11VertexShader*& pVertexShader) {
    auto result = m_pDevice->CreateVertexShader(
        pBlob->GetBufferPointer(), 
        pBlob->GetBufferSize(),
        nullptr,
        &pVertexShader);

    if (FAILED(result)) {
        return false;
    }
    return true;
}
