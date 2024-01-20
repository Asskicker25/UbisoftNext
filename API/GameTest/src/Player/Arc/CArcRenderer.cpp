#include "CArcRenderer.h"

CArcRenderer::CArcRenderer(int resolution) : CGameObject(), mResolution{ resolution }
{
	float sizeFactor = 0.1f / mResolution;
	for (int i = 0; i < mResolution; i++)
	{
		CArcDot* dot = new CArcDot();

		dot->pSprite->SetScale(0.1 - i * sizeFactor);

		mListOfDots.push_back(dot);
	}
}

void CArcRenderer::Start()
{

	CGameObject::Start();
}

void CArcRenderer::Update()
{
	CGameObject::Update();
}

void CArcRenderer::Render()
{
	CGameObject::Render();
}

void CArcRenderer::Cleanup()
{
	while (mListOfDots.size() != 0)
	{
		CArcDot* dot = mListOfDots[0];

		mListOfDots.erase(std::remove(mListOfDots.begin(), mListOfDots.end(), dot), mListOfDots.end());

		dot->Cleanup();
	}

	CGameObject::Cleanup();
}

void CArcRenderer::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CArcRenderer::UpdatePositions(std::vector<Vector2> pos)
{
	int i = 0;
	for (CArcDot* dot : mListOfDots)
	{
		dot->SetPosition(pos[i].x, pos[i].y, true);

		dot->mIsVisible = true;

		i++;
	}
}

void CArcRenderer::Disable()
{
	for (CArcDot* dot : mListOfDots)
	{
		dot->mIsVisible = false;
	}
}

void CArcRenderer::UpdateColor(float x, float y, float z, float w)
{
	for (CArcDot* dot : mListOfDots)
	{
		dot->pSprite->SetColor(x, y, z);
		dot->mOpacity = w;
	}
}
