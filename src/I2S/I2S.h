/*
	Author: bitluni 2019
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://youtube.com/bitlunislab
		https://github.com/bitluni
		http://bitluni.net
*/
#pragma once

#include "DMABufferDescriptor.h"

class I2S
{
  public:
	int i2sIndex;
	void* interruptHandle;
	int dmaBufferDescriptorCount;
	int dmaBufferDescriptorActive;
	DMABufferDescriptor *dmaBufferDescriptors;
	volatile bool stopSignal;

	/// hardware index [0, 1]
	I2S(const int i2sIndex = 0);
	void reset();

	void stop();

	void i2sStop();
	void startTX();
	void startRX();

	void resetDMA();
	void resetFIFO();
	bool initParallelOutputMode(const int *pinMap, long APLLFreq = 1000000, const int bitCount = 8, int wordSelect = -1, int baseClock = -1);
	bool initSerialOutputMode(int dataPin, const int bitCount = 8, int wordSelect = -1, int baseClock = -1, long sampleRate = -1);
	bool initParallelInputMode(const int *pinMap, long sampleRate = 1000000, const int bitCount = 8, int wordSelect = -1, int baseClock = -1);
	void enableDAC(int selectedDACs = 1);

	virtual DMABufferDescriptor *firstDescriptorAddress() const;

	void allocateDMABuffers(int count, int bytes);
	void deleteDMABuffers();
	virtual void getClockSetting(long *sampleRate, int *n, int *a, int *b, int *div);

	void (*interruptStaticChild)(void *arg) = 0;

  protected:
	virtual bool useInterrupt();
	void setAPLLClock(long sampleRate, int bitCount);
	void setClock(long sampleRate, int bitCount, bool useAPLL = true);
	
  private:
	static void IRAM_ATTR interruptStatic(void *arg);
};
