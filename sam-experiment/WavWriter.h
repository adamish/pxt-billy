#ifndef WAVWRITER_H
#define WAVWRITER_H

#include <iostream>
#include <string>
#include <fstream>

class WavWriter {
	std::ofstream out;
	int size;
	int sampleRate;
	void writeLittle2(int value);
	void writeLittle4(int value);
public:
	WavWriter();
	void init(std::string filename);
	void setSampleRate(int sampleRate);
	void write(char value);
	void close();
};

#endif
