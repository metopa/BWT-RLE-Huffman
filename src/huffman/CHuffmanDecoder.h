//
// Created by metopa on 07.09.2015.
//

#ifndef BWT_RLE_CHUFFMANDECODER_H
#define BWT_RLE_CHUFFMANDECODER_H

#include "../faststreams.h"

class CHuffmanDecoder {
	CFastIStream& in_m;
	CFastOStream& out_m;

public:
	CHuffmanDecoder( CFastIStream& in, CFastOStream& out ) :
			in_m( in ), out_m( out ) {}


	bool decode();

};


#endif //BWT_RLE_CHUFFMANDECODER_H
