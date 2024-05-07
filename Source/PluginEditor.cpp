#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginFadeInVolumeEffectAudioProcessorEditor::AudioPluginFadeInVolumeEffectAudioProcessorEditor (AudioPluginFadeInVolumeEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(200, 100);

    durationSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    durationSlider.setRange(0.0, 60, 0.1);
    durationSlider.setValue(5.0);
    durationSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 30);
    durationSlider.setTextValueSuffix(" Seconds");

    addAndMakeVisible(&durationSlider);

    durationSlider.addListener(this);
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
    g.drawFittedText("Fade-in Effect", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void AudioPluginFadeInVolumeEffectAudioProcessorEditor::resized()
{
    durationSlider.setBounds(30, 40, getWidth() - 60, 40);
}

void AudioPluginFadeInVolumeEffectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.updateFadein(durationSlider.getValue());
}
