//
// Created by metopa on 05.10.2015.
//

#include "CFOSInMemory.h"

bool CFOSInMemory::write( const char * data, size_t size ) {
	buf_m.append( data, size );
	return true;
}

bool CFOSInMemory::put( char c ) {
	buf_m += c;
	return true;
}

bool CFOSInMemory::fail() const {
	return false;
}
