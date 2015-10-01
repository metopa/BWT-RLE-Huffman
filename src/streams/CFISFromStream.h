//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFISFROMSTREAM_H
#define BWT_RLE_CFISFROMSTREAM_H

#include "CFastIStream.h"
#include <istream>
using namespace std;

class CFISFromStream : public CFastIStream {
protected:
	istream& in_m;

public:
	CFISFromStream( istream& in ) : in_m( in ) { }

	virtual bool fail() const override;

	virtual bool get( char& c ) override;

	virtual size_t readsome( char * buf, size_t size ) override;
};


#endif //BWT_RLE_CFISFROMSTREAM_H
