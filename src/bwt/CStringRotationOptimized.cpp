//
// Created by metopa on 29.08.2015.
//

#include "CStringRotationOptimized.h"

ostream& operator <<( ostream& out, const CStringRotationOptimized& str ) {
	for ( size_t i = 0; i < str.size(); i++ )
		out << str[i];

	return out;
}

