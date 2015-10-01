//
// Created by metopa on 07.09.2015.
//

#ifndef BWT_RLE_CHUFFMANTREE_H
#define BWT_RLE_CHUFFMANTREE_H

#include <cstdint>
#include <ostream>
#include <functional>
#include "CBits.h"
#include "CBitsIStream.h"
#include "../streams/CFastIStream.h"
#include "../streams/CFastOStream.h"

using namespace std;

class CNode {
protected:
	typedef CNode * ptr_type;
	ptr_type children_m[2];
	size_t weight_m;

	ptr_type& left() { return children_m[0]; }
	ptr_type left() const { return children_m[0]; }
	ptr_type& right() { return children_m[1]; }
	ptr_type right() const { return children_m[1]; }

public:
	CNode( size_t weight = 0, ptr_type left = nullptr, ptr_type right = nullptr );

	CNode( ptr_type first, ptr_type second );

	virtual ~CNode();

	static ptr_type deserialize( CFastIStream& in );

	void forEachChar( const function<void( unsigned char, CBits& )>& op ) const;

	virtual void serialize( CFastOStream& out, unsigned char depth = 0 ) const;

	virtual unsigned char walk( CBitsIStream& in ) const;

	size_t getWeight() const { return weight_m; }

protected:
	static ptr_type deserialize( CFastIStream& in, int currentDepth, int& newDepth );

	virtual void forEach( CBits& path, const function<void( unsigned char, CBits& )>& op ) const;
};

class COuterNode : public CNode {
	unsigned char c_m;

public:
	COuterNode( unsigned char c, size_t weight = 0, ptr_type left = nullptr, ptr_type right = nullptr );

	virtual void serialize( CFastOStream& out, unsigned char depth = 0 ) const override;

	virtual unsigned char walk( CBitsIStream& in ) const override;

protected:

	virtual void forEach( CBits& path, const function<void( unsigned char, CBits& )>& op ) const override;
};


#endif //BWT_RLE_CHUFFMANTREE_H
