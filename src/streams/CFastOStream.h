//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFASTSTREAM_H
#define BWT_RLE_CFASTSTREAM_H


#include "CFastIStream.h"
#include "../CLogger.h"

class CFastOStream {
	CLogger* logger_m;
	size_t fromLastUpdate_m;
	constexpr static const size_t updateRate_m = 1024*50;
public:
	CFastOStream() : logger_m( nullptr ), fromLastUpdate_m( 0 ) { }
	virtual ~CFastOStream() {
		detachLogger();
	}

	virtual bool write( const char * data, size_t size ) = 0;
	virtual bool put( char c ) = 0;

	size_t put( CFastIStream& in ) {
		char buf[1024];
		size_t written = 0;
		size_t total = 0;
		while ( ( written = in.readsome( buf, 1024 ) ) > 0 ) {
			write( buf, written );
			total += written;
		}
		return written;
	}

	void attachLogger( CLogger* newLogger ) {
		logger_m = newLogger;
	}

	void detachLogger() {
		if ( logger_m )
			logger_m->updateOutput( fromLastUpdate_m );
		fromLastUpdate_m = 0;
	}
	virtual bool fail() const = 0;
protected:
	void inline update( size_t gain ) {
		if ( logger_m ) {
			fromLastUpdate_m += gain;
			if ( fromLastUpdate_m > updateRate_m ) {
				logger_m->updateOutput( fromLastUpdate_m );
				fromLastUpdate_m = 0;
			}
		}
	}
};


#endif //BWT_RLE_CFASTSTREAM_H
