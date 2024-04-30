/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lindley_5430_ProjectAudioProcessorEditor::Lindley_5430_ProjectAudioProcessorEditor (Lindley_5430_ProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    cutoffSlider.setBounds(10, 30, 100, 100);
    cutoffSlider.setRange(20, 20000);
    cutoffSlider.setSkewFactorFromMidPoint(1000);
    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(cutoffSlider);
    cutoffSlider.addListener(this);
    cutoffSlider.setValue(20000);
    addAndMakeVisible(freqLabel);
    freqLabel.setText("LPF Frequency", juce::dontSendNotification);
    freqLabel.attachToComponent(&cutoffSlider, false);
    freqLabel.setJustificationType(juce::Justification::centred);

    
    
    rateDivisorSlider.setBounds(210, 30, 100, 100);
    rateDivisorSlider.setRange(1, 100);
    //rateDivisorSlider.setSkewFactorFromMidPoint();
    rateDivisorSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateDivisorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(rateDivisorSlider);
    rateDivisorSlider.addListener(this);
    addAndMakeVisible(downSampleLabel);
    downSampleLabel.setText("Downsample", juce::dontSendNotification);
    downSampleLabel.attachToComponent(&rateDivisorSlider, false);
    downSampleLabel.setJustificationType(juce::Justification::centred);
    
    bitDepthSlider.setBounds(110, 30, 100, 100);
    bitDepthSlider.setRange(1, 24);
    bitDepthSlider.setSkewFactorFromMidPoint(8);
    bitDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    bitDepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    addAndMakeVisible(bitDepthSlider);
    bitDepthSlider.addListener(this);
    bitDepthSlider.setValue(24);
    addAndMakeVisible(bitDepthLabel);
    bitDepthLabel.setText("Bit Depth", juce::dontSendNotification);
    bitDepthLabel.attachToComponent(&bitDepthSlider, false);
    bitDepthLabel.setJustificationType(juce::Justification::centred);


    filterPost.setBounds(180, 150, 50, 50);
    addAndMakeVisible(filterPost);
    filterPost.setButtonText("Filter Post");
    filterPost.setClickingTogglesState(true);
    filterPost.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::peru);
    filterPost.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::grey);
    filterPost.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::whitesmoke);
    filterPost.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::whitesmoke);
    checkButton();
    



    
    
}

Lindley_5430_ProjectAudioProcessorEditor::~Lindley_5430_ProjectAudioProcessorEditor()
{
}

//==============================================================================
void Lindley_5430_ProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::turquoise);
    
    

   
}

void Lindley_5430_ProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void Lindley_5430_ProjectAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider ==&cutoffSlider ){
        audioProcessor.filterCutoff = cutoffSlider.getValue();
    }
    if (slider ==&rateDivisorSlider ){
        audioProcessor.rateDivisor = rateDivisorSlider.getValue();
    }
    if (slider ==&bitDepthSlider ){
        audioProcessor.bitDepth = bitDepthSlider.getValue();
    }
    
}

void Lindley_5430_ProjectAudioProcessorEditor::checkButton()
{
        audioProcessor.filterIsPost = filterPost.getToggleState();
    
}
