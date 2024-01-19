#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "../../../App/DataClasses.h"

#define PI 3.14159265358979323846 

class CParabolicArc
{
public:

    CParabolicArc(Vector2 startPos,  int resolution, float angle, float velocity, float gravity);

    Vector2 CalculateArcPoint(float t, float maxDistance, float radianAngle);
    std::vector<Vector2> GetArc();

    int mResolution;
    float mAngle;
    float mVelocity;
    float mGravity;

    Vector2 mStartPos;

};

