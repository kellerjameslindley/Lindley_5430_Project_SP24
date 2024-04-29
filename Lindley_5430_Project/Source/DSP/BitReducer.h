/*
  ==============================================================================

    BitReducer.h
    Created: 11 Apr 2024 2:59:47am
    Author:  Keller Lindley

  ==============================================================================
*/

#pragma once
#include <vector>
#include <cmath>

class BitReducer {
public:
    
    void prepareToPlay(double sampleRate);
    
    
    void processBuffer(float * samples, const int numSamples, const int channel);
       
    float processSample(float x, int channel);

    void setFs(float Fs);
    float getFs();

    void setBitDepth(float bitDepth);
    float getBitDepth();

private:
    float Fs = 48000;
    float bitDepth = 10;
    
    float ampValues;
    float shrinkInput;
    float scaleInput;
    float roundInput;
    float prepOut;
    float y;
    
};
