//
// Created by metopa on 02.09.2015.
//


#include "CLogger.h"
#include <algorithm>
#include <cstring>

long long int millisecondsFrom( const high_resolution_clock::time_point& t ) {
	return duration_cast<milliseconds>( high_resolution_clock::now() - t ).count();
}

ostream& operator<< ( ostream& out, const high_resolution_clock::duration& t ) {
	/*auto us = duration_cast<microseconds>( t ).count();
	auto ms = us / 1000;
	us %= 1000;
	if ( ms > 1000 )
		out << ( ms / 1000 ) << "s " << ( ms % 1000 ) << "ms";
	else
		out << ms << '.' << us << "ms";*/
	out << duration_cast<microseconds>( t ).count();
	return out;
}

const char * CLogger::toString( EActivity a ) {
	switch ( a ) {
		case BWT:
			return "BWT";
		case RLE:
			return "RLE";
		case HUFFMAN:
			return "Huffman";
		default:
			return "NONE";
	}
}

void CLogger::startNewActivity( EActivity a, bool verbose, const char * msg) {
	if ( !currentActivity_m.empty() ) {
		timers_m[currentActivity_m.top()] += high_resolution_clock::now() - currentTimer_m;
	}
	currentActivity_m.push( a );
	if ( verbose ) {
		*logStream_m << "Started activity " << toString( a );
		if ( msg )
			*logStream_m << " (" << msg << ')' << endl;
	}
	currentTimer_m = high_resolution_clock::now();
}

void CLogger::finishActivity() {
	high_resolution_clock::duration d;
	d = high_resolution_clock::now() - currentTimer_m;
	timers_m[currentActivity_m.top()] += d;

	refresh();

	currentActivity_m.pop();
	currentTimer_m = high_resolution_clock::now();
}

void CLogger::reset() {
	memset( timers_m, 0, sizeof( timers_m ) );
	totalSize_m = 0;
	compressedSize_m = 0;
	currentSize_m = 0;
	firstLoop_m = true;
	enableMaxPerformanceMode( false );
}

void CLogger::printStats( bool decompression ) {
	logBenchmark( decompression );
	return;
	nicePrint();

	*logStream_m << "\nTotal time: " << ( high_resolution_clock::now() - externalTimer_m ) << endl;
	for ( int i = 0; i < EA_MAX_ENUM; i++ ) {
		*logStream_m << toString( (EActivity) i ) << " time: " << timers_m[i] << endl;
	}

	*logStream_m <<   "Original size: ";
	printSize( originalSize_m, false);
	*logStream_m << "\nNew size:      ";
	printSize( compressedSize_m, false);
	*logStream_m << endl;
	if ( originalSize_m ) {
		if ( decompression )
			*logStream_m << "Decompression ratio: " << setprecision( 2 )
			<< ( (double)originalSize_m / compressedSize_m * 100 ) << '%' << endl;
		else
			*logStream_m << "Compression ratio: " << setprecision( 2 )
			<< ( (double)compressedSize_m / originalSize_m * 100 ) << '%' << endl;
	}
	*logStream_m << "----------------------------------------------------------------------" << endl;
}

void CLogger::nicePrint() {
	int percents;
	if ( totalSize_m )
	 	percents = (int) ( (unsigned long long int)currentSize_m * 100 / totalSize_m );
	else
		percents = -1;

	*logStream_m << '\r' << "                                                                               " << '\r';
	if ( percents >= 0 )
		*logStream_m << setw( 3 ) << percents << "% ";

	printSize( currentSize_m, true );
	if ( totalSize_m ) {
		*logStream_m << '/';
		printSize( totalSize_m, false );
	}
	*logStream_m << ' ';
	unsigned int speed = 0;
	auto d = millisecondsFrom( externalTimer_m );
	if ( d != 0 )
		speed = (unsigned int) ( (unsigned long long int)currentSize_m * 1000 / d );

	printSize( speed, true );
	*logStream_m << "/s ";
	for ( int i = 0; i < percents / 2; i++ )
		*logStream_m << '#';
}

void CLogger::refresh() {
	if ( maxPerformance_m )
		return;
	if ( firstLoop_m || millisecondsFrom( lastRefresh_m ) >= refreshRate_m ) {
		firstLoop_m = false;
		lastRefresh_m = high_resolution_clock::now();
		nicePrint();
	}
}

void CLogger::printSizeNum( size_t size ) {
	if ( size < 1024 * 10 )
		*logStream_m << setprecision( 2 ) << (double)size / 1024;
	else if ( size < 1024 * 100 )
		*logStream_m << setprecision( 1 ) << ( (double)size ) / 1024;
	else
		*logStream_m << size / 1024;
}

void CLogger::printSize( size_t size, bool allign ) {
	if ( allign )
		*logStream_m << setw( 4 );
	if ( size < 1024 ) {
		*logStream_m << size << "b ";
		return;
	}
	if ( size < 1024 * 1024  ) {
		printSizeNum( size );
		*logStream_m << "Kb";
		return;
	}
	size /= 1024;
	if ( size < 1024 * 1024 ) {
		printSizeNum( size );
		*logStream_m << "Mb";
		return;
	}
	size /= 1024;
	printSizeNum( size );
	*logStream_m << "Gb";
	return;
}

void CLogger::startExternalTimer() {
	externalTimer_m = high_resolution_clock::now();
}

void CLogger::setOriginalFileSize( size_t size ) {
	originalSize_m = size;
	setFileSize( size );
}

void CLogger::setFileSize( size_t size ) {
	totalSize_m = size;
	currentSize_m = compressedSize_m = 0;
}

CLogger logger;

void CLogger::enableMaxPerformanceMode( bool set ) {
	maxPerformance_m = set;
}

void CLogger::updateInput( size_t gain ) {
	currentSize_m += gain;
	refresh();
}

void CLogger::updateOutput( size_t gain ) {
	compressedSize_m += gain;
	refresh();
}

void CLogger::benchmark() {
	cout << endl;
	for ( int d = 0; d < 2; d++ ) {
		for ( int i = 0; i < 4; i++ ) {
			vector<high_resolution_clock::duration> &current = benchmark_m[i][d];
			sort( current.begin(), current.end() );
			cout << current[current.size()/2] << endl;
		}
		cout << endl;
	}
}

void CLogger::logBenchmark( bool decompression ) {
	for ( int i = 0; i < 3; i++ )
		benchmark_m[i][decompression].push_back(timers_m[i] );
	benchmark_m[3][decompression].push_back( high_resolution_clock::now() - externalTimer_m );
}
