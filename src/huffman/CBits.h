//
// Created by metopa on 05.09.2015.
//

#ifndef BWT_RLE_CBITS_H
#define BWT_RLE_CBITS_H

#include <cstdint>
#include <ostream>
//max size is 64 bits
class CBits {
	uint64_t data_m;
	uint8_t length_m;

public:
	CBits() {
		data_m = 0;
		length_m = 0;
	}

	inline uint64_t get( uint8_t pos ) {
		return data_m & ( 1 << pos );
	}

	inline void set( uint8_t pos ) {
		data_m |= ( 1 << pos );
	}

	inline void reset( uint8_t pos ) {
		data_m &= ~( 1 << pos );
	}

	inline void append_1() {
		set( length_m++ );
	}

	inline void append_0() {
		reset( length_m++ );
	}

	inline operator uint64_t() const {
		return data_m;
	}

	inline void clear() {
		length_m = 0;
	}

	inline void shrink() {
		length_m--;
	}

	inline uint8_t length() const {
		return length_m;
	}

	inline uint64_t operator[]( uint8_t pos ) {
		return get( pos );
	}
};

std::ostream& operator<<( std::ostream& out, CBits& b );


#endif //BWT_RLE_CBITS_H
