#pragma once

#include "../../App/app.h"
#include "Physics_Utils.h"


class CSimpleSprite;

// Abstract base class for physics shapes associated with a sprite.
class CPhysicsBaseShape
{
public:

	// Initializes a CPhysicsBaseShape without an associated sprite.
	CPhysicsBaseShape();	

	// Constructor: Initializes a CPhysicsBaseShape with a given sprite.
	// Parameters:
	//   sprite - Pointer to the associated gameObject.
	CPhysicsBaseShape(CGameObject* gameObject);

	virtual ~CPhysicsBaseShape() {};	// Ensures proper cleanup of derived classes.
	virtual void CalculateShape() = 0;	// Calculates the shape of the physics object.
	virtual void Render() = 0;			// Renders the physics shape.

	// SetScale method: Sets the scale of the physics shape.
	// Parameters:
	//   x - Scale factor along the x-axis.
	//   y - Scale factor along the y-axis.
	void SetScale(float x, float y);

	// SetOffset method: Sets the offset of the physics shape.
	// Parameters:
	//   x - Offset along the x-axis.
	//   y - Offset along the y-axis.
	void SetOffset(float x, float y);

	Vector2 GetOffset();

protected: 

	CGameObject* pGameObject = nullptr;	// Pointer to the associated gameObject.
	
	Vector2 mScale = Vector2(1, 1);		// Scale of the physics shape.
	Vector2 mOffset = Vector2(0, 0);	// Offset of the physics shape.
};

