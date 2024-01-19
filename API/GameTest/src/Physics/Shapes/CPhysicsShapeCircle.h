#pragma once

#include "../CPhysicsBaseShape.h"

// Represents a circle physics shape derived from CPhysicsBaseShape.
class CPhysicsShapeCircle : public CPhysicsBaseShape
{
public:

	// Initializes a CPhysicsShapeCircle.
	CPhysicsShapeCircle();	

	// Constructor: Initializes a CPhysicsShapeCircle with a given sprite.
	// Parameters:
	//   sprite - Pointer to the associated gameObject.
	CPhysicsShapeCircle(CGameObject* gameObject);


	void CalculateShape() override;		// Calculates the shape of the circle physics object.
	void Render() override;				// Renders the circle physics shape.

	// GetCircle method: Retrieves the information about the circle.
	// Returns:
	//   A structure containing information about the circle.
	SCircle GetCircle();

	// SetCenter method: Sets the center of the circle.
	// Parameters:
	//   x - X-coordinate of the center.
	//   y - Y-coordinate of the center.
	void SetCenter(float x, float y);

	// SetRadius method: Sets the radius of the circle.
	// Parameters:
	//   radius - Radius of the circle.
	void SetRadius(float radius);

private:

	SCircle mCircle;	// Structure representing the circle.

};

