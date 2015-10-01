//
// Created by metopa on 30.08.2015.
//

#include "CCoder.h"
#include "bwt/CBwtEncoderBuf.h"
#include "rle/CRleEncoderBuf.h"
#include "rle/CRleDecoder.h"
#include "rle/CRleDecoderBuf.h"
#include "bwt/CBwtDecoder.h"
#include "bwt/CBwtDecoderBuf.h"
#include "CLogger.h"
#include "streams/CContainerBuf.h"
#include "huffman/CHuffmanEncoder.h"

using namespace std;

//TODO make args buffers

/**
 * Output structure
 * 	--------------------
 * 	data [compressed with RLE]
 * 	bwt_positions [uncompressed] (N * 4 bytes)
 * 	block_size (4 bytes)
 * 	last_block_size (4 bytes)
 * 	N (4 bytes)
 *  --------------------
 */

void CCoder::encode( const char * in, const char * out, size_t blockSize ) {
	ifstream inFile( in, ios::binary );
	ofstream outFile( out, ios::binary );
	if ( !inFile || !outFile )
		throw exceptions::fail();
	encode( inFile, outFile, blockSize );
}

void CCoder::encode( ifstream& in, ostream& out, size_t blockSize ) {
	logger.reset();
	logger.enableMaxPerformanceMode( true );
	logger.startExternalTimer();

	in.seekg( 0, in.end );
	size_t fileSize = (size_t) in.tellg();
	logger.setOriginalFileSize( fileSize );
	in.seekg( 0, in.beg );

	CFISFromStream encodeIn( in );
	CFOSFromStream encodeOut( out );

	encodeExternal( encodeIn, encodeOut, "D:\\bwt\\temp.bin", blockSize );

	logger.printStats( false );
}

void CCoder::encodeInMemory( CFastIStream& in, CFastOStream& out, size_t blockSize ) {

}

void CCoder::encodeExternal( CFastIStream& in, CFastOStream& out, const char * tempFile, size_t blockSize ) {
	fstream temp;
	temp.open( tempFile, ios::out | ios::binary | ios::trunc );
	if ( !temp.is_open() )
		throw exceptions::fail();


	CFOSFromStream tempStream( temp );
	in.attachLogger( &logger );
	tempStream.attachLogger( &logger );

	CBwtEncoder bwt( in, blockSize );
	CBwtEncoderBuf bwtBuf( bwt );
	CFISFromBuffer rleIn( bwtBuf );

	CRleEncoder rle( rleIn );
	CRleEncoderBuf rleBuf( rle, blockSize * blockSize );

	CFISFromBuffer rleStream( rleBuf );
	CFastOStream& hack = tempStream;
	hack.put( rleStream );

	CContainerBuf headerBuf( bwtBuf.getHeader() );
	CFISFromBuffer headerStream( headerBuf );
	hack.put( headerStream );

	in.detachLogger();
	tempStream.detachLogger();


	temp.close();
	temp.open( tempFile, ios::in | ios::binary );
	if ( !temp.is_open() )
		throw exceptions::fail();

	logger.startNewActivity( CLogger::HUFFMAN );

	CFISFromStream huffIn( temp );
	CHuffmanEncoder huffman( huffIn, out );
	huffman.generateTable( huffIn );

	temp.clear();
	logger.setFileSize( (size_t) temp.tellg() );
	temp.seekg( 0, temp.beg );

	huffIn.attachLogger( &logger );
	out.attachLogger( &logger );

	huffman.encode();

	huffIn.detachLogger();
	out.detachLogger();
	logger.finishActivity();


	temp.close();
	remove( tempFile );
}

//TODO Error handling

bool CCoder::decode( const char * in, const char * out ) {
	logger.reset();
	logger.enableMaxPerformanceMode( true );
	logger.startExternalTimer();

	ifstream inFile( in, ios::binary );
	CFISFromStream inStream( inFile );
	ofstream outFile( out, ios::binary );
	CFOSFromStream outStream( outFile );
	if ( !inFile || !outFile )
		throw exceptions::fail();

	inFile.seekg( 0, inFile.end );
	logger.setOriginalFileSize( (size_t) inFile.tellg() );
	inFile.seekg( 0, inFile.beg );

	bool rc = decodeExternal( inStream, outStream, "WlORUnZC.temp" );
	logger.printStats( true );
	return rc;
}


bool CCoder::decodeExternal( CFastIStream& in, CFastOStream& out, const char * tempFile ) {
	fstream temp;
	temp.open( tempFile, ios::out | ios::binary | ios::trunc );
	if ( !temp.is_open() )
		throw exceptions::fail();

	{
		CFOSFromStream tempOut( temp );
		in.attachLogger( &logger );
		tempOut.attachLogger( &logger );
		CHuffmanDecoder huffman( in, tempOut );
		logger.startNewActivity( CLogger::HUFFMAN );
		if ( !huffman.decode() )
			throw exceptions::fail();
		in.detachLogger();
		tempOut.detachLogger();
		logger.finishActivity();
	}

	temp.close();
	temp.open( tempFile, ios::in | ios::binary );

	if ( !temp.is_open() )
		throw exceptions::fail();

	bool rc = decodeRLE( temp, out );
	temp.close();
	remove( tempFile );
	return rc;
}


bool CCoder::decodeRLE( fstream& in, CFastOStream& out ) {
	uint32_t blockSize = 0;
	uint32_t lastBlockSize = 0;
	uint32_t blockCount = 0;
	in.seekg( -12, in.end );
	logger.setFileSize( (size_t) in.tellg() + 12 );

	in.read( (char *) &blockSize, 4 );
	in.read( (char *) &lastBlockSize, 4 );
	in.read( (char *) &blockCount, 4 );
	in.seekg( -12 - (int) blockCount * 4, in.end );

	vector<uint32_t> header;
	header.resize( blockCount, 0 );
	in.read( (char *) &header.front(), blockCount * 4 );

	if ( in.fail() )
		return false;

	logger.updateInput( blockCount * 4 + 12 );
	in.clear();
	in.seekg( 0, in.beg );
	CFISFromStream inStream( in );

	return decodeRLE( inStream, out, header, blockSize, lastBlockSize, blockCount );
}

bool CCoder::decodeRLE( CFastIStream& in, CFastOStream& out, vector<uint32_t>& positions,
						uint32_t blockSize, uint32_t lastBlockSize, uint32_t blockCount ) {
	CRleDecoder rle( in );
	CRleDecoderBuf rleBuf( rle, blockSize );

	CFISFromBuffer bwtIn( rleBuf );
	CBwtDecoder bwt( bwtIn, blockSize, lastBlockSize, blockCount );
	CBwtDecoderBuf bwtBuf( bwt, positions, blockSize );
	CFISFromBuffer bwtOut( bwtBuf );
	in.attachLogger( &logger );
	out.attachLogger( &logger );
	out.put( bwtOut );
	in.detachLogger();
	out.detachLogger();
	return true;
}
