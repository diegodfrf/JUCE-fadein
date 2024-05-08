#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginFadeInVolumeEffectAudioProcessor::AudioPluginFadeInVolumeEffectAudioProcessor()
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

AudioPluginFadeInVolumeEffectAudioProcessor::~AudioPluginFadeInVolumeEffectAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginFadeInVolumeEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginFadeInVolumeEffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginFadeInVolumeEffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginFadeInVolumeEffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginFadeInVolumeEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginFadeInVolumeEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginFadeInVolumeEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginFadeInVolumeEffectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AudioPluginFadeInVolumeEffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void AudioPluginFadeInVolumeEffectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AudioPluginFadeInVolumeEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void AudioPluginFadeInVolumeEffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioPluginFadeInVolumeEffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AudioPluginFadeInVolumeEffectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto playHeadPosition = getPlayHead()->getPosition();

    if(!playHeadPosition->getIsPlaying()) return;

    auto samplesElapsed = playHeadPosition->getTimeInSamples();
    if(!samplesElapsed.hasValue()) return;

    if(expectedNextSamplePosition != (*samplesElapsed))
    {
        resetSmoothedValue(*samplesElapsed);
    }

    double gain = 0.0;
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        gain = smoothedGain.getNextValue();

        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            channelData[sample] *= gain;
        }
    }

    expectedNextSamplePosition = *samplesElapsed + buffer.getNumSamples();
}

//==============================================================================
bool AudioPluginFadeInVolumeEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginFadeInVolumeEffectAudioProcessor::createEditor()
{
    return new AudioPluginFadeInVolumeEffectAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginFadeInVolumeEffectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AudioPluginFadeInVolumeEffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void AudioPluginFadeInVolumeEffectAudioProcessor::updateFadein (double seconds)
{
    secondsFadein = seconds;
    resetSmoothedValue(expectedNextSamplePosition);
}

void AudioPluginFadeInVolumeEffectAudioProcessor::resetSmoothedValue(int64_t samplesElapsed)
{
    smoothedGain.reset(getSampleRate(), secondsFadein);
    smoothedGain.setCurrentAndTargetValue(0.0);
    smoothedGain.setTargetValue(1.0);
    smoothedGain.skip(samplesElapsed);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginFadeInVolumeEffectAudioProcessor();
}
