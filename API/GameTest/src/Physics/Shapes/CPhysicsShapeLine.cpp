#include "CPhysicsShapeLine.h"

CPhysicsShapeLine::CPhysicsShapeLine()
{
}

void CPhysicsShapeLine::CalculateShape()
{
}

SLine CPhysicsShapeLine::GetLine()
{
	SLine line = mLine;

	// Apply scale to the line coordinates.
	line.mStartPoint.x *= mScale.x;
	line.mStartPoint.y *= mScale.y;

	line.mEndPoint.x *= mScale.x;
	line.mEndPoint.y *= mScale.y;

	// Apply offset to the line coordinates.
	line.mStartPoint = line.mStartPoint + mOffset;
	line.mEndPoint = line.mEndPoint + mOffset;

	return line;
}

void CPhysicsShapeLine::SetLine(float sx, float sy, float ex, float ey)
{
	mLine.mStartPoint = Vector2(sx, sy);
	mLine.mEndPoint = Vector2(ex, ey);
}

void CPhysicsShapeLine::Render()
{
	SLine line = GetLine();

	App::DrawLine(line.mStartPoint.x, line.mStartPoint.y, line.mEndPoint.x, line.mEndPoint.y, 0, 1, 0);
}


