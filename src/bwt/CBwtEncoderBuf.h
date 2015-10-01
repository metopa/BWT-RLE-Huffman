//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CBWTBUF_H
#define BWT_RLE_CBWTBUF_H

#include <streambuf>
#include <vector>
#include <cstdint>
#include "CBwtEncoder.h"
using namespace std;

/**
 * Output structure
 * 	--------------------
 * 	block 1 (block_size)
 * 	.
 * 	block N-1 (block_size)
 * 	block N (last_block_size)
 * 	endPos 1 (4 bytes)
 * 	.
 * 	endPos N (4 bytes)
 * 	block_size (4 bytes)
 * 	last_block_size (4 bytes)
 * 	N (4 bytes)
 *  --------------------
 */

class CBwtEncoderBuf : public streambuf {
	CBwtEncoder& coder_m;
	char * buffer_m;
	vector<uint32_t> header_m;
	size_t lastBlockSize_m;

public:
	CBwtEncoderBuf( CBwtEncoder& coder );
	virtual ~CBwtEncoderBuf();
	CBwtEncoderBuf( const CBwtEncoderBuf& ) = delete;
	void operator=( const CBwtEncoderBuf& ) = delete;

	const vector<uint32_t>& getHeader() const;

protected:
	virtual int_type underflow();
};



#endif //BWT_RLE_CBWTBUF_H
