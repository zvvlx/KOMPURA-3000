/*
  ==============================================================================

    CircularBuffer.h
    Created: 24 May 2022 4:20:59pm
    Author:  smauP

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class CircularBuffer {
public:
    CircularBuffer();
    CircularBuffer(int bufferSize, int delayLength);
    float getData();
    void setData(float data);
    void nextSample();
private:
    juce::AudioSampleBuffer buffer;
    int writeIndex;
    int readIndex;
    int delayLength;
};