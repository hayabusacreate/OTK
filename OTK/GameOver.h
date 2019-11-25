#pragma once
#include "BaseScene.h"
#include "Sound.h"

class GameOver
	:public BaseScene
{
public:
	GameOver(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	int pad;
	int InputMonitor;
	int SoundHandle;
	Sound sound;
};