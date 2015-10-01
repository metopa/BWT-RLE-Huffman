//
// Created by metopa on 05.09.2015.
//

#include "CBitsOutbuf.h"
#include <cassert>
CBitsOutbuf::CBitsOutbuf( CFastOStream& out ): out_m( out ) {
	idx_m = 0;
	byteIdx_m = 0;
	buf_m[0] = 0;
	uint32_t size = bufSize * 8;
	out_m.write( (char*)&size, 4 );
}

CBitsOutbuf::~CBitsOutbuf() {
	flush( true );
}

CBitsOutbuf& CBitsOutbuf::operator <<( CBits& value ) {
	unsigned int in_current = value.length();
	unsigned int in_next = 0;

	if ( in_current + byteIdx_m > 64 ) {
		in_current = 64 - byteIdx_m;
		in_next = value.length() - in_current;
	}

	buf_m[idx_m] |= ( value & mask( 0, in_current ) ) << byteIdx_m;
	byteIdx_m += in_current;

	if ( in_next ) {
		incIdx();
		byteIdx_m = in_next;
		buf_m[idx_m] = ( value & mask( in_current, value.length() ) ) >> in_current;
	}
	return *this;
}

void CBitsOutbuf::incIdx() {

	if ( idx_m == bufSize - 1 )
		flush();
	else
		idx_m++;
	buf_m[idx_m] = 0;
}

void CBitsOutbuf::flush( bool finalFlush ) {
	size_t length = idx_m * 8 + byteIdx_m / 8;
	idx_m = 0;
	byteIdx_m %= 8;

	if ( !finalFlush ) {
		out_m.put( 0 );
		assert( length == bufSize * 8 );
		assert( byteIdx_m == 0 );
	}
	else {
		out_m.put( (char) ( 0x80 | byteIdx_m ) );
		out_m.write( (char*)&length, 4 );
	}
	out_m.write( (char*)buf_m, length );

	if ( byteIdx_m )
		out_m.put( ((char*)buf_m)[length] );
}
