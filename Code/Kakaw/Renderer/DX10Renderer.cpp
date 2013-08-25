// DX10Renderer.cpp

#include <Kakaw/Renderer/DX10Renderer.hpp>
#include <Kakaw/Utils/SafeDelete.hpp>
#include <stdexcept>

namespace Kakaw {



struct Texture
{
	ID3D10Resource				*resource;
	ID3D10ShaderResourceView	*srv;
	ID3D10RenderTargetView		*rtv;
	ID3D10DepthStencilView		*dsv;
}; // texture;





DX10Renderer::DX10Renderer(const HWND hwnd, const unsigned int width, const unsigned int height, const bool isFullscreen, DXGI_FORMAT backBufferFormat, DXGI_FORMAT depthBufferFormat)
	: Renderer()
	, mDevice(nullptr)
	, mSwapChain(nullptr)
	, mBackBufferFormat(backBufferFormat)
	, mDepthBufferFormat(depthBufferFormat)
	, mBackBufferID(NO_TEXTURE)
{
	// Check HWND
	if(!hwnd) {
		throw std::runtime_error("DX10Renderer: HWND is null!");
	}


	// Setup Display
	IDXGIFactory *dxgiFactory;
	if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **) &dxgiFactory))) {
		throw std::runtime_error("DX10Renderer: Failed to create DXGI Factory!");
	}

	IDXGIAdapter *dxgiAdapter;
	if (dxgiFactory->EnumAdapters(0, &dxgiAdapter) == DXGI_ERROR_NOT_FOUND){
		throw std::runtime_error("DX10Renderer: Failed to find an adapter!");
	}

	IDXGIOutput *dxgiOutput;
	if (dxgiAdapter->EnumOutputs(0, &dxgiOutput) == DXGI_ERROR_NOT_FOUND){
		throw std::runtime_error("DX10Renderer: Failed to find an output!");
	}



	DWORD deviceFlags = D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_DEBUG;

	if (FAILED(D3D10CreateDevice(dxgiAdapter, D3D10_DRIVER_TYPE_HARDWARE, 0, deviceFlags, D3D10_SDK_VERSION, &mDevice))){
		throw std::runtime_error("DX10Renderer: Can't create D3D10Device!");
	}



	// Create swap chain
	{
		DXGI_OUTPUT_DESC oDesc;
		dxgiOutput->GetDesc(&oDesc);

		DXGI_RATIONAL refresh = {60, 1};

		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(swapDesc));

		swapDesc.BufferDesc.Width		= width;
		swapDesc.BufferDesc.Height		= height;
		swapDesc.BufferDesc.Format		= mBackBufferFormat;
		swapDesc.BufferDesc.RefreshRate = refresh;
		swapDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT |  DXGI_USAGE_SHADER_INPUT;
		swapDesc.BufferCount			= 1;
		swapDesc.OutputWindow			= hwnd;
		swapDesc.Windowed				= (BOOL)(!isFullscreen);
		swapDesc.SwapEffect				= DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Flags					= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapDesc.SampleDesc.Count		= 1;
		swapDesc.SampleDesc.Quality		= 0;

			
		if (FAILED(dxgiFactory->CreateSwapChain(mDevice, &swapDesc, &mSwapChain))){
			throw std::runtime_error("DX10Renderer: Can't create swapchain!");
		}
	}

	dxgiOutput->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	/*
	if(!setResolution(width, height)) {
		throw std::runtime_error("Failed creating buffers!");
	}
	*/

	setDefaultBufferSize(width, height);
}


DX10Renderer::~DX10Renderer()
{
	// Loop through textures etc and release.
}



// *** GENERIC STUFF & PLATFORM HOOKS *** //
ID3D10Device * DX10Renderer::getDevice() const { return mDevice; }


void DX10Renderer::setDefaultBuffer() const {
	mDevice->OMSetRenderTargets(1, &mBackBufferRTV, mDepthBufferDSV);
}

//TextureID DX10Renderer::getBackBuffer() const { return mBackBufferID; }

TextureID DX10Renderer::setDefaultBufferSize(const unsigned int width, const unsigned int height)
{
	// Delete buffers first!!!
	if(mBackBufferID != NO_TEXTURE)
	{
		mDevice->OMSetRenderTargets(0, nullptr, nullptr);
		
		SafeRelease(mBackBuffer);
		SafeRelease(mDepthBuffer);
		SafeRelease(mBackBufferRTV);
		SafeRelease(mDepthBufferDSV);
	}
	else
	{
		Texture *tex = new Texture();
		ZeroMemory(tex, sizeof(tex));

		mTextures.push_back(tex);
		mBackBufferID = mTextures.size();
	}


	mSwapChain->ResizeBuffers(1, width, height, mBackBufferFormat, 0);


	// Create Buffers
	if(FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID *) &mBackBuffer))) {
		std::runtime_error("DX10Renderer: Failed to Get Buffer from Swap Chain!");
	}

	if(FAILED(mDevice->CreateRenderTargetView(mBackBuffer, 0, &mBackBufferRTV))) {
		std::runtime_error("DX10Renderer: Failed to Create RTV for BackBuffer!");
	}


	// Depth Buffer.
	{
		D3D10_TEXTURE2D_DESC depthDesc;
		ZeroMemory(&depthDesc, sizeof(depthDesc));

		depthDesc.Width					= width;
		depthDesc.Height				= height;
		depthDesc.MipLevels				= 1;
		depthDesc.ArraySize				= 1;
		depthDesc.Format				= mDepthBufferFormat;
		depthDesc.SampleDesc.Count		= 1;
		depthDesc.SampleDesc.Quality	= 0;
		depthDesc.Usage					= D3D10_USAGE_DEFAULT;
		depthDesc.BindFlags				= D3D10_BIND_DEPTH_STENCIL;
		depthDesc.CPUAccessFlags		= 0;
		depthDesc.MiscFlags				= 0;

		if(FAILED(mDevice->CreateTexture2D(&depthDesc, 0, &mDepthBuffer))) {
			std::runtime_error("DX10Renderer: Failed to create depth buffer.");
		}

		D3D10_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(dsvDesc));

		dsvDesc.Format				= depthDesc.Format;
		dsvDesc.ViewDimension		= D3D10_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice	= 0;

		if(FAILED(mDevice->CreateDepthStencilView(mDepthBuffer, &dsvDesc, &mDepthBufferDSV))) {
			std::runtime_error("DX10Renderer: Failed to create depth stencil view buffer.");
		}
	}


	// Set defaults.
	setDefaultBuffer();
	setViewPort(width, height);
	

	return 0;
}


void DX10Renderer::startFrame() {}
void DX10Renderer::endFrame()	{ mSwapChain->Present(0, 0); }

void DX10Renderer::setViewPort(const unsigned int width, const unsigned int height) const
{
	D3D10_VIEWPORT viewport;
	viewport.Width		= width;
	viewport.Height		= height;
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;
	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;

	mDevice->RSSetViewports(1, &viewport);
}


void DX10Renderer::clear(const bool clearColor, const float *color) const
{
	if(clearColor) {
		mDevice->ClearRenderTargetView(mBackBufferRTV, color);
	}
}


// *** SHADERS *** //
void DX10Renderer::setShaderData(const char *var, const void *data, const unsigned int size) const {}


// *** TEXTURES *** //
TextureID DX10Renderer::addRenderTargetView(const unsigned int width, const unsigned int height, const unsigned int depth)
{
	Texture tex;
	ZeroMemory(&tex, sizeof(tex));

	return 0;
}



} // namespace