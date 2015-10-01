//
// Created by metopa on 30.08.2015.
//

#include "CFISFromBuffer.h"

bool CFISFromBuffer::fail() const {
	return fail_m;
}

bool CFISFromBuffer::get( char& c ) {
	if ( fail_m )
		return false;

	auto tmp = in_m.sbumpc();
	if ( tmp == streambuf::traits_type::eof() ) {
		fail_m = true;
		return false;
	}

	c = streambuf::traits_type::to_char_type( tmp );
	update( 1 );
	return true;
}

unsigned int CFISFromBuffer::readsome( char * buf, size_t size ) {
	size_t read = 0;
	if ( fail_m )
		return 0;
	while ( read < size ) {
		ptrdiff_t rc = in_m.sgetn( buf + read, size - read );
		if ( rc == 0 ) {
			fail_m = true;
			break;
		}
		read += rc;
	}
	update( read );
	return read;
}
