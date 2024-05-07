#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginFadeInVolumeEffectAudioProcessorEditor::AudioPluginFadeInVolumeEffectAudioProcessorEditor (AudioPluginFadeInVolumeEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

AudioPluginFadeInVolumeEffectAudioProcessorEditor::~AudioPluginFadeInVolumeEffectAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginFadeInVolumeEffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginFadeInVolumeEffectAudioProcessorEditor::resized()
{
}
