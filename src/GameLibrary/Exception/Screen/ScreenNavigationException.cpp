
#include "ScreenNavigationException.h"

namespace GameLibrary
{
	ScreenNavigationException::ScreenNavigationException(const ScreenNavigationException&exception) : Exception(exception)
	{
		//
	}

	ScreenNavigationException::ScreenNavigationException(const String&message) : Exception(message)
	{
		//
	}

	ScreenNavigationException::~ScreenNavigationException()
	{
		//
	}
	
	ScreenNavigationException& ScreenNavigationException::operator=(const ScreenNavigationException&exception)
	{
		Exception::operator=(exception);
		return *this;
	}
	
	MEMBERFUNC_GETCLASSNAME(ScreenNavigationException)
}
