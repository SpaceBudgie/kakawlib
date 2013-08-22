#ifndef SYS_PLATFORM_INCLUDED
#define SYS_PLATFORM_INCLUDED


// WINDOWS //

#ifdef WIN32// || _WIN32)

// Windows stuff.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0501 // XP
#endif

#ifndef NOMENUS
#define NOMENUS
#endif

#ifndef NOSCROLL  // Scrolling stuff.
#define NOSCROLL
#endif

#ifndef NOHELP    // Help engine interface.
#define NOHELP
#endif

#ifndef NOMCX   // Modem config.
#define NOMCX
#endif

#ifndef NOMINMAX  // Definatly want this one.
#define NOMINMAX  // Uses macros for min and max, conflicts with using namespace std people.
#endif

#include <Windows.h>


#ifndef SYS_IS_WINDOWS
#define SYS_IS_WINDOWS
#endif







#endif // #ifdef WIN32 || _WIN32



#endif // include guard