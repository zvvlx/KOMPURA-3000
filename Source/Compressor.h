/*
  ==============================================================================

    Compressor.h
    Created: 24 May 2022 4:18:31pm
    Author:  smauP

  ==============================================================================
*/

#include "CircularBuffer.h"
#pragma once

class Compressor {
public:
    Compressor();
    float compressSample(float data, float thresh, float ratio, float attack, float release, float knee, float gainParam);
    float interpolatePoints(float* xPoints, float* yPoints, float detectedValue);
private:
    CircularBuffer buffer;
    float tav, rms, gain;
};