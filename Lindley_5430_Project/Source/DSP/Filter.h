/*
  ==============================================================================

    Filter.h
    Created: 29 Apr 2024 3:50:34pm
    Author:  Keller Lindley

  ==============================================================================
*/

#pragma once
#include <cmath>

class Filter {
 public:

    Filter() {};

    
    void processBuffer(float * samples, const int numSamples, const int channel);
            
    float processSample(float x, int channel);

    void setFs(float Fs);
    float getFs();

    void setCutoff(float freq);
    float getCutoff();

    void setQ(float Q);
    float getQ();

    void setAmpdB(float ampdB);
    float getAmpdB();

    

 private:
    float Fs = 48000.f;

    
    float x1[2] = { 0.0f }; // 1 sample of delay feedforward
    float x2[2] = { 0.0f }; // 2 samples of delay feedforward
    float y1[2] = { 0.0f }; // 1 sample of delay feedback
    float y2[2] = { 0.0f }; // 2 samples of delay feedback
    
    float freq = 500.f; // frequency in Hz
    float Q = 0.707f; // Q => [0.1 - 10]
    float ampdB = 0.0f; // Amplitude on dB scale
    
    float w0 = (float) (2.0 * M_PI) * freq / Fs; // Normalize frequency
    float alpha = std::sin(w0) / (2.0f * Q); // Bandwidth/slope/resonance parameter
    float A = std::pow(10.0f, ampdB / 40.0f); // Linear amplitude
    
    //filter coefficents
    float b0 = (1.0f - std::cos(w0)) / 2.0f;
    float b1 = 1.0f - std::cos(w0);
    float b2 = (1.0f - std::cos(w0)) / 2.0f;
    float a0 = 1.0f + alpha;
    float a1 = -2.0f * std::cos(w0);
    float a2 = 1.0f - alpha;
      
};

   
