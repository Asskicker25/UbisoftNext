#pragma once

#include "../Entities/CGameObject.h"

struct SParticleData
{
	CSimpleSprite* sprite = nullptr;
	Vector2 mVelocity;
	float mGravity = 0;
	float mLifetime = 0;
	bool mIsEnabled = true;
};

class CParticleSystem : public CGameObject
{
public:

	CParticleSystem(const std::string& texPath, int totalParticles, int row);

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	Vector2 mStartVelocityX = {-100, 100};
	Vector2 mStartVelocityY = {-100, 100};

	Vector2 mOriginInit;
	Vector2 mStartLifeTime = { 0,2 };

	float mGravity = 0;
	float mSpawnRadius = 50;
	float mScale = 1;

	float mColorX = 1;
	float mColorY = 1;
	float mColorZ = 1;

	int mTotalParticles = 10;

private:

	std::vector<SParticleData> mListOfParticles;

};

