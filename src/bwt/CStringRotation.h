//
// Created by metopa on 29.08.2015.
//

#ifndef BTW_RLE_CSTRINGROTATIONUNOPTIMIZED_H
#define BTW_RLE_CSTRINGROTATIONUNOPTIMIZED_H

#include <ostream>
using namespace std;

class CStringRotation {
protected:
	const char * str_m;
	size_t size_m;
	size_t startPos_m;

public:
	CStringRotation( const char * str, size_t size, size_t startPos ) :
			str_m( str ), size_m( size ), startPos_m( startPos ) {}

	inline CStringRotation& operator=( const CStringRotation& other ) {
		startPos_m = other.startPos_m;
		return *this;
	}

	inline char operator []( size_t pos ) const {
		//return str_m[( pos + startPos_m ) % size_m];
		pos += startPos_m;
		if ( pos >= size_m )
			pos -= size_m;
		return str_m[pos];
	}

	inline bool operator== ( const CStringRotation& other ) const {
		return ( &str_m == &other.str_m && startPos_m == other.startPos_m );
	}

	inline bool operator< ( const CStringRotation& other ) const {
		int i;
		for ( i = 0; i < size_m; i++ ) {
			if ( (*this)[i] != other[i] )
				return (*this)[i] < other[i];
		}

		return false;
	}

	inline size_t size() const {
		return size_m;
	}

	inline char back() const {
		return (*this)[size_m-1];
	}

	inline bool zeroOffset() const {
		return startPos_m == 0;
	}

	friend ostream& operator<<( ostream& out, const CStringRotation& str );
};


#endif //BTW_RLE_CSTRINGROTATIONUNOPTIMIZED_H
