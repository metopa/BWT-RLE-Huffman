//
// Created by metopa on 05.09.2015.
//


#include "CHuffmanEncoder.h"
#include <cstring>
#include <vector>
#include <algorithm>
#include <bits/unique_ptr.h>
#include <iostream>
#include "CBitsOutbuf.h"

CHuffmanEncoder::CHuffmanEncoder( CFastIStream& in, CFastOStream& out ) : in_m( in ), out_m( out ) {}

void CHuffmanEncoder::generateTable( CFastIStream& in ) {
	memset( freq_m, '\0', 256 * sizeof( size_t ) );
	getFreq( in );

	unique_ptr<CNode> tree ( makeTree() );
	tree->serialize( out_m );
	makeDictionary( tree.get() );
	//tree->forEachChar( [&]( unsigned char c, CBits& bits ) { cout << c << " -> " << bits << endl; } );
}

void CHuffmanEncoder::encode() {
	CBitsOutbuf bitsOut( out_m );
	char c;
	while ( in_m.get( c ) ) {//TODO Optimize
		bitsOut << dict_m[(unsigned char)c];
	}
}

void CHuffmanEncoder::getFreq( CFastIStream& in ) {
	char c;
	while ( in.get( c ) ) { //TODO Optimize
		freq_m[(unsigned char)c]++;
	}
}

CNode * CHuffmanEncoder::makeTree() {
	vector<CNode*> heap;
	auto heapComp = []( CNode * a, CNode * b ) -> bool {
		return a->getWeight() > b->getWeight();
	};
	make_heap( heap.begin(), heap.end(), heapComp );
	for ( int i = 0; i < 256; i++ )
		if ( freq_m[i] ) {
			heap.push_back( new COuterNode( (unsigned char) i, freq_m[i] ) );
			push_heap( heap.begin(), heap.end(), heapComp );
		}

	if ( heap.empty() )
		return nullptr;

	while ( heap.size() > 1 ) {
		pop_heap( heap.begin(), heap.end(), heapComp );
		CNode * first = heap.back();
		heap.pop_back();

		pop_heap( heap.begin(), heap.end(), heapComp );
		CNode * second = heap.back();
		heap.pop_back();

		heap.push_back( new CNode( first, second ) );
		push_heap( heap.begin(), heap.end(), heapComp );
	}
	return heap[0];
}

void CHuffmanEncoder::makeDictionary( CNode * tree ) {
	tree->forEachChar( [&]( unsigned char c, CBits& bits ) { dict_m[c] = bits; } );
}




