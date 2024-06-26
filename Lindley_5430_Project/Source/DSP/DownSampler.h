/*
  ==============================================================================

    DownSampler.h
    Created: 11 Apr 2024 2:20:19am
    Author:  Keller Lindley

  ==============================================================================
*/

#pragma once
#include <vector>

class DownSampler {
 public:

    DownSampler () {};
    
    void processBuffer(float * samples, const int numSamples, const int channel);
       
    float processSample(float x, int channel);

    void setFs(float Fs);
    float getFs();



    void setRateDivisor(int rateDivisor);

 private:
    float Fs = 48000;
    float newFs = 24000;
    
    int rateDivisor = 10;
};

   
