/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class KOMPURA3000AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KOMPURA3000AudioProcessorEditor (KOMPURA3000AudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~KOMPURA3000AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void addSlider(juce::String name, juce::String labelText, juce::Slider& slider, juce::Label& label, std::unique_ptr<SliderAttachment>& attachment);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KOMPURA3000AudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& params;
    juce::Slider threshSlider, slopeSlider, kneeSlider, attackSlider, releaseSlider, gainSlider;
    juce::Label threshLabel, slopeLabel, kneeLabel, attackLabel, releaseLabel, gainLabel;
    std::unique_ptr<SliderAttachment> threshAttachment, slopeAttachment, kneeAttachment, attackAttachment, releaseAttachment, gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KOMPURA3000AudioProcessorEditor)
};
