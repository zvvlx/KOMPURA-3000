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
class KOMPURA3000AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KOMPURA3000AudioProcessorEditor (KOMPURA3000AudioProcessor&);
    ~KOMPURA3000AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KOMPURA3000AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KOMPURA3000AudioProcessorEditor)
};
