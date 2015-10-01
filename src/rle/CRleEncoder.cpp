//
// Created by metopa on 29.08.2015.
//

#include "CRleEncoder.h"
#include "../CLogger.h"

void CRleEncoder::encode( string& out, size_t count ) {
	char c;

	logger.startNewActivity( CLogger::RLE );

	while ( count-- && in_m.get( c ) ) {
		if ( index_m == 128 )
			flush( out );
		else if ( sequence_m == 127 )
			flushSeq( out );

		if ( sequence_m > 0 ) {
			if ( c == *buf_m )
				sequence_m++;
			else {
				flushSeq( out );
				*buf_m = c;
				index_m++;
			}
		}
		else {
			if ( index_m >= 2 && c == buf_m[index_m - 1] && c == buf_m[index_m - 2] ) {
				index_m -= 2;
				if ( index_m > 0 )
					flush( out );
				sequence_m = 3;
				*buf_m = c;
			}
			else
				buf_m[index_m++] = c;
		}
	}

	if ( in_m.fail() ) {
		if ( index_m > 0 )
			flush( out );
		else if ( sequence_m > 0 )
			flushSeq( out );
	}

	logger.finishActivity();
}


string CRleEncoder::encode( size_t count ) {
	string out;
	encode( out, count );
	return out;
}

void CRleEncoder::flush( string& out ) {
	out += (char) -index_m;
	out.append( buf_m, buf_m + index_m );
	index_m = 0;
}

void CRleEncoder::flushSeq( string& out ) {
	out += (char) sequence_m;
	out += *buf_m;
	sequence_m = 0;
}
