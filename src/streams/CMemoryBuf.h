//
// Created by metopa on 26.09.2015.
//

#ifndef BWT_RLE_CMEMORYBUF_H
#define BWT_RLE_CMEMORYBUF_H

#include <streambuf>
#include <vector>
#include <cassert>
using namespace std;

class CMemoryBuf : public streambuf {
	vector<char> buf_m;
	size_t totalSize_m;
public:

	CMemoryBuf( size_t prealloc = 0 ) : basic_streambuf() {
		totalSize_m = 0;
		if ( prealloc > 0 ) {
			buf_m.resize( prealloc );
			setg( &buf_m.front(), &buf_m.front(), ( &buf_m.back() + 1 ) );
		}
		else
			setg( nullptr, nullptr, nullptr );
	}


protected:
	virtual	int_type CMemoryBuf::overflow( int_type __c ) {
		assert( 0 );
		return basic_streambuf::overflow( __c );
	}

};

#endif //BWT_RLE_CMEMORYBUF_H


