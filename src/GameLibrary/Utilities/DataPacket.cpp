
#define _CRT_SECURE_NO_WARNINGS

#include "DataPacket.h"
#include <cstdio>
#include <cstdlib>

namespace GameLibrary
{
	int DataPacket::toInt(const void*data)
	{
		const int*r = (const int*)data;
		return *r;
	}

	bool DataPacket::toBool(const void*data)
	{
		const bool*r = (const bool*)data;
		return *r;
	}
	
	long DataPacket::toLong(const void*data)
	{
		const long*r = (const long*)data;
		return *r;
	}
	
	float DataPacket::toFloat(const void*data)
	{
		const float*r = (const float*)data;
		return *r;
	}
	
	double DataPacket::toDouble(const void*data)
	{
		const double*r = (const double*)data;
		return *r;
	}

	DataPacket::DataPacket()
	{
		data = nullptr;
		total = 0;
	}

	DataPacket::DataPacket(const DataPacket&dataPacket)
	{
		if(dataPacket.data == nullptr)
		{
			data = nullptr;
			total = 0;
		}
		else
		{
			data = (byte*)std::malloc(dataPacket.total);
			for(size_t i=0; i<dataPacket.total; i++)
			{
				data[i] = dataPacket.data[i];
			}
			total = dataPacket.total;
		}
	}
	
	DataPacket::DataPacket(const String&str)
	{
		if(str.length()==0)
		{
			data = nullptr;
			total = 0;
		}
		{
			data = (byte*)std::malloc(str.length());
			const byte* cpyBytes = (const byte*)((const char*)str);
			for(size_t i = 0; i < str.length(); i++)
			{
				data[i] = cpyBytes[i];
			}
			total = str.length();
		}
	}
	
	DataPacket::DataPacket(size_t size)
	{
		data = (byte*)std::malloc(size);
		for(size_t i=0; i<size; i++)
		{
			data[i] = 0;
		}
		total = size;
	}
	
	DataPacket::DataPacket(const void*data1, size_t size)
	{
		if(data1 == nullptr)
		{
			throw IllegalArgumentException("data", "null");
		}
		else if(size>0)
		{
			data = (byte*)std::malloc(size);
			const byte*copyBytes = (const byte*)data1;
			for(size_t i=0; i<size; i++)
			{
				data[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			data = nullptr;
			total = 0;
		}
	}
	
	DataPacket::~DataPacket()
	{
		if(data!=nullptr)
		{
			std::free(data);
			data = nullptr;
			total = 0;
		}
	}

	DataPacket& DataPacket::operator=(const DataPacket&dataPacket)
	{
		setData(dataPacket);
		return *this;
	}

	bool DataPacket::loadFromFile(const String&path, String*error)
	{
		FILE*file = std::fopen(path, "r");
		if (file == nullptr)
		{
			//TODO add switch for errno
			if(error!=nullptr)
			{
				*error = "Unable to load data from file";
			}
			return false;
		}
		
		std::fseek(file, 0, SEEK_END);
		size_t fileSize = (size_t)std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
		
		if(data == nullptr)
		{
			data = (byte*)std::malloc(fileSize);
		}
		else
		{
			data = (byte*)std::realloc(data,fileSize);
		}
		
		std::fread((void*)data, 1, fileSize, file);
		
		std::fclose(file);

		total = (size_t)fileSize;

		return true;
	}
	
	bool DataPacket::saveToFile(const String&path, String*error) const
	{
		FILE*file = std::fopen(path, "w");
		if(file==NULL)
		{
			if(error != nullptr)
			{
				//TODO add checking of errno
				*error = "Unable to open file for writing";
			}
			return false;
		}
		
		size_t written = std::fwrite(data, 1, total, file);
		if(written != total)
		{
			if(error != nullptr)
			{
				//TODO add checking of errno
				*error = (String)"Unable to write all bytes to file stream";
			}
			return false;
		}
		
		if(std::fclose(file) == EOF)
		{
			if(error!=nullptr)
			{
				//TODO add checking of errno
				*error = "Error closing the file";
			}
			return false;
		}
		return true;
	}
	
	String DataPacket::toString() const
	{
		if(data == nullptr)
		{
			return String();
		}
		else
		{
			return String((char*)data, total);
		}
	}
	
	DataPacket::operator String() const
	{
		if(data == nullptr)
		{
			return String();
		}
		else
		{
			return String((char*)data, total);
		}
	}
	
	void*DataPacket::getData()
	{
		return (void*)data;
	}

	const void*DataPacket::getData() const
	{
		return (const void*)data;
	}

	void DataPacket::setData(const void*data1, size_t size)
	{
		if(size > 0)
		{
			if(data1==nullptr)
			{
				throw IllegalArgumentException("data", "null");
			}

			if(data==nullptr)
			{
				data = (byte*)std::malloc(size);
			}
			else
			{
				data = (byte*)std::realloc(data, size);
			}

			const byte*copyBytes = (const byte*)data1;
			for(size_t i=0; i<size; i++)
			{
				data[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			if(data != nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}

	void DataPacket::setData(const DataPacket&dataPacket)
	{
		if(dataPacket.total > 0)
		{
			if(data==nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
			}
			else
			{
				data = (byte*)std::realloc(data, dataPacket.total);
			}

			for(size_t i=0; i<dataPacket.total; i++)
			{
				data[i] = dataPacket.data[i];
			}
			total = dataPacket.total;
		}
		else
		{
			if(data != nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}
	
	size_t DataPacket::size() const
	{
		return total;
	}
	
	void DataPacket::resize(size_t size)
	{
		if(size > 0)
		{
			if(data==nullptr)
			{
				data = (byte*)std::malloc(size);
				for(size_t i=0; i<size; i++)
				{
					data[i] = 0;
				}
				total = size;
			}
			else
			{
				data = (byte*)std::realloc(data, size);
				if(size>total)
				{
					for(size_t i=total; i<size; i++)
					{
						data[i] = 0;
					}
				}
				total = size;
			}
		}
		else
		{
			if(data!=nullptr)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
		}
	}
	
	void DataPacket::clear()
	{
		if(data!=nullptr)
		{
			std::free(data);
			data = nullptr;
			total = 0;
		}
	}
	
	void DataPacket::add(const void*data1, size_t size)
	{
		if(size>0)
		{
			if(data1 == nullptr)
			{
				throw IllegalArgumentException("data", "null");
			}

			if(data == nullptr)
			{
				data = (byte*)std::malloc(size);
				const byte*copyBytes = (const byte*)data1;
				for(size_t i=0; i<size; i++)
				{
					data[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				size_t newTotal = total + size;
				data = (byte*)std::realloc(data, newTotal);
				const byte*copyBytes = (const byte*)data1;
				size_t counter = 0;
				for(size_t i=total; i<newTotal; i++)
				{
					data[i] = copyBytes[counter];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(size_t byteIndex, const void*data1, size_t size)
	{
		if(data1 == nullptr)
		{
			throw IllegalArgumentException("data","null");
		}
		else if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(size);
				const byte*copyBytes = (const byte*)data1;
				for(size_t i=0; i<size; i++)
				{
					data[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				size_t newTotal = total+size;
				data = (byte*)std::realloc(data, newTotal);
				const byte*copyBytes = (const byte*)data1;
				size_t counter = (total-1);
				size_t endIndex = byteIndex + size;
				for(size_t i=(newTotal-1); i>endIndex; i--)
				{
					data[i] = data[counter];
					counter--;
				}
				counter = byteIndex;
				for(size_t i=0; i<size; i++)
				{
					data[counter] = copyBytes[i];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(const DataPacket&dataPacket)
	{
		if(dataPacket.total>0)
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
				for(size_t i=0; i<dataPacket.total; i++)
				{
					data[i] = dataPacket.data[i];
				}
				total = dataPacket.total;
			}
			else
			{
				size_t newTotal = total + dataPacket.total;
				data = (byte*)std::realloc(data, newTotal);
				size_t counter = 0;
				for(size_t i=total; i<newTotal; i++)
				{
					data[i] = dataPacket.data[counter];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(size_t byteIndex, const DataPacket&dataPacket)
	{
		if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(dataPacket.total>0)
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(dataPacket.total);
				for(size_t i=0; i<dataPacket.total; i++)
				{
					data[i] = dataPacket.data[i];
				}
				total = dataPacket.total;
			}
			else
			{
				size_t newTotal = total+dataPacket.total;
				data = (byte*)std::realloc(data, newTotal);
				size_t counter = (total-1);
				size_t endIndex = byteIndex + dataPacket.total;
				for(size_t i=(newTotal-1); i>endIndex; i--)
				{
					data[i] = data[counter];
					counter--;
				}
				counter = byteIndex;
				for(size_t i=0; i<dataPacket.total; i++)
				{
					data[counter] = dataPacket.data[i];
					counter++;
				}
				total = newTotal;
			}
		}
	}
	
	void DataPacket::add(byte dataByte)
	{
		if(data == nullptr)
		{
			data = (byte*)std::malloc(1);
			data[0] = dataByte;
			total=1;
		}
		else
		{
			data = (byte*)std::realloc(data, total+1);
			data[total] = dataByte;
			total++;
		}
	}
	
	void DataPacket::add(size_t byteIndex, byte dataByte)
	{
		if(byteIndex > total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			if(data == nullptr)
			{
				data = (byte*)std::malloc(1);
				data[0] = dataByte;
				total = 1;
			}
			else
			{
				size_t newTotal = total+1;
				data = (byte*)std::realloc(data, newTotal);
				for(size_t i=(newTotal-1); i>byteIndex; i--)
				{
					data[i] = data[i-1];
				}
				data[byteIndex] = dataByte;
				total = newTotal;
			}
		}
	}
	
	void DataPacket::remove(size_t byteIndex, size_t size)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			size_t endOfRemove = byteIndex+size;
			size_t counter = byteIndex;
			for(size_t i=endOfRemove; i<total; i++)
			{
				data[counter] = data[i];
				counter++;
			}
			size_t newTotal = total - size;
			if(newTotal == 0)
			{
				std::free(data);
				data = nullptr;
				total = 0;
			}
			else
			{
				data = (byte*)std::realloc(data, newTotal);
				total = newTotal;
			}
		}
	}
	
	void DataPacket::remove(size_t byteIndex)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			size_t endOfRemove = byteIndex+1;
			size_t counter = byteIndex;
			for(size_t i=endOfRemove; i<total; i++)
			{
				data[counter] = data[i];
				counter++;
			}
			size_t newTotal = total - 1;
			data = (byte*)std::realloc(data, newTotal);
			total = newTotal;
		}
	}
	
	void DataPacket::set(size_t byteIndex, const void*data1, size_t size)
	{
		if(data1 == nullptr)
		{
			throw IllegalArgumentException("data", "null");
		}
		size_t endIndex = byteIndex + size;
		if(endIndex>total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(size>0)
		{
			const byte*copyBytes = (const byte*)data1;
			size_t counter = byteIndex;
			for(size_t i=0; i<size; i++)
			{
				data[counter] = copyBytes[i];
			}
		}
	}
	
	void DataPacket::set(size_t byteIndex, const DataPacket&dataPacket)
	{
		size_t endIndex = byteIndex + dataPacket.total;
		if(endIndex>total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else if(dataPacket.total>0)
		{
			size_t counter = byteIndex;
			for(size_t i=0; i<dataPacket.total; i++)
			{
				data[counter] = dataPacket.data[i];
			}
		}
	}
	
	void DataPacket::set(size_t byteIndex, byte dataByte)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			data[byteIndex] = dataByte;
		}
	}
	
	void*DataPacket::get(size_t byteIndex)
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return (void*)(data + byteIndex);
		}
	}

	const void*DataPacket::get(size_t byteIndex) const
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return (const void*)(data + byteIndex);
		}
	}
	
	byte DataPacket::getByte(size_t byteIndex) const
	{
		if(byteIndex >= total)
		{
			throw DataPacketOutOfBoundsException(byteIndex, total);
		}
		else
		{
			return data[byteIndex];
		}
	}
}