#include "Particle.h"
#include "Vector2.h"
#include "Renderer.h"
#include "DxLib.h"


Particle::Particle(const char * filename,Vector2 & position, Vector2 & velocity, const IParticleMediator * mediator):
	filename(filename),
	position(position),
	velocity(velocity),
	gravity(gravity),
	mediator(mediator)
{

	isDeadFrag = false;
}

Particle::Particle(const IParticleMediator * mediator) :
	filename(filename),
	position(position),
	velocity(velocity),
	gravity(gravity),
	mediator(mediator)
{

	isDeadFrag = false;
}

Particle::~Particle()
{

}

void Particle::SetTexture(const char * filename)
{
	this->filename = filename;
}

void Particle::SetVelocity(Vector2& velocity)
{
	this->velocity = velocity;
}

void Particle::SetGravity(Vector2 & gravity)
{
	this->gravity = gravity;
}

 const char * Particle::GetTexture()
{
	return filename;
}

 Vector2 & Particle::GetPosition()
{
	return position;
}

Vector2 & Particle::GetVelocity()
{
	return velocity;
}

Vector2 & Particle::GetGravity()
{
	return gravity;
}

void Particle::Update()
{

	position = velocity;

	velocity += gravity;
}

void Particle::Draw()
{
	//画像の読み込み
	int GHandle = LoadGraph(filename);

	// 読みこんだグラフィックを画面に描画
	DrawGraph(position.x, position.y, GHandle, TRUE);

	// 読み込んだ画像のグラフィックハンドルを削除
	DeleteGraph(GHandle);
}

bool* Particle::IsDead()
{
	return isDeadFrag;
}
