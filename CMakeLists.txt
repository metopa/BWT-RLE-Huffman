cmake_minimum_required(VERSION 3.2)
project(BWT_RLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES
        src/bwt/CBwtEncoder.cpp
        src/bwt/CBwtEncoder.h
        src/bwt/CStringRotationOptimized.cpp
        src/bwt/CStringRotationOptimized.h
        src/bwt/CStringRotation.cpp
        src/bwt/CStringRotation.h
        src/main.cpp src/streams/CMemoryBuf.h src/exceptions.h)

add_executable(BWT_RLE ${SOURCE_FILES} src/rle/CRleEncoder.cpp src/rle/CRleEncoder.h src/CCoder.cpp src/CCoder.h src/bwt/CBwtEncoderBuf.cpp src/bwt/CBwtEncoderBuf.h src/streams/CFastOStream.h src/streams/CFOSFromStream.cpp src/streams/CFOSFromStream.h src/streams/CFOSFromBuffer.cpp src/streams/CFOSFromBuffer.h src/streams/CFastIStream.h src/streams/CFISFromStream.cpp src/streams/CFISFromStream.h src/streams/CFISFromBuffer.cpp src/streams/CFISFromBuffer.h src/faststreams.h src/bwt/CBwtDecoder.cpp src/bwt/CBwtDecoder.h src/streams/CContainerBuf.h src/rle/CRleDecoder.cpp src/rle/CRleDecoder.h src/rle/CRleEncoderBuf.cpp src/rle/CRleEncoderBuf.h src/bwt/CBwtDecoderBuf.cpp src/bwt/CBwtDecoderBuf.h src/rle/CRleDecoderBuf.cpp src/rle/CRleDecoderBuf.h src/CLogger.cpp src/CLogger.h src/huffman/CHuffmanEncoder.cpp src/huffman/CHuffmanEncoder.h src/huffman/CBits.cpp src/huffman/CBits.h src/huffman/CBitsOutbuf.cpp src/huffman/CBitsOutbuf.h src/huffman/CBitsIStream.cpp src/huffman/CBitsIStream.h src/huffman/CHuffmanDecoder.cpp src/huffman/CHuffmanDecoder.h src/huffman/CHuffmanTree.cpp src/huffman/CHuffmanTree.h)
