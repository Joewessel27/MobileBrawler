
#pragma once

#include "../Types.h"
#include "String.h"
#include "../Exception/Utilities/BitSetOutOfBoundsException.h"

namespace GameLibrary
{
	class BitSet
	{
	private:
		byte b;
		
	public:
		enum Bitmask
		{
			BITMASK_1 = 0x01,
			BITMASK_2 = 0x02,
			BITMASK_3 = 0x04,
			BITMASK_4 = 0x08,
			BITMASK_5 = 0x10,
			BITMASK_6 = 0x20,
			BITMASK_7 = 0x40,
			BITMASK_8 = 0x80
		};

		BitSet();
		BitSet(const BitSet&);
		BitSet(byte b);
		explicit BitSet(char bits[8]);
		explicit BitSet(bool bits[8]);
		~BitSet();

		BitSet& operator=(const BitSet&bitset);
		bool operator==(const BitSet&) const;
		
		bool get(size_t index) const;
		void set(size_t index, bool toggle);
		
		const byte& getByte() const;
		
		String toString() const;
	};
}
