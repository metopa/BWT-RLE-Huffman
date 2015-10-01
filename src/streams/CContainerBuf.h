//
// Created by metopa on 01.09.2015.
//

#ifndef BWT_RLE_CVECTORBUF_H
#define BWT_RLE_CVECTORBUF_H

#include <streambuf>

using namespace std;

class CContainerBuf : public streambuf {

public:
	template<class sequence_container>
	CContainerBuf( const sequence_container& c ) : basic_streambuf() {
		setg( (char*)&c[0], (char*)&c[0], (char*)(&c.back() + 1) );
	}

	template <class pointer>
	CContainerBuf( const pointer& begin, const pointer& end ) : basic_streambuf()  {
		setg( (char*)begin, (char*)begin, (char*)end );
	}
};


#endif //BWT_RLE_CVECTORBUF_H
