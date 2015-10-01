//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CCODER_H
#define BWT_RLE_CCODER_H

#include <fstream>
#include <vector>
#include "streams/CFastIStream.h"
#include "streams/CFastOStream.h"
#include "huffman/CHuffmanDecoder.h"

using namespace std;

class CCoder {
public:
	static void encode( const char * in, const char * out, size_t blockSize = 1024 );

	static void encode( ifstream& in, ostream& out, size_t blockSize = 1024 );

private:
	static void encodeInMemory( CFastIStream& in, CFastOStream& out, size_t blockSize );

	static void encodeExternal( CFastIStream& in, CFastOStream& out, const char * tempFile, size_t blockSize );


public:
	static bool decode( const char * in, const char * out );

private:
	static bool decodeExternal ( CFastIStream& in, CFastOStream& out, const char * tempFile );

	static bool decodeRLE( fstream& in, CFastOStream& out );

	static bool decodeRLE( CFastIStream& in, CFastOStream& out, vector<uint32_t>& positions, uint32_t blockSize,
						   uint32_t lastBlockSize, uint32_t blockCount );
};


#endif //BWT_RLE_CCODER_H
