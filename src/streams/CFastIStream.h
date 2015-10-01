//
// Created by metopa on 30.08.2015.
//

#ifndef BWT_RLE_CFASTISTREAM_H
#define BWT_RLE_CFASTISTREAM_H

#include <stddef.h>
#include "../CLogger.h"

class CFastIStream {
	CLogger* logger_m;
	size_t fromLastUpdate_m;
	constexpr static const size_t updateRate_m = 1024*50;
public:

	CFastIStream() : logger_m( nullptr ), fromLastUpdate_m( 0 ) { }
	virtual ~CFastIStream() {
		detachLogger();
	}
	virtual bool fail() const = 0;
	virtual bool get( char& c ) = 0;
	virtual size_t readsome( char * buf, size_t size ) = 0;
	void attachLogger( CLogger* newLogger ) {
		logger_m = newLogger;
	}
	void detachLogger() {
		if ( logger_m )
			logger_m->updateInput( fromLastUpdate_m );
		fromLastUpdate_m = 0;
	}
protected:
	void inline update( size_t gain ) {
		if ( logger_m ) {
			fromLastUpdate_m += gain;
			if ( fromLastUpdate_m > updateRate_m ) {
				logger_m->updateInput( fromLastUpdate_m );
				fromLastUpdate_m = 0;
			}
		}
	}
};

#endif //BWT_RLE_CFASTISTREAM_H
