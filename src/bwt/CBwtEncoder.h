//
// Created by metopa on 29.08.2015.
//

#ifndef BTW_RLE_CBWT_H
#define BTW_RLE_CBWT_H


#include <stddef.h>
#include <stdint.h>
#include "../streams/CFastIStream.h"

class CBwtEncoder {
	CFastIStream& in_m;
	char * buf_m;
	const size_t blockSize_m;

public:
	CBwtEncoder( CFastIStream& in, const size_t blockSize ) :
			in_m( in ), blockSize_m( blockSize ) {
		buf_m = new char[blockSize];
	}

	~CBwtEncoder() {
		delete[] buf_m;
	}

	CBwtEncoder( const CBwtEncoder& ) = delete;
	void operator= ( const CBwtEncoder& ) = delete;

	size_t encode( char * outBuf, uint32_t& endPos );

	const size_t getBlockSize() const;

private:
	bool isPowerOf2( size_t i ) const;

	template <class T>
	uint32_t encodeInternal( char * outBuf, size_t size ) const;
};


#endif //BTW_RLE_CBWT_H
