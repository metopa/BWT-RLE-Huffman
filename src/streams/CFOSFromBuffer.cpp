//
// Created by metopa on 30.08.2015.
//

#include "CFOSFromBuffer.h"

bool CFOSFromBuffer::write( const char * data, size_t size ) {
	if ( fail_m )
		return false;
	try {
		fail_m = ( out_m.sputn( data, size ) != size );
		if ( !fail_m ) {
			update( size );
			return true;
		}
		else
			return false;
	}
	catch (...) {
		fail_m = true;
		return fail_m;
	}
}

bool CFOSFromBuffer::put( char c ) {
	if ( fail_m )
		return false;
	fail_m = ( out_m.sputc( c ) != c );
	if ( !fail_m ) {
		update( 1 );
		return true;
	}
	else
		return false;
}


bool CFOSFromBuffer::fail() const {
	return fail_m;
}
