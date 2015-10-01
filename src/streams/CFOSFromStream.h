//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFOSFROMSTREAM_H
#define BWT_RLE_CFOSFROMSTREAM_H


#include "CFastOStream.h"
#include <ostream>
using namespace std;

class CFOSFromStream : public CFastOStream {
protected:
	ostream& out_m;
public:
	CFOSFromStream( ostream& out ) : out_m( out ) { }

	virtual bool write( const char * data, size_t size ) override;

	virtual bool put( char c ) override;

	virtual bool fail() const override;
};


#endif //BWT_RLE_CFOSFROMSTREAM_H
