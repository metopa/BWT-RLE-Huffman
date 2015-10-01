//
// Created by metopa on 01.09.2015.
//

#ifndef BWT_RLE_CRLEDECODERBUF_H
#define BWT_RLE_CRLEDECODERBUF_H

#include <streambuf>
#include "CRleDecoder.h"

using namespace std;

class CRleDecoderBuf : public streambuf{
	CRleDecoder& coder_m;
	char * buf_m;
	size_t blockSize_m;
public:
	CRleDecoderBuf( CRleDecoder& coder, size_t blockSize = 1024 ) :
			basic_streambuf(), coder_m( coder ), blockSize_m( blockSize ){
		setg( nullptr, nullptr, nullptr );
		buf_m = new char[blockSize];
	}
	~CRleDecoderBuf() {
		delete[] buf_m;
	}
	CRleDecoderBuf( const CRleDecoderBuf& ) = delete;
	void operator=( const CRleDecoderBuf& ) = delete;

	size_t getBlockSize() const {
		return blockSize_m;
	}

protected:
	virtual int_type underflow() override;


	virtual streamsize xsgetn( char_type * __s, streamsize __n ) override;
};


#endif //BWT_RLE_CRLEDECODERBUF_H
