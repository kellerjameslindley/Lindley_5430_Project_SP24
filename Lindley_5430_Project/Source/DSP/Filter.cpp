/*
  ==============================================================================

    Filter.cpp
    Created: 29 Apr 2024 3:50:34pm
    Author:  Keller Lindley

  ==============================================================================
*/

#include "Filter.h"


// Define the functions of Filter
void Filter::processBuffer(float * samples, const int numSamples, const int channel)
{
    
    updateCoefficients();

    
    // Perform the processing
    for (int n = 0; n < numSamples ; n++){
        float x = samples[n];
        
        samples[n] = processSample(x,channel);
    }
}

float Filter::processSample(float x, int channel)
{
    // Output, processed sample (Direct Form 1)
    float y = (b0 / a0) * x + (b1 / a0) * x1[channel] + (b2 / a0) * x2[channel]
            + (-a1 / a0) * y1[channel] + (-a2 / a0) * y2[channel];

    x2[channel] = x1[channel]; // store delay samples for next process step
    x1[channel] = x;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
};

void Filter::setFs(float sampleRate)
{
    this->Fs = sampleRate;
    updateCoefficients();
};

float Filter::getFs()
{
    return Fs;
};

void Filter::setCutoff(float freq)
{
    
    this->freq = freq;

    // Use this to adjust for Bilinear Transform:
    //fc = (2.0f*Fs) * std::tan(fc/(Fs*2.0f)); //Frequency Warping

    w0 = (float) (2.0 * M_PI) * freq / Fs; // Normalize frequency

    // Bandwidth/slope/resonance parameter
    alpha = std::sin(w0) / (2.0f * Q);
    updateCoefficients();

};

float Filter::getCutoff()
{
    return freq;
};

void Filter::setQ(float Q)
{
    this->Q = Q;

    // Bandwidth/slope/resonance parameter
    alpha = std::sin(w0) / (2.0f * Q);
    updateCoefficients();

};

float Filter::getQ()
{
    return Q;
};

void Filter::setAmpdB(float ampdB)
{
    this->ampdB = ampdB;

    A = std::pow(10.0f, ampdB / 40.0f); // Linear amplitude
    updateCoefficients();

};

float Filter::getAmpdB()
{
    return ampdB;
    
};

void Filter::updateCoefficients()
{
  
        b0 = (1.0f - std::cos(w0)) / 2.0f;
        b1 = 1.0f - std::cos(w0);
        b2 = (1.0f - std::cos(w0)) / 2.0f;
        a0 = 1.0f + alpha;
        a1 = -2.0f * std::cos(w0);
        a2 = 1.0f - alpha;
       
};
