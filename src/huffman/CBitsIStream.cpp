#include "CBitsIStream.h"

CBitsIStream::CBitsIStream( CFastIStream& in ):
		in_m( in ), idx_m( 0 ), byteIdx_m( 0 ), eof_m( false ) {
	blockSize_m = 0;

	if ( in_m.readsome( (char*)&blockSize_m, 4 ) != 4 )
		throw exceptions::fail();

	buf_m.reserve( blockSize_m );
	idx_m = blockSize_m;
}

void CBitsIStream::readmore() {
	char blockType = 0;
	in_m.get( blockType );

	if ( blockType == 0 ) { //NORMAL
		in_m.readsome( &buf_m.front(), blockSize_m );
	}
	else { //LAST BLOCK
		eof_m = true;
		lastByteSize_m = (char) ( blockType & 0x7F );
		in_m.readsome( (char*)&blockSize_m, 4 );
		in_m.readsome( &buf_m.front(), blockSize_m );
		if ( lastByteSize_m )
			in_m.readsome( (char *) &lastByte_m, 1 );
	}

	if ( in_m.fail() )
		throw exceptions::fail();

	idx_m = 0;
	byteIdx_m = 0;
}

