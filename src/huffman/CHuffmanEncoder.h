//
// Created by metopa on 05.09.2015.
//

#ifndef BWT_RLE_CHUFFMANDECODE_H
#define BWT_RLE_CHUFFMANDECODE_H

#include "CBits.h"
#include "CHuffmanTree.h"
#include "../streams/CFastIStream.h"
#include "../streams/CFastOStream.h"

using namespace std;

class CHuffmanEncoder {
	CFastIStream& in_m;
	CFastOStream& out_m;
	size_t freq_m[256];
	CBits dict_m[256];
public:
	CHuffmanEncoder( CFastIStream& in, CFastOStream& out );

	void encode();

	void generateTable( CFastIStream& in );

private:
	void getFreq( CFastIStream& in);

	CNode * makeTree();

	void makeDictionary( CNode * tree );
};


#endif //BWT_RLE_CHUFFMANDECODE_H
