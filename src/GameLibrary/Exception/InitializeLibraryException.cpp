
#include "InitializeLibraryException.h"

namespace GameLibrary
{
	InitializeLibraryException::InitializeLibraryException(const InitializeLibraryException&exception) : Exception(exception)
	{
		//
	}

	InitializeLibraryException::InitializeLibraryException(const String&lib, const String&message) : Exception(lib + ": " + message)
	{
		library = lib;
	}

	InitializeLibraryException::~InitializeLibraryException()
	{
		//
	}
}