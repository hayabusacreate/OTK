#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Effect.h"
#include "Sound.h"

//�Q�[����ʃN���X
class GamePlay
	: public BaseScene
{

public:
	GamePlay(ISceneChanger * changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	int count;
	int SoundHandle;
	Sound sound;
};
