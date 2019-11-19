//パーティクル
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "IParticleMediator.h"
#include "Vector2.h"

class Particle
{
public:
	Particle(const char* filename,Vector2& position,Vector2& velocity,const IParticleMediator* mediator);
	Particle(const IParticleMediator * mediator);
	~Particle();
	void SetTexture(const char* filename);
	void SetVelocity(Vector2& velocity);
	void SetGravity(Vector2& gravity);
	const char* GetTexture();
	Vector2& GetPosition();
	Vector2& GetVelocity();
	Vector2& GetGravity();
	virtual void Update();
	virtual void Draw();
	bool* IsDead();

protected:
	Vector2& gravity;
	const char* filename;
	bool* isDeadFrag;
	Vector2& position;
	Vector2& velocity;
	const IParticleMediator* mediator;
};

#endif // !_PARTICLE_H_
