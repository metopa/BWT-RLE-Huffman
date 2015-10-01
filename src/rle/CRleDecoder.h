//
// Created by metopa on 01.09.2015.
//

#ifndef BWT_RLE_CRLEDECODE_H
#define BWT_RLE_CRLEDECODE_H

#include "../faststreams.h"

class CRleDecoder {
	CFastIStream& in_m;
	char length_m;
	char current_m;
	bool eof_m;
public:
	CRleDecoder( CFastIStream& in ) : in_m( in ), length_m( 0 ), eof_m( false ) { }

	size_t decode( char * out, size_t count );

	bool eof() const;

private:
	bool getNewLength();
};


#endif //BWT_RLE_CRLEDECODE_H
