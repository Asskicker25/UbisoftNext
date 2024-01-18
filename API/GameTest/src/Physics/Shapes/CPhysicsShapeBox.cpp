#include "CPhysicsShapeBox.h"

CPhysicsShapeBox::CPhysicsShapeBox() : CPhysicsBaseShape()
{
	// Set default box dimensions.

	mBox.mMinPoint = Vector2(-1, -1);
	mBox.mMaxPoint = Vector2(1, 1);
}

CPhysicsShapeBox::CPhysicsShapeBox(CSimpleSprite* sprite) : CPhysicsBaseShape(sprite)
{
	CalculateShape();
}

void CPhysicsShapeBox::CalculateShape()
{

	if (pSprite == nullptr) return;

	// Calculate box dimensions based on sprite size.
	float extendX = pSprite->GetWidth() * 0.5f;
	float extendY = pSprite->GetHeight() * 0.5f;

	mBox.mMinPoint = Vector2(-extendX, -extendY);
	mBox.mMaxPoint = Vector2(extendX, extendY);

}

SBox CPhysicsShapeBox::GetBox()
{
	SBox box = mBox;

	// Apply scaling to box dimensions.
	box.mMinPoint.x *= mScale.x;
	box.mMinPoint.y *= mScale.y;

	box.mMaxPoint.x *= mScale.x;
	box.mMaxPoint.y *= mScale.y;

	// Adjust box position based on sprite and scaling.
	if (pSprite != nullptr)
	{

		box.mMinPoint = box.mMinPoint * pSprite->GetScale();
		box.mMaxPoint = box.mMaxPoint * pSprite->GetScale();

		float x, y;
		pSprite->GetPosition(x, y);

		box.mMinPoint.x += x;
		box.mMinPoint.y += y;

		box.mMaxPoint.x += x;
		box.mMaxPoint.y += y;

	}

	// Apply offset to box position.
	box.mMinPoint = box.mMinPoint + mOffset;
	box.mMaxPoint = box.mMaxPoint + mOffset;


	return box;
}

void CPhysicsShapeBox::Render()
{
	SBox box = GetBox();

	App::DrawLine(box.mMinPoint.x, box.mMinPoint.y, box.mMaxPoint.x, box.mMinPoint.y, 0, 1, 0);
	App::DrawLine(box.mMaxPoint.x, box.mMinPoint.y, box.mMaxPoint.x, box.mMaxPoint.y, 0, 1, 0);
	App::DrawLine(box.mMaxPoint.x, box.mMaxPoint.y, box.mMinPoint.x, box.mMaxPoint.y, 0, 1, 0);
	App::DrawLine(box.mMinPoint.x, box.mMaxPoint.y, box.mMinPoint.x, box.mMinPoint.y, 0, 1, 0);
}
