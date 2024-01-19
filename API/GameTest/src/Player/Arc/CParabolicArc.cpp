#include "CParabolicArc.h"


CParabolicArc::CParabolicArc(Vector2 startPos, int resolution, float angle, float velocity, float gravity) :
	mStartPos{ startPos }, mResolution{ resolution }, mAngle{ angle }, mVelocity{ velocity }, mGravity{ gravity }
{

}

Vector2 CParabolicArc::CalculateArcPoint(float t, float maxDistance, float radianAngle)
{
	float x = t * maxDistance;
	float y = x * tan(radianAngle) - ((mGravity * x * x) / (2 * mVelocity * mVelocity * cos(radianAngle) * cos(radianAngle)));

	return Vector2(x + mStartPos.x, y + mStartPos.y);
}

std::vector<Vector2> CParabolicArc::GetArc()
{
	std::vector<Vector2> arcArray(mResolution + 1);

	float radianAngle = PI / 180.0f * mAngle;

	float maxDistance = (mVelocity * mVelocity * sin(2 * radianAngle)) / mGravity;

	for (int i = 0; i <= mResolution; i++) {
		float t = static_cast<float>(i) / static_cast<float>(mResolution);
		arcArray[i] = CalculateArcPoint(t, maxDistance, radianAngle);
	}

	return arcArray;
}
