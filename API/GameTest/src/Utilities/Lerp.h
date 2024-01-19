#pragma once


float Lerp(float start, float end, float t)
{
    return start + t * (end - start);
}

static double CalculateTForSpeed(double currentT, double deltaTime, double lerpSpeed)
{
    double step = lerpSpeed * deltaTime;

    return (currentT + step);
}