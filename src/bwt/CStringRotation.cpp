//
// Created by metopa on 29.08.2015.
//


#include "CStringRotation.h"

ostream& operator <<( ostream& out, const CStringRotation& str ) {
	for ( size_t i = 0; i < str.size(); i++ )
		out << str[i];

	return out;
}
