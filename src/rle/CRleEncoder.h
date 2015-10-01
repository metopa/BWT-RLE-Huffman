//
// Created by metopa on 29.08.2015.
//

#ifndef BWT_RLE_CRLE_H
#define BWT_RLE_CRLE_H

#include "../faststreams.h"
#include <string>
using namespace std;

class CRleEncoder {
	CFastIStream& in_m;
	char buf_m[128];
	int sequence_m;
	size_t index_m;

public:
	CRleEncoder( CFastIStream& in ): in_m( in ) {
		sequence_m = 0;
		index_m = 0;
	}

	void encode( string& out, size_t count = (size_t) -1 );

	string encode( size_t count = (size_t) -1 );

private:
	void flush( string& out );

	void flushSeq( string& out );
};


#endif //BWT_RLE_CRLE_H
