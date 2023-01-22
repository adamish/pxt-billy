#include "WavWriter.h"
#include <string>

WavWriter::WavWriter() {
	this->sampleRate = 2048;
}

void WavWriter::init(std::string filename) {
	out.open(filename, std::ios::binary);
	this->size = 0;

	/* Marks the file as a riff file. Characters are each 1 byte long. */
	char riff[4] = { 'R', 'I', 'F', 'F' };
	out.write(riff, 4);
	/*
	 * Size of the overall file - 8 bytes, in bytes (32-bit integer). Typically, you’d fill this in after creation.
	 */
	this->writeLittle4(0x12345678);
	/*
	 * File Type Header. For our purposes, it always equals “WAVE”.
	 */
	char wave[4] = { 'W', 'A', 'V', 'E' };
	out.write(wave, 4);
	/*
	 * Format chunk marker. Includes trailing null
	 */
	char fmt[4] = { 'f', 'm', 't', ' ' };
	out.write(fmt, 4);
	/*
	 * Length of format data as listed above
	 */
	this->writeLittle4(16);
	/**
	 * Type of format (1 is PCM) - 2 byte integer
	 */
	this->writeLittle2(1);
	/*
	 * Number of Channels - 2 byte integer
	 */
	this->writeLittle2(1);
	/**
	 * Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). Sample Rate = Number of Samples per second, or Hertz.
	 */
	this->writeLittle4(this->sampleRate);
	/*
	 * (Sample Rate * BitsPerSample * Channels) / 8.
	 */
	this->writeLittle4((this->sampleRate * 8 * 1) / 8);
	/*
	 * (BitsPerSample * Channels) / 8
	 */
	this->writeLittle2(1);
	/**
	 * Bits per sample
	 */
	this->writeLittle2(8);

	char data[4] = { 'd', 'a', 't', 'a' };
	out.write(data, 4);
	/*
	 * Size of the data section.
	 */
	this->writeLittle4(0xffffffff);
}

void WavWriter::writeLittle4(int value) {
	out.put(value & 0xff);
	out.put((value >> 8) & 0xff);
	out.put((value >> 16) & 0xff);
	out.put((value >> 24) & 0xff);
}
void WavWriter::writeLittle2(int value) {
	out.put(value & 0xff);
	out.put((value >> 8) & 0xff);
}
void WavWriter::write(char value) {
	out.put(value);
	this->size++;
}
void WavWriter::setSampleRate(int _sampleRate) {
	this->sampleRate = _sampleRate;
}
void WavWriter::close() {
	int fileSize = 44 - 8 + this->size;
	out.seekp(4);
	this->writeLittle4(fileSize);
	out.seekp(40);
	this->writeLittle4(this->size);
	out.close();
}
