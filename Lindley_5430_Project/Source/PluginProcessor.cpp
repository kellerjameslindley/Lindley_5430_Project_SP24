/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Lindley_5430_ProjectAudioProcessor::Lindley_5430_ProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{


    
    
}

Lindley_5430_ProjectAudioProcessor::~Lindley_5430_ProjectAudioProcessor()
{
    


    
}



void Lindley_5430_ProjectAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
  
}



//==============================================================================
const juce::String Lindley_5430_ProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Lindley_5430_ProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Lindley_5430_ProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Lindley_5430_ProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Lindley_5430_ProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Lindley_5430_ProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Lindley_5430_ProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Lindley_5430_ProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Lindley_5430_ProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void Lindley_5430_ProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Lindley_5430_ProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    bitReduce.setFs(sampleRate);
    bitReduce.setBitDepth(bitDepth);
    
    filter.setFs(sampleRate);
    filter.setCutoff(filterCutoff);
    
    downSample.setFs(sampleRate);
    downSample.setRateDivisor(rateDivisor);
    
    
}

void Lindley_5430_ProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Lindley_5430_ProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Lindley_5430_ProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    auto numSamples = buffer.getNumSamples();
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            
            auto* channelData = buffer.getWritePointer (channel);
            bitReduce.processBuffer(channelData, numSamples, channel);
            filter.processBuffer(channelData, numSamples, channel);
            downSample.processBuffer(channelData, numSamples, channel);

        }
    
      buffer.copyFrom(0, 0, buffer, 0, 0, numSamples);
      buffer.copyFrom(1, 0, buffer, 1, 0, numSamples);
    
  

    
    
}

//==============================================================================
bool Lindley_5430_ProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Lindley_5430_ProjectAudioProcessor::createEditor()
{
    return new Lindley_5430_ProjectAudioProcessorEditor (*this);
}

//==============================================================================
void Lindley_5430_ProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, false);
}

void Lindley_5430_ProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
  
        
       
    
    
    
}

juce::AudioProcessorValueTreeState::ParameterLayout Lindley_5430_ProjectAudioProcessor::createParameterLayout()
{
    
    APVTS::ParameterLayout layout;
    
    using namespace juce;
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID("BitDepth", 1),
                                                    "BitDepth",
                                                    NormalisableRange<float>(2, 24, 1, 1),
                                                    24));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID("Threshold", 1),
                                                    "Threshold",
                                                    NormalisableRange<float>(-60, 12, 1, 1),
                                                    0));
    
    auto attackReleaseRange = NormalisableRange<float>(5, 500, 1, 1);
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID("Attack", 1),
                                                    "Attack",
                                                    attackReleaseRange,
                                                    50));
    
    layout.add(std::make_unique<AudioParameterFloat>(juce::ParameterID("Release", 1),
                                                    "Release",
                                                    attackReleaseRange,
                                                    250));
    
    auto ratioChoices = std::vector<double>{1, 1.5, 2, 4, 8, 20};
    juce::StringArray ratioChoicesArray;
    
    for (auto ratioChoice : ratioChoices )
    {
        ratioChoicesArray.add(juce::String(ratioChoice, 1));
    }

    layout.add(std::make_unique<AudioParameterChoice>(juce::ParameterID("Ratio", 1),
                                                     "Ratio",
                                                     ratioChoicesArray,
                                                      3));
    
    return layout;
    
   
}
    
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Lindley_5430_ProjectAudioProcessor();
}
