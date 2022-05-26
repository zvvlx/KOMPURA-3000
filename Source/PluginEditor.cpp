/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KOMPURA3000AudioProcessorEditor::KOMPURA3000AudioProcessorEditor (KOMPURA3000AudioProcessor& p, juce::AudioProcessorValueTreeState& state)
    : AudioProcessorEditor (&p), audioProcessor (p), params(state)
{
    addSlider("thresh", "Threshold (dB)", threshSlider, threshLabel, threshAttachment);
    addSlider("ratio", "Ratio (X:1)", slopeSlider, slopeLabel, slopeAttachment);
    addSlider("attack", "Attack (ms)", attackSlider, attackLabel, attackAttachment);
    addSlider("release", "Release (ms)", releaseSlider, releaseLabel, releaseAttachment);
    addSlider("gain", "Gain (dB)", gainSlider, gainLabel, gainAttachment);
    setSize (1450, 500);
    addAndMakeVisible(MeterLeft);
    addAndMakeVisible(MeterRight);

    startTimerHz(24);
}

KOMPURA3000AudioProcessorEditor::~KOMPURA3000AudioProcessorEditor()
{
}

//==============================================================================
void KOMPURA3000AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setFont(juce::Font("Aerial", 15.0f, juce::Font::plain));
    g.setColour (juce::Colours::white);
    g.setFont (40.0f);
    g.drawFittedText("KOMPURA-3000", getLocalBounds(), juce::Justification::centredTop, 1);
    g.setFont(20.0f);
    g.drawFittedText("Output volume levels", getLocalBounds(), juce::Justification::centred, 1);
}

void KOMPURA3000AudioProcessorEditor::resized()
{
    threshSlider.setBounds(50, 390, 200, 0);
    slopeSlider.setBounds(300, 390, 200, 0);
    attackSlider.setBounds(550, 390, 200, 0);
    releaseSlider.setBounds(800, 390, 200, 0);
    gainSlider.setBounds(1230, 390, 200, 0);

    threshSlider.setSize(180, 100);
    slopeSlider.setSize(180, 100);
    attackSlider.setSize(180, 100);
    releaseSlider.setSize(180, 100);
    gainSlider.setSize(180, 100);

    MeterLeft.setBounds(550, 180, 200, 15);
    MeterRight.setBounds(550, 200, 200, 15);
    MeterLeft.setSize(330, 10);
    MeterRight.setSize(330, 10);
}


void KOMPURA3000AudioProcessorEditor::addSlider(juce::String name, juce::String labelText, juce::Slider& slider, juce::Label& label, std::unique_ptr<SliderAttachment>& attachment) {
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    attachment.reset(new SliderAttachment(params, name, slider));

    label.setText(labelText, juce::dontSendNotification);

    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);
}

void KOMPURA3000AudioProcessorEditor::timerCallback() {
    MeterLeft.setLevel(audioProcessor.getRmsValue(0));
    MeterRight.setLevel(audioProcessor.getRmsValue(1));
    MeterLeft.repaint();
    MeterRight.repaint();
}
