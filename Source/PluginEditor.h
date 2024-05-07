#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioPluginFadeInVolumeEffectAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    AudioPluginFadeInVolumeEffectAudioProcessorEditor (AudioPluginFadeInVolumeEffectAudioProcessor&);
    ~AudioPluginFadeInVolumeEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;

    AudioPluginFadeInVolumeEffectAudioProcessor& audioProcessor;
    juce::Slider durationSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginFadeInVolumeEffectAudioProcessorEditor)
};
