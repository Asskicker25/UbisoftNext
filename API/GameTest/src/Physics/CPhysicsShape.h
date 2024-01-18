#pragma once
#include "CPhysicsBaseShape.h"

// Available physics shape types.
enum EPhysicsShape
{
	CIRCLE,
	BOX,
	LINE
};

// Represents a physics shape associated with a sprite.
class CPhysicsShape
{
public:

	CPhysicsShape(CSimpleSprite* sprite, CPhysicsShape* physicsShape);	// Initializes a CPhysicsShape with a given sprite and physics shape.
	CPhysicsShape(CSimpleSprite* sprite, EPhysicsShape shapeType);		// Initializes a CPhysicsShape with a given sprite and physics shape type.
	
	~CPhysicsShape();
	
	EPhysicsShape mShapeType = EPhysicsShape::CIRCLE;					// Type of Physics Shape

	void InitializePhysics(EPhysicsShape shapeType);		// Initializes the physics shape based on the specified type
	void Render();											// Renders the physics shape.

	CPhysicsBaseShape* pShape = nullptr;					// Pointer to the base class for the physics shape.
private:
	CSimpleSprite* pSprite = nullptr;						// Pointer to the sprite associated with the physics shape.
};

