// Renderer.cpp


#include <Kakaw/Renderer.hpp>
#include <limits.h>


namespace Kakaw {


Renderer::Renderer()
{
	mTextures.reserve(UCHAR_MAX);
}


Renderer::~Renderer()
{
}


// **** SHADERS **** //
void Renderer::setShader1i(const char *var, const int *data) {
	setShaderData(var, data, sizeof(int));
}

void Renderer::setShader1f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float));
}

void Renderer::setShader2f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float) * 2);
}

void Renderer::setShader3f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float) * 3);
}

void Renderer::setShader4f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float) * 4);
}

void Renderer::setShader33f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float) * 9);
}

void Renderer::setShader44f(const char* var, const float* data) {
	setShaderData(var, data, sizeof(float) * 16);
}




} // namespace