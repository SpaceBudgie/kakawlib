#ifndef UTIL_NONCOPYABLE_INCLUDED
#define UTIL_NONCOPYABLE_INCLUDED

class NonCopyable
{
protected:

	NonCopyable ()	{}
	~NonCopyable () {}

private: 
	
	NonCopyable(const NonCopyable &);
	NonCopyable & operator=(const NonCopyable &);

}; // class

#endif // include guard