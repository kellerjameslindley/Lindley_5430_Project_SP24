/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./DSP/BitReducer.h"
#include "./DSP/DownSampler.h"

//==============================================================================
/**
*/
class Lindley_5430_ProjectAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    Lindley_5430_ProjectAudioProcessor();
    ~Lindley_5430_ProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float bitDepth = 10.f;
    int rateDivisor = 10;

    
    
    using APVTS = juce::AudioProcessorValueTreeState;
    static APVTS::ParameterLayout createParameterLayout();
    
    APVTS apvts {*this, nullptr, "PARAMETERS", createParameterLayout()};
    
private:
    
    //juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    
    
    BitReducer bitReduce;
    DownSampler downSample;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lindley_5430_ProjectAudioProcessor)
    
    
};
