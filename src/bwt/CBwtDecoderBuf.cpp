//
// Created by metopa on 01.09.2015.
//

#include "CBwtDecoderBuf.h"

CBwtDecoderBuf::int_type CBwtDecoderBuf::underflow() {
	if ( fail_m )
		return traits_type::eof();

	if ( gptr() < egptr() )
		return traits_type::to_int_type( *gptr() );

	size_t generated = 0;
	try {
		generated = coder_m.decode( &buf_m.front(), positions_m[posIdx_m++] );
	}
	//TODO distinct eof and fail
	catch( ... ) {
		fail_m = true;
		return traits_type::eof();
	}

	setg( &buf_m.front(), &buf_m.front(), &buf_m.front() + generated );
	return traits_type::to_int_type( *gptr() );
}
