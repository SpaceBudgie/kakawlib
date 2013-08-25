#ifndef KAKAW_DX10_RENDERER_INCLUDED
#define KAKAW_DX10_RENDERER_INCLUDED

#include <Kakaw/Renderer.hpp>
#include <Kakaw/Platform.hpp>

namespace Kakaw {

	
class DX10Renderer : public Renderer
{
	
	// Device and Stuff
	ID3D10Device			*mDevice;
	IDXGISwapChain			*mSwapChain;

	ID3D10Texture2D			*mBackBuffer;
	ID3D10Texture2D			*mDepthBuffer;
	ID3D10RenderTargetView	*mBackBufferRTV;
	ID3D10DepthStencilView	*mDepthBufferDSV;

	DXGI_FORMAT				mBackBufferFormat;
	DXGI_FORMAT				mDepthBufferFormat;

	TextureID				mBackBufferID;
	
public:

	explicit				DX10Renderer(const HWND hwnd, const unsigned int width, const unsigned int height, const bool isFullscreen, DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
							~DX10Renderer();


	// *** GENERIC STUFF & PLATFORM HOOKS *** //
	ID3D10Device *			getDevice() const;

	void					setDefaultBuffer() const override;
	TextureID				getBackBuffer() const override { return mBackBufferID; }
	TextureID				setDefaultBufferSize(const unsigned int width, const unsigned int height) override;
	void					setViewPort(const unsigned int width, const unsigned int height) const override;
	void					clear(const bool clearColor, const float *color) const override;

	void					startFrame() override;
	void					endFrame() override;

	// *** SHADERS *** //
	virtual void			setShaderData(const char *var, const void *data, const unsigned int size) const override;


	// *** TEXTURES *** //
	TextureID				addRenderTargetView(const unsigned int width, const unsigned int height, const unsigned int depth) override;


private:



};


} // namespace


#endif // include guard