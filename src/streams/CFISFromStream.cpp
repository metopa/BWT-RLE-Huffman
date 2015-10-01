//
// Created by metopa on 30.08.2015.
//

#include "CFISFromStream.h"
#include <cassert>
bool CFISFromStream::fail() const {
	return in_m.fail();
}

bool CFISFromStream::get( char& c ) {

	auto tmp = in_m.get();
	if ( tmp != -1 ) {
		c = (char) tmp;
		update( 1 );
		return true;
	}
	else
		return false;
}

size_t CFISFromStream::readsome( char * buf, size_t size ) {
	size_t read = 0;
	while ( read < size ) {
		ptrdiff_t rc = in_m.readsome( buf + read, size - read );
		if ( rc == 0 || in_m.eof() )
			break;
		read += rc;
	}
	update( read );
	return read;
}
