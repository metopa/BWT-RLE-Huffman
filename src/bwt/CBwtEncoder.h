//
// Created by metopa on 29.08.2015.
//

#ifndef BTW_RLE_CBWT_H
#define BTW_RLE_CBWT_H


#include <cstddef>
#include <cstdint>
#include <string>
#include <typeinfo>
#include "../streams/CFastIStream.h"

class CBwtEncoder {
	CFastIStream& in_m;
	string buf_m;
	const size_t blockSize_m;

public:
	CBwtEncoder( CFastIStream& in, const size_t blockSize ) :
			in_m( in ), blockSize_m( blockSize ) {
		buf_m.reserve( blockSize );
	}

	~CBwtEncoder() {}

	size_t encode( char * outBuf, uint32_t& endPos );

	const size_t getBlockSize() const;

	void sortTest();

private:
	bool isPowerOf2( size_t i ) const;

	template <class RA_Iterator,
			class PivotProvider,
			class value_t = typename iterator_traits<RA_Iterator>::value_type,
			class diff_t =  typename iterator_traits<RA_Iterator>::difference_type>
	void besesort( RA_Iterator begin, RA_Iterator end,
				   const PivotProvider& pivotProvider,
				   size_t strLength,
				   size_t depth = 0,
				   value_t lowValue = value_t(0),
				   value_t highValue = value_t(-1) ) const;

	template <class T>
	uint32_t encodeInternal( char * outBuf, size_t size ) const;
};


#endif //BTW_RLE_CBWT_H
