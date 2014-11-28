
#include "UnsupportedImageFormatException.h"

namespace GameLibrary
{
	UnsupportedImageFormatException::UnsupportedImageFormatException(const UnsupportedImageFormatException&exception) : Exception(exception)
	{
		format = exception.format;
	}

	UnsupportedImageFormatException::UnsupportedImageFormatException(const String&formatType) : Exception((formatType.length() == 0 ? "Unspecified Image format" : ((String)"Unsupported Image format \"" + formatType + "\"")))
	{
		format = formatType;
	}

	UnsupportedImageFormatException::~UnsupportedImageFormatException()
	{
		//
	}
}