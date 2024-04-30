/*
  ==============================================================================

    Filter.h
    Created: 29 Apr 2024 3:50:34pm
    Author:  Keller Lindley - Almost Entirely Based on Dr. Eric Tarr's Biquad Class

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
    
    float freq = 20000.f; // frequency in Hz
    float Q = 1.f; // Q => [0.1 - 10]
    float ampdB = 0.0f; // Amplitude on dB scale
    
    float w0 = (float) (2.0 * M_PI) * freq / Fs; // Normalize frequency
    float alpha = std::sin(w0) / (2.0f * Q); // Bandwidth/slope/resonance parameter
    float A = std::pow(10.0f, ampdB / 40.0f); // Linear amplitude
    
    // Filter coefficients
    float b0 = 1.0f; // initialized to pass signal
    float b1 = 0.0f; // without filtering
    float b2 = 0.0f;
    float a0 = 1.0f;
    float a1 = 0.0f;
    float a2 = 0.0f;
    
    void updateCoefficients();
};

   
