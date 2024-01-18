#pragma once

#include "../CPhysicsBaseShape.h"

// Represents a box physics shape derived from CPhysicsBaseShape.
class CPhysicsShapeBox : public CPhysicsBaseShape
{
public:

	// Initializes a CPhysicsShapeBox.
	CPhysicsShapeBox();

	// Constructor: Initializes a CPhysicsShapeBox with a given sprite.
	// Parameters:
	//   sprite - Pointer to the associated sprite.
	CPhysicsShapeBox(CSimpleSprite* sprite);


	void CalculateShape() override;		// Calculates the shape of the box physics object.
	void Render() override;				// Renders the box physics shape

	// GetBox method: Retrieves the information about the box.
	// Returns:
	//   A structure containing information about the box.
	SBox GetBox();


private:

	SBox mBox;		// Structure representing the box.
};

