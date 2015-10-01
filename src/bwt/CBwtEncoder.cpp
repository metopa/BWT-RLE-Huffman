//
// Created by metopa on 29.08.2015.
//

#include "CBwtEncoder.h"
#include "CStringRotationOptimized.h"
#include "../CLogger.h"

#include <vector>
#include <algorithm>

using namespace std;

size_t CBwtEncoder::encode( char * outBuf, uint32_t & endPos ) {
	logger.startNewActivity( CLogger::BWT );

	size_t size = in_m.readsome( buf_m, blockSize_m );

	if ( size == 0 )
		return 0;
	else if ( size == 1 ) {
		*outBuf = *buf_m;
		endPos = 0;
	}
	else if ( isPowerOf2( size ) )
		endPos = encodeInternal<CStringRotationOptimized>( outBuf, size );
	else
		endPos = encodeInternal<CStringRotation>( outBuf, size );

	logger.finishActivity();

	return size;
}

template<class T>
uint32_t CBwtEncoder::encodeInternal( char * outBuf, size_t size ) const {
	vector<T> rotations;
	rotations.reserve( size );
	for ( size_t i = 0; i < size; i++ )
		rotations.push_back( T( buf_m, size, i ) );

	stable_sort( rotations.begin(), rotations.end() ); //TODO Better sort

	uint32_t endPos = 0;
	for ( size_t i = 0; i < rotations.size(); i++ ) {
		if ( rotations[i].zeroOffset() )
			endPos = i;

		outBuf[i] = rotations[i].back();
	}

	return endPos;
}

bool CBwtEncoder::isPowerOf2( size_t i ) const {
	if ( i == 0 )
		return false;

	while ( i % 2 == 0 )
		i /= 2;

	return i / 2 == 0;
}

const size_t CBwtEncoder::getBlockSize() const {
	return blockSize_m;
}
