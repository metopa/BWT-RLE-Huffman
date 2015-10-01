//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFOSFROMBUFFER_H
#define BWT_RLE_CFOSFROMBUFFER_H


#include "CFastOStream.h"
#include <streambuf>
using namespace std;

class CFOSFromBuffer : public CFastOStream {
protected:
	streambuf& out_m;
	bool fail_m;
public:
	CFOSFromBuffer( streambuf& out ) : out_m( out ), fail_m( false ) { }

	virtual bool write( const char * data, size_t size ) override;

	virtual bool put( char c ) override;

	virtual bool fail() const override;
};


#endif //BWT_RLE_CFOSFROMBUFFER_H
