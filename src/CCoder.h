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
#include "bwt/CStringRotation.h"

using namespace std;

class CCoder {
	constexpr static size_t maxInmemorySize = ( is_same<size_t, uint32_t>::value  ?
											( (size_t) 1 << 30 ) / 2 * 5      : //2,5 Gb
											numeric_limits<size_t>::max() / 2 );


public:
	constexpr static const char * TEMP_FILE = "WlORUnZCWlORUnZC.temp";

	CCoder() { }

	static void encode( const char * in, const char * out, size_t blockSize = 1024 );

	static void encode( ifstream& in, ostream& out, size_t blockSize = 1024 );

	static bool decode( const char * in, const char * out );

private:
	static void encodeInMemory( CFastIStream& in, CFastOStream& out, size_t blockSize );

	static void encodeExternal( CFastIStream& in, CFastOStream& out, size_t blockSize, const char * tempFile = TEMP_FILE );

	static bool decodeInMemory( CFastIStream& in, CFastOStream& out );

	static bool decodeExternal ( CFastIStream& in, CFastOStream& out, const char * tempFile = TEMP_FILE );

	static bool decodeRLE( const string& in, CFastOStream& out );

	static bool decodeRLE( fstream& in, CFastOStream& out );

	static bool decodeRLE( CFastIStream& in, CFastOStream& out, vector<uint32_t>& positions,
						   uint32_t blockSize, uint32_t lastBlockSize, uint32_t blockCount );

};


#endif //BWT_RLE_CCODER_H
