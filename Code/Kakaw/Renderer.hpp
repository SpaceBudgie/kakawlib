#ifndef KAKAW_RENDERER_INCLUDED
#define KAKAW_RENDERER_INCLUDED

#include <cstdint>
#include <vector>

namespace Kakaw {

typedef uint8_t ShaderID;
typedef uint8_t VertexLayoutID;
typedef uint8_t TextureID;
typedef uint8_t VertexBufferID;
typedef uint8_t IndexBufferID;


struct Shader;
struct VertexLayout;
struct Texture;
struct VertexBuffer;
struct IndexBuffer;


#define NO_SHADER 0
#define NO_VERTEX_LAYOUT 0
#define NO_TEXTURE 0
#define NO_VERTEX_BUFFER 0
#define NO_INDEX_BUFFER 0


class Renderer
{
protected:

	std::vector<Texture*>			mTextures;

public:

	explicit 						Renderer();
	virtual							~Renderer();


	// *** GENERIC STUFF & PLATFORM HOOKS *** //	
	virtual void					setDefaultBuffer() const = 0;
	virtual TextureID				setDefaultBufferSize(const unsigned int width, const unsigned int height) = 0;
	virtual TextureID				getBackBuffer() const = 0;
	virtual void					setViewPort(const unsigned int width, const unsigned int height) const = 0;

	virtual void 					startFrame() {}
	virtual void 					endFrame()	{}


	// *** SHADERS *** //
	/*
	virtual ShaderID				addShader(const char* filename);
	virtual void					setShader(const ShaderID id);

	virtual VertexID				addVertex();
	virtual void					setVertex(const VertexID id);
	*/

	void							setShader1i(const char *var, const int* data);
	void							setShader1f(const char* var, const float* data);
	void							setShader2f(const char* var, const float* data);
	void							setShader3f(const char* var, const float* data);
	void							setShader4f(const char* var, const float* data);
	void							setShader33f(const char* var, const float* data);
	void							setShader44f(const char* var, const float* data);
	
	virtual void					setShaderData(const char *var, const void *data, const unsigned int size) const = 0;

	
	virtual void					clear(const bool clearColor, const float *color) const = 0;

	// *** TEXTURES *** //

	virtual TextureID				addRenderTargetView(const unsigned int width, const unsigned int height, const unsigned int depth) = 0;

		/*
	virtual TextureID				addTexture(const char* filename);
	virtual void					removeTexture(const TextureID id);
	

	*/


}; // class

}  // namespace


#endif // include guard 