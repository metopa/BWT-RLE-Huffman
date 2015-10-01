//
// Created by metopa on 01.09.2015.
//

#ifndef BWT_RLE_CRLEENCODEBUF_H
#define BWT_RLE_CRLEENCODEBUF_H

#include <streambuf>
#include <string>
#include "CRleEncoder.h"

using namespace std;

class CRleEncoderBuf : public streambuf {
	CRleEncoder& coder_m;
	size_t blockSize_m;
	string currentBlock_m;
	bool eof_m;

public:
	CRleEncoderBuf( CRleEncoder& coder, size_t blockSize = 1024 ) :
			basic_streambuf(), coder_m( coder ), blockSize_m( blockSize ) {
		setg( nullptr, nullptr, nullptr );
		eof_m = false;
	}

	bool eof() const {
		return eof_m;
	}

protected:
	virtual int_type underflow();
};


#endif //BWT_RLE_CRLEENCODEBUF_H
