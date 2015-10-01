//
// Created by metopa on 01.09.2015.
//

#include "CRleDecoder.h"
#include "../CLogger.h"
#include "../exceptions.h"


size_t CRleDecoder::decode( char * out, size_t count ) {
	size_t generated = 0;

	logger.startNewActivity( CLogger::RLE );

	if ( eof_m )
		throw exceptions::eof();

	while ( count-- && ( length_m || getNewLength() ) ) {
		if ( length_m > 0 ) {
			*out = current_m;
			out++;
			length_m--;
		}
		else {
			if ( !in_m.get( current_m ) ) //TODO Optimize
				break;
			*out = current_m;
			out++;
			length_m++;
		}
		generated++;
	}

	logger.finishActivity();

	return generated;
}

bool CRleDecoder::getNewLength() {
	if ( !in_m.get( length_m ) ) {
		eof_m = true;
		return false;
	}
	return length_m != 0 && ( length_m < 0 || in_m.get( current_m ) );
}

bool CRleDecoder::eof() const {
	return eof_m;
}
