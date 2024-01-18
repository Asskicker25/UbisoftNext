#pragma once

#include "../CPhysicsBaseShape.h"

// Represents a line physics shape derived from CPhysicsBaseShape.
class CPhysicsShapeLine : public CPhysicsBaseShape
{
public:

	CPhysicsShapeLine();			// Initializes a CPhysicsShapeLine.

	void CalculateShape() override; // Calculates the shape of the line physics
	void Render() override;			// Renders the line physics shape.

	// GetLine method: Retrieves the information about the line.
	// Returns:
	//   A structure containing information about the line.
	SLine GetLine();

	// SetLine method: Sets the parameters of the line.
	// Parameters:
	//   sx - Start x-coordinate of the line.
	//   sy - Start y-coordinate of the line.
	//   ex - End x-coordinate of the line.
	//   ey - End y-coordinate of the line.
	void SetLine(float sx, float sy, float ex, float ey);

private:

	SLine mLine;	// Structure representing the line
};

