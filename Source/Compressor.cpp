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

    if (knee > 0 && dbRMS > (thresh - knee / 2.0) && dbRMS < (thresh + knee / 2.0)) {
        float kneeBottom = thresh - knee / 2.0, kneeTop = thresh + knee / 2.0;
        float xPoints[2], yPoints[2];
        xPoints[0] = kneeBottom;
        xPoints[1] = kneeTop;
        xPoints[1] = std::fmin(0.0f, kneeTop);
        yPoints[0] = 0.0f;
        yPoints[1] = slope;
        slope = interpolatePoints(&xPoints[0], &yPoints[0], thresh);
        thresh = kneeBottom;
    }

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

float Compressor::interpolatePoints(float* xPoints, float* yPoints, float detectedValue) {
    float result = 0.0f;
    int n = 2;

    for (int i = 0; i < n; i++)
    {
        float term = 1.0f;
        for (int j = 0; j < n; j++)
        {
            if (j != i) {
                term *= (detectedValue - xPoints[j]) / (xPoints[i] - xPoints[j]);
            }
        }
        result += term * yPoints[i];
    }

    return result;

}
