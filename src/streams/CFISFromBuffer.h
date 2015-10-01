//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFISFROMBUFFER_H
#define BWT_RLE_CFISFROMBUFFER_H


#include "CFastIStream.h"
#include <streambuf>
using namespace std;

class CFISFromBuffer : public CFastIStream {
protected:
	streambuf& in_m;
	bool fail_m;

public:
	CFISFromBuffer( streambuf& in ) : in_m( in ), fail_m( false ) { }

	virtual bool fail() const override;

	virtual bool get( char& c ) override;

	virtual size_t readsome( char * buf, size_t size ) override;
};


#endif //BWT_RLE_CFISFROMBUFFER_H
