//
// Created by metopa on 05.09.2015.
//

#include "CBits.h"

std::ostream& operator <<( std::ostream& out, CBits& b ) {
	if ( b.length() == 0 )
		return out << '-';
	for ( unsigned char i = 0; i < b.length(); i++ )
		out << ( b.get(i) ? '1' : '0' );
	return out;
}