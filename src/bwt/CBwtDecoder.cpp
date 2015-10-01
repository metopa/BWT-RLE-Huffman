//
// Created by metopa on 31.08.2015.
//

#include "CBwtDecoder.h"
#include "../CLogger.h"
#include "../exceptions.h"
#include <cstring>

size_t CBwtDecoder::getBlockSize() const {
	return blockSize_m;
}

size_t CBwtDecoder::decode( char * outBuf, size_t endPos ) {
	size_t size = ( blockCount_m > 1 ? blockSize_m : lastBlockSize_m );

	logger.startNewActivity( CLogger::BWT );

	if ( eof_m || size == 0 )
		throw exceptions::eof();

	if ( --blockCount_m == 0 )
		eof_m = true;

	vector<unsigned char> block( size, 0 );
	size_t read = in_m.readsome( (char*)&block[0], size );
	if ( read != size )
		throw exceptions::fail();

	decodeImpl( outBuf, endPos, block );

	logger.finishActivity();
	return size;
}

void CBwtDecoder::decodeImpl( char * outBuf, size_t endPos, const vector<unsigned char>& block ) const {
	size_t count[256];
	memset( count, 0, 256 * sizeof( size_t ) );
	vector<size_t> pred ( block.size(), 0 );


	for ( size_t i = 0; i < block.size(); i++ ) {
		pred[i] = count[block[i]];
		count[block[i]]++;
	}

	size_t sum = 0;
	for ( int i = 0; i < 256; i++ ) {
		size_t j = count[i];
		count[i] = sum;
		sum += j;
	}

	for( size_t i = block.size(); i > 0; i-- ) {
		outBuf[i-1] = block[endPos];
		endPos = pred[endPos] + count[block[endPos]];
	}
}
