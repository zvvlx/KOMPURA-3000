/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KOMPURA3000AudioProcessorEditor::KOMPURA3000AudioProcessorEditor (KOMPURA3000AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 500);
}

KOMPURA3000AudioProcessorEditor::~KOMPURA3000AudioProcessorEditor()
{
}

//==============================================================================
void KOMPURA3000AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("KOMPURA-3000", getLocalBounds(), juce::Justification::centredTop, 1);
}

void KOMPURA3000AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
