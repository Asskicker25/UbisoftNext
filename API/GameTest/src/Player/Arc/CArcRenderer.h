#pragma once

#include "CArcDot.h"

class CArcRenderer : public CGameObject
{
public:

	CArcRenderer(int resolution);

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void UpdatePositions(std::vector<Vector2> pos);
	void Disable();

	void UpdateColor(float x, float y, float z, float w);

private:
	int mResolution = 10;
	std::vector<CArcDot*> mListOfDots;
};

