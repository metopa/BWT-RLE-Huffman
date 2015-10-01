//
// Created by metopa on 02.09.2015.
//

#ifndef BWT_RLE_CLOGGER_H
#define BWT_RLE_CLOGGER_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <stack>
#include <vector>

using namespace std;
using namespace chrono;

class CLogger {
public:
	enum EActivity {
		BWT, RLE, HUFFMAN, EA_MAX_ENUM
	};

	void benchmark();

private:
	ostream * logStream_m;

	high_resolution_clock::duration timers_m[EA_MAX_ENUM];
	high_resolution_clock::time_point currentTimer_m;
	high_resolution_clock::time_point externalTimer_m;
	high_resolution_clock::time_point lastRefresh_m;

	stack<EActivity> currentActivity_m;

	unsigned int refreshRate_m;
	bool maxPerformance_m;
	bool firstLoop_m;

	size_t originalSize_m;
	size_t totalSize_m;
	size_t compressedSize_m;
	size_t currentSize_m;

	vector<high_resolution_clock::duration> benchmark_m[4][2];

public:
	CLogger( ostream * logStream = &cout, unsigned int refreshRate = 100 ) :
			logStream_m( logStream ), refreshRate_m( refreshRate ) {
		reset();
		*logStream << fixed;
	}

	void startExternalTimer();

	void startNewActivity( EActivity a, bool verbose = false, const char * msg = nullptr );

	void finishActivity();

	void updateInput( size_t gain );

	void updateOutput( size_t gain );

	void reset();

	void printStats( bool decompression );

	void refresh();

	void nicePrint();

	void enableMaxPerformanceMode( bool set );

	void setOriginalFileSize( size_t size );

	void setFileSize( size_t size );

private:
	void printSize( size_t size, bool allign );

	void printSizeNum( size_t size );

	const char * toString( EActivity a );

	void logBenchmark( bool decompression );
};

extern CLogger logger;


#endif //BWT_RLE_CLOGGER_H
