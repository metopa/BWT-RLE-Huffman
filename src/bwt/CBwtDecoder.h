//
// Created by metopa on 31.08.2015.
//

#ifndef BWT_RLE_CBWTDECODER_H
#define BWT_RLE_CBWTDECODER_H

#include "../faststreams.h"
#include <vector>
using namespace std;

class CBwtDecoder {
	CFastIStream& in_m;
	size_t blockSize_m;
	size_t lastBlockSize_m;
	size_t blockCount_m;
	bool eof_m;
public:

	CBwtDecoder( CFastIStream& in, size_t blockSize, size_t lastBlockSize, size_t blockCount )
			: in_m( in ), blockSize_m( blockSize ), lastBlockSize_m( lastBlockSize ),
			  blockCount_m( blockCount ), eof_m( false ) { }

	size_t getBlockSize() const;

	size_t decode( char * outBuf, size_t endPos );

private:
	void decodeImpl( char * outBuf, size_t endPos, const vector<unsigned char>& block ) const;
};


#endif //BWT_RLE_CBWTDECODER_H
