//
// Created by metopa on 29.08.2015.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#ifndef BTW_RLE_CSTRINGROTATION_H
#define BTW_RLE_CSTRINGROTATION_H

#include "CStringRotation.h"

class CStringRotationOptimized : public CStringRotation {
protected:
	size_t divider_m;

public:
	CStringRotationOptimized( const char * str, size_t size,
							  size_t startPos )
			: CStringRotation( str, size, startPos ) {
		divider_m = size_m - 1;
	}

	inline char back() const {
		return (*this)[divider_m];
	}

	inline char operator[] ( size_t pos ) const {
		return str_m[( pos + startPos_m ) & divider_m];
	}

	inline bool operator< ( const CStringRotationOptimized& other ) const {
		int i;
		for ( i = 0; i < size_m; i++ ) {
			if ( (*this)[i] != other[i] )
				return (*this)[i] < other[i];
		}

		return false;
	}

	friend ostream& operator<<( ostream& out, const CStringRotationOptimized& str );
};




#endif //BTW_RLE_CSTRINGROTATION_H

#pragma clang diagnostic pop
