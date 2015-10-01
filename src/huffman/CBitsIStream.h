//
// Created by metopa on 06.09.2015.
//

#ifndef BWT_RLE_CBITSCUSTOMINBUF_H
#define BWT_RLE_CBITSCUSTOMINBUF_H


#include "../streams/CFastIStream.h"
#include "../exceptions.h"
#include <string>

class CBitsIStream {
	CFastIStream& in_m;
	std::string buf_m;

	size_t blockSize_m;
	size_t idx_m;
	char byteIdx_m;

	char lastByteSize_m;
	unsigned char lastByte_m;

	bool eof_m;

public:

	CBitsIStream( CFastIStream& in );

	inline unsigned char getNextBit()  {

		if ( byteIdx_m == 8 ) {
			idx_m++;
			byteIdx_m = 0;
		}
		if ( idx_m == blockSize_m ) {
			if ( eof_m ) {
				if ( byteIdx_m < lastByteSize_m )
					return bt( lastByte_m, byteIdx_m++ );
				else
					throw exceptions::eof();
			}
			else
				readmore();
		}

		return bt( buf_m[idx_m], byteIdx_m++ );;
	}

private:
	void readmore();

	inline unsigned char bt( char byte, char pos ) {
		return (unsigned char)byte & ( (unsigned char)1 << pos );
	}


};


#endif //BWT_RLE_CBITSCUSTOMINBUF_H
