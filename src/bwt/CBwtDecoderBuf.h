//
// Created by metopa on 01.09.2015.
//

#ifndef BWT_RLE_CBWTDECODEBUF_H
#define BWT_RLE_CBWTDECODEBUF_H

#include <streambuf>
#include <vector>
#include <string>
#include "CBwtDecoder.h"

using namespace std;

class CBwtDecoderBuf : public streambuf {
	CBwtDecoder& coder_m;
	vector<uint32_t> positions_m;
	string buf_m;
	size_t posIdx_m;
	bool fail_m;
public:

	CBwtDecoderBuf( CBwtDecoder& coder, const vector<uint32_t>& positions, size_t blockSize ) :
			basic_streambuf(), coder_m( coder ), positions_m( positions ), posIdx_m( 0 ), fail_m( false ) {
		setg( nullptr, nullptr, nullptr );
		buf_m.resize( blockSize, '\0' );
	}

protected:
	virtual int_type underflow() override;
};


#endif //BWT_RLE_CBWTDECODEBUF_H
