//
// Created by metopa on 07.09.2015.
//

#include "CHuffmanTree.h"
#include <bits/unique_ptr.h>

CNode::CNode( size_t weight, ptr_type left_, ptr_type right_ ) {
	left() = left_;
	right() = right_;
	weight_m = weight;
}

CNode::CNode( ptr_type first, ptr_type second ) {
	left() = first;
	right() = second;
	weight_m = first->getWeight() + second->getWeight();
}

CNode::~CNode() {
	delete left();
	delete right();
}

COuterNode::COuterNode( unsigned char c, size_t weight, ptr_type left, ptr_type right )
		: CNode( weight, left, right ), c_m( c ) {}

void CNode::forEach( CBits& path, const function<void( unsigned char, CBits& )>& op ) const {
	path.append_0();
	left()->forEach( path, op );
	path.shrink();
	path.append_1();
	right()->forEach( path, op );
	path.shrink();
}

void COuterNode::forEach( CBits& path, const function<void( unsigned char, CBits& )>& op ) const {
	op( c_m, path );
}

void CNode::serialize( CFastOStream& out, unsigned char depth ) const {
	left()->serialize( out, (unsigned char) ( depth + 1 ) );
	right()->serialize( out, (unsigned char) ( depth + 1 ) );
}

void COuterNode::serialize( CFastOStream& out, unsigned char depth ) const {
	out.put( depth );
	out.put( c_m );
}

CNode::ptr_type CNode::deserialize( CFastIStream& in, int currentDepth, int& newDepth ) {
	unique_ptr<CNode> node;
	if ( newDepth == -1 ) {
		newDepth = 0;
		if ( !in.get( (char&) newDepth ) )
			return nullptr;
	}
	if ( currentDepth == newDepth ) {
		unsigned char c = 0;
		if ( !in.get( (char&) c ) )
			return nullptr;
		node.reset( new COuterNode( c ) );
		newDepth = -1;
	}
	else if ( currentDepth > newDepth ) {
		return nullptr;
	}
	else {
		node.reset( new CNode() );
		node->left() = deserialize( in, currentDepth + 1, newDepth );
		if ( newDepth == -1 ) {
			newDepth = 0;
			if ( !in.get( (char&) newDepth ) ) {
				return nullptr;
			}
		}
		node->right() = deserialize( in, currentDepth + 1, newDepth );
		if ( !node->left() || !node->right() ) {
			return nullptr;
		}
	}

	return node.release();
}

unsigned char CNode::walk( CBitsIStream& in ) const {
	return children_m[( in.getNextBit() != 0 )]->walk( in );
}

unsigned char COuterNode::walk( CBitsIStream& in ) const {
	return c_m;
}

void CNode::forEachChar( const function<void( unsigned char, CBits& )>& op ) const {
	CBits b;
	forEach( b, op );
}

CNode::ptr_type CNode::deserialize( CFastIStream& in ) {
	int depth = -1;
	return deserialize( in, 0, depth );
}
