//
// Created by metopa on 30.08.2015.
//

#include "CBwtEncoderBuf.h"

CBwtEncoderBuf::CBwtEncoderBuf( CBwtEncoder& coder ) : basic_streambuf(), coder_m( coder ) {
	buffer_m = new char[coder.getBlockSize()];
	setg( buffer_m, buffer_m, buffer_m );
}

CBwtEncoderBuf::~CBwtEncoderBuf() {
	delete[] buffer_m;
}

streambuf::int_type CBwtEncoderBuf::underflow() {
	if ( gptr() < egptr() )
		return traits_type::to_int_type( *gptr() );

	size_t endPos;
	size_t bytesGenerated = coder_m.encode( buffer_m, endPos );

	if ( bytesGenerated == 0 ) {
		header_m.push_back( coder_m.getBlockSize() );
		header_m.push_back( lastBlockSize_m );
		header_m.push_back( header_m.size() - 2 );
		return traits_type::eof();
	}

	header_m.push_back( endPos );
	lastBlockSize_m = bytesGenerated;
	setg( buffer_m, buffer_m, buffer_m + bytesGenerated );

	return traits_type::to_int_type( *gptr() );
}


const vector<uint32_t>& CBwtEncoderBuf::getHeader() const {
	return header_m;
}
