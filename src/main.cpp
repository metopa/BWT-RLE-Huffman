#include <iostream>
#include <stdlib.h>

#include "CCoder.h"
#include "exceptions.h"

using namespace std;

//TODO Inmemory
//TODO New sort
//TODO Exceptions

int main() {
	const char * iniFile = "settings.txt";
	string input1( "D:\\Sources\\C++\\BWT-RLE-Huffman\\examples\\code.data" );
	string input2( "D:\\Sources\\C++\\BWT-RLE-Huffman\\examples\\audio.data" );
	string encoded( "D:\\Sources\\C++\\BWT-RLE-Huffman\\examples\\encoded.brh" );
	string decoded( "D:\\Sources\\C++\\BWT-RLE-Huffman\\examples\\decoded.data" );
	/*ifstream settings( iniFile );
	if ( settings.is_open() ) {
		getline( settings, input );
		getline( settings, encoded );
		getline( settings, decoded );
	}
	else {
		cerr << "File settings.txt not found!\n";
		system("PAUSE");
		return -1;
	}
	if ( settings.fail() ) {
		cerr << "File settings.txt is corrupted!\n";
		system("PAUSE");
		return -1;
	}*/

	for ( int i = 0; i < 10; i++ ) {
		try {
			cout << "\rTest 1: run " << i + 1 << "/10";
			CCoder::encode( input1.c_str(), encoded.c_str() );
			CCoder::decode( encoded.c_str(), decoded.c_str() );

		}
		catch ( exceptions::fail& ) {
			cerr << "Unknown error" << endl;
		}


	}
	logger.benchmark();
	for ( int i = 0; i < 10; i++ ) {
		try {
			cout << "\rTest 2: run " << i + 1 << "/10";
			CCoder::encode( input2.c_str(), encoded.c_str() );
			CCoder::decode( encoded.c_str(), decoded.c_str() );

		}
		catch ( exceptions::fail& ) {
			cerr << "Unknown error" << endl;
		}


	}
	logger.benchmark();

	return 0;
}

