//
// Created by metopa on 01.09.2015.
//

#include "CRleEncoderBuf.h"

CRleEncoderBuf::int_type CRleEncoderBuf::underflow() {
	if ( gptr() < egptr() )
		return traits_type::to_int_type( *gptr() );

	if ( eof_m )
		return traits_type::eof();

	currentBlock_m.clear();
	coder_m.encode( currentBlock_m, blockSize_m );

	if ( currentBlock_m.empty() ) {
		eof_m = true;
		return traits_type::eof();
	}

	setg( &currentBlock_m[0], &currentBlock_m[0], &currentBlock_m.back() + 1 );

	return traits_type::to_int_type( *gptr() );
}
