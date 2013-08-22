#ifndef UTIL_SAFE_DELETE_INCLUDED
#define UTIL_SAFE_DELETE_INCLUDED


// Safe Deletes

template<typename T>
void SafeDelete(T*& a)
{
	delete a;
	a = nullptr;
}


template<typename T>
void SafeArrayDelete(T*& a)
{
	delete a[];
	a = nullptr;
}



// For COM interfaces

#define SAFE_RELEASE(com)	\
	if(com != 0)			\
	{						\
		com->Release();		\
		com = 0;			\
	}						\

template<typename T>
void SafeRelease(T*& a)
{
	if(a) {
		a->Release();
		a = 0;
	}
}



#endif // include guard