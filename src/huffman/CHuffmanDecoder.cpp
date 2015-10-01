//
// Created by metopa on 07.09.2015.
//

#include "CHuffmanDecoder.h"
#include <bits/unique_ptr.h>
#include "CHuffmanTree.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

bool CHuffmanDecoder::decode() {
	unique_ptr<CNode> tree( CNode::deserialize( in_m ) );
	if ( !tree )
		return false;
	//tree->forEachChar( [&]( unsigned char c, CBits& bits ) { cout << c << " -> " << bits << endl; } );
	try {
		CBitsIStream bitsIn( in_m );
		while ( 1 )
			out_m.put( tree->walk( bitsIn ) );
	}
	catch ( exceptions::eof& ) {//TODO change exception
		return true;
	}
	catch ( exceptions::fail& ) {
		return false;
	}
}

#pragma clang diagnostic pop
