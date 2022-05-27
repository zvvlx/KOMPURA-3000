/*
  ==============================================================================

    Compressor.cpp
    Created: 24 May 2022 4:18:31pm
    Author:  smauP

  ==============================================================================
*/

#include "Compressor.h"

Compressor::Compressor()
{
    buffer = CircularBuffer(150, 20);
    tav = 0.01;
    rms = 0;
    gain = 1;
}

float Compressor::compressSample(float data, float thresh, float ratio, float attack, float release, float knee, float gainParam)
{
    rms = (1 - tav) * rms + tav * std::pow(data, 2.0f);
    float dbRMS = 10 * std::log10(rms);

    float slope = 1 - (1 / ratio);
    float dbGain = std::min(0.0f, (slope * (thresh - dbRMS)));
    float newGain = std::pow(10, dbGain / 20);

    float coeff;
    if (newGain < gain) coeff = attack;
    else coeff = release;
    gainParam = pow(10, gainParam / 20);
    gain = (1 - coeff) * gain + coeff * newGain * gainParam;

    float compressedSample = gain * buffer.getData();
    buffer.setData(data);
    buffer.nextSample();
    return compressedSample;
}
