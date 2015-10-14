//
// Created by metopa on 29.08.2015.
//

#include "CBwtEncoder.h"
#include "CStringRotationOptimized.h"
#include "../CLogger.h"

#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

size_t CBwtEncoder::encode( char * outBuf, uint32_t & endPos ) {
	logger.startNewActivity( CLogger::BWT );

	size_t size = in_m.readsome( &buf_m.front(), blockSize_m );

	if ( size == 0 )
		return 0;
	else if ( size == 1 ) {
		*outBuf = buf_m.front();
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
		rotations.push_back( T( &buf_m.front(), size, i ) );

	stable_sort( rotations.begin(), rotations.end() ); //TODO Better sort

	uint32_t endPos = 0;//TODO Fix types
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

template<class RA_Iterator,
		class PivotProvider,
		class value_t,
		class diff_t>
void CBwtEncoder::besesort( RA_Iterator begin, RA_Iterator end,
							const PivotProvider& pivotProvider,
							size_t strLength, size_t depth,
							value_t lowValue, value_t highValue ) const {
	if ( distance( begin, end ) <= 1 || depth == strLength )
		return;

	value_t pivot = pivotProvider( begin, end, lowValue, highValue );

	RA_Iterator low = begin,
			high = end - 1,
			lowEq = low,
			highEq = high;

	while ( true ) {
		while ( low < high && (*low)[depth] <= pivot ) {
			if ( (*low)[depth] == pivot )
				swap( *(lowEq++), *low );
			++low;
		}
		while ( low < high && (*high)[depth] >= pivot ) {
			if ( (*high)[depth] == pivot )
				swap( *(highEq--), *high );
			--high;
		}
		if ( low > high )
			break;
		swap( *(low++), *(high--) );
	}

	using RIter = reverse_iterator<RA_Iterator>;
	
	diff_t toSwap = min ( lowEq - begin, low - lowEq );
	low -= toSwap;
	swap_ranges( begin, begin + toSwap, low );
	assert( (*low)[depth] >= pivot );
	assert( low == begin || (*(low-1))[depth] < pivot );
	besesort( begin, low, pivotProvider, strLength, depth, lowValue, pivot );
	
	toSwap = min ( end - highEq - 1, highEq - high );
	high += toSwap;
	swap_ranges( RIter(end), RIter(end - toSwap), RIter(high + 1) );
	assert( (*high)[depth] > pivot );
	assert( high == begin || (*(high-1))[depth] <= pivot );
	besesort( high, end, pivotProvider, strLength, depth, pivot, highValue );

	besesort( low, high, pivotProvider, strLength, depth + 1 );
}

/*struct defaultPivot
auto defaultPivot = []( auto& begin, auto& end, char, char ) {
	vector<decltype(*begin)> pivots({ *begin, *(end-1), *(begin + (end - begin) / 2 ) });
	sort( pivots.begin(), pivots.end() );
	return pivots[1];
};*/



void CBwtEncoder::sortTest() {
	vector<string> data = { "ab", "dd", "dd", "bg", "we", "de", "we", "dd", "re", "te", "ac", "re", "te", "dd" };

	//besesort( data.begin(), data.end(), defaultPivot, 20 );
}
