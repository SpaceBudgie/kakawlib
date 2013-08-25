#ifndef KAKAW_PLATFORM_INCLUDED
#define KAKAW_PLATFORM_INCLUDED


#define KAKAW_ON_WINDOWS
#define KADAW_IS_OPENGL

// DX10
// Linking the DX10 stuff
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#ifndef NDEBUG
#pragma comment(lib, "d3dx10d.lib")
#else
#pragma comment(lib, "d3dx10.lib")
#endif

#include <d3d10.h>
#include <d3dx10.h>
#include <dxgi.h>
#include <dxerr.h>

#include <Windows.h>
#include <winerror.h>


#endif // include guard
