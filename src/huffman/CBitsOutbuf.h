//
// Created by metopa on 05.09.2015.
//

#ifndef BWT_RLE_CBITSOUTBUF_H
#define BWT_RLE_CBITSOUTBUF_H

#include "CBits.h"
#include "../streams/CFastOStream.h"

using namespace std;

class CBitsOutbuf {
	constexpr static const size_t bufSize = 1024 * 100;
	CFastOStream& out_m;
	uint64_t buf_m[bufSize];
	size_t idx_m;
	size_t byteIdx_m;
public:

	CBitsOutbuf( CFastOStream& out );

	~CBitsOutbuf();

	CBitsOutbuf& operator<<( CBits& value );
private:
	void flush( bool finalFlush = false );

	inline uint64_t mask( int begin, int end ) {
		return  ( ( ( (uint64_t)1 << ( end - begin ) ) - 1 ) << begin );
	}

	void incIdx();
};


#endif //BWT_RLE_CBITSOUTBUF_H
