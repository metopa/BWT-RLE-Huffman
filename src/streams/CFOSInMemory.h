//
// Created by metopa on 05.10.2015.
//

#ifndef BWT_RLE_CFOSINMEMORY_H
#define BWT_RLE_CFOSINMEMORY_H


#include "CFastOStream.h"
#include <string>

using namespace std;

class CFOSInMemory : public CFastOStream {
	string buf_m;
public:

	CFOSInMemory( size_t prealloc = 1 ) {
		if ( prealloc > 0 )
			buf_m.reserve( prealloc );
	}

	virtual bool write( const char * data, size_t size );

	virtual bool put( char c );

	virtual bool fail() const;

	virtual string& getBuffer() { return buf_m; }
};


#endif //BWT_RLE_CFOSINMEMORY_H
