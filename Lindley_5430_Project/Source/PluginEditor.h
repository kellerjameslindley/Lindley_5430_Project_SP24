/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Lindley_5430_ProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Lindley_5430_ProjectAudioProcessorEditor (Lindley_5430_ProjectAudioProcessor&);
    ~Lindley_5430_ProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Lindley_5430_ProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lindley_5430_ProjectAudioProcessorEditor)
};
