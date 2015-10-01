//
// Created by metopa on 30.08.2015.
//

#include "CFOSFromStream.h"
#include <cassert>
bool CFOSFromStream::write( const char * data, size_t size ) {
	out_m.write( data, size );
	if ( out_m ) {
		update( size );
		return true;
	}
	else
		return false;
}

bool CFOSFromStream::put( char c ) {

	out_m.put( c );
	if ( out_m ) {
		update( 1 );
		return true;
	}
	else
		return false;
}


bool CFOSFromStream::fail() const {
	return out_m.fail();
}
