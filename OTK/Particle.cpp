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
	//�摜�̓ǂݍ���
	int GHandle = LoadGraph(filename);

	// �ǂ݂��񂾃O���t�B�b�N����ʂɕ`��
	DrawGraph(position.x, position.y, GHandle, TRUE);

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	DeleteGraph(GHandle);
}

bool* Particle::IsDead()
{
	return isDeadFrag;
}
