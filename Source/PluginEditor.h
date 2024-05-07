#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioPluginFadeInVolumeEffectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AudioPluginFadeInVolumeEffectAudioProcessorEditor (AudioPluginFadeInVolumeEffectAudioProcessor&);
    ~AudioPluginFadeInVolumeEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AudioPluginFadeInVolumeEffectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginFadeInVolumeEffectAudioProcessorEditor)
};
