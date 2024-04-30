/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./DSP/BitReducer.h"
#include "./DSP/DownSampler.h"
#include "./DSP/Filter.h"



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

    

    
    
//    juce::AudioProcessorValueTreeState apvts;
//    static const juce::StringRef bitDepthKnob;
//    static const juce::StringRef filterKnob;
//    static const juce::StringRef downSampleKnob;
//    static const juce::StringRef button;
//    
//    
//    void bitDepthKnobChanged(float value);
//    void filterKnobChanged(float value);
//    void downSampleKnobChanged(float value);
//    
//    
//    void buttonClicked(bool value);
//    
    
   
    
    float bitDepth;
    int rateDivisor;
    float filterCutoff;
    bool filterIsPost;
    
//private:
    
    //juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    
    
    
    BitReducer bitReduce;
    DownSampler downSample;
    Filter filter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lindley_5430_ProjectAudioProcessor)
    
    
};
