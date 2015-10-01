//
// Created by metopa on 01.09.2015.
//

#include "CRleDecoderBuf.h"
#include <cstring>
CRleDecoderBuf::int_type CRleDecoderBuf::underflow() {
	if ( gptr() < egptr() )
		return traits_type::to_int_type( *gptr() );

	int rc = coder_m.decode( buf_m, blockSize_m );

	if ( rc == -1 ) {
		return traits_type::eof();
	}

	setg( buf_m, buf_m, buf_m + rc );
	return traits_type::to_int_type( *gptr() );
}

streamsize CRleDecoderBuf::xsgetn( char * __s, streamsize __n ) {
	unsigned int written = 0;
	while ( written < __n ) {
		unsigned int avail = egptr() - gptr();
		if ( avail == 0 ) {
			if ( underflow() == -1 )
				break;
			else
				continue;
		}
		if ( avail > __n - written )
			avail = __n - written;
		memcpy( __s + written, gptr(), avail );
		written += avail;
		__safe_gbump( avail );
	}
	return written;
}
