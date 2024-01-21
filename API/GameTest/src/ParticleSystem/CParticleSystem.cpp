#include "CParticleSystem.h"
#include "../stb_image/stb_image.h"
#include "../Timer/CTimer.h"
#include "../Utilities/Random.h"

#include "../World/CWorld.h"


CParticleSystem::CParticleSystem(const std::string& texPath, int totalParticles, int row) : CGameObject(),
	mTotalParticles{ totalParticles } 
{
	pSprite = App::CreateSprite("Assets/Sprites/Circle.png", 1, 1);
	mOrder = 1;
	mOpacity = 0.2;

	for (int i = 0; i < mTotalParticles; i++)
	{
		SParticleData data;
		data.sprite = App::CreateSprite(texPath.c_str(), row, 1);

		std::vector<int> frames;
		for (int i = 0; i < row; i++)
		{
			frames.push_back(i);
		}
		data.sprite->CreateAnimation(0, 1.0f / 6.0f, frames);
		data.sprite->SetAnimation(0);

		mListOfParticles.push_back(data);
	}

}

void CParticleSystem::Start()
{
	for (SParticleData& data : mListOfParticles)
	{
		data.mVelocity = Vector2(GetRandomFloatNumber(mStartVelocityX.x, mStartVelocityX.y) , 
			GetRandomFloatNumber(mStartVelocityY.x, mStartVelocityY.y));

		data.mLifetime = GetRandomFloatNumber(mStartLifeTime.x, mStartLifeTime.y);


		Vector2 pos = GetPosition();

		float x = GetRandomFloatNumber(-1, 1);
		float y = GetRandomFloatNumber(-1, 1);

		pos.x += x * mSpawnRadius;
		pos.y += y * mSpawnRadius;

		data.sprite->SetPosition(pos.x, pos.y);
	}

	mOriginInit = CWorld::GetInstance().mOrigin;

	CGameObject::Start();
}

void CParticleSystem::Update()
{

	Vector2 currentOrigin = CWorld::GetInstance().mOrigin;;

	Vector2 offset = currentOrigin - mOriginInit;

	for (SParticleData& data : mListOfParticles)
	{
		if (!data.mIsEnabled) continue;


		float x, y;

		data.sprite->GetPosition(x, y);

		x -= offset.x;
		y -= offset.y;

		data.mGravity -= mGravity * CTimer::GetInstance().mDeltaTime;
		y -= data.mGravity;

		x += data.mVelocity.x * CTimer::GetInstance().mDeltaTime;
		y += data.mVelocity.y * CTimer::GetInstance().mDeltaTime;

		data.sprite->SetPosition(x, y);

		data.sprite->SetScale(mScale);

		data.sprite->SetColor(mColorX, mColorY, mColorZ);

		data.mLifetime -= CTimer::GetInstance().mDeltaTime;

		if (data.mLifetime <= 0)
		{
			data.mIsEnabled = false;
		}

	}

	CGameObject::Update();

	mOriginInit = CWorld::GetInstance().mOrigin;
}

void CParticleSystem::Render()
{
	for (SParticleData& data : mListOfParticles)
	{
		if (!data.mIsEnabled) continue;

		data.sprite->Draw();
	}
	CGameObject::Render();
}

void CParticleSystem::Cleanup()
{
	mListOfParticles.clear();

	CGameObject::Cleanup();
}

void CParticleSystem::OnDestroy()
{
	CGameObject::OnDestroy();
}
