#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

//������
void Title::Initialize()
{
	mImageHandle = LoadGraph("title.png");    //�摜�̃��[�h
	InputMonitor = 0;
	sound.PlayBGM("Title.mp3");

}

void Title::Finalize()
{
	BaseScene::Finalize();
	sound.StopBGM("Title.mp3");
}

//�X�V
void Title::Update()
{

	pad = GetJoypadInputState(DX_INPUT_PAD1);

	if ((pad & PAD_INPUT_B))
	{
		if (InputMonitor == 0)
		{
			PlaySoundFile("", DX_PLAYTYPE_BACK);
			mSceneChanger->ChangeScene(eScene_GamePlay);//�V�[�������j���[�ɕύX
		}
		InputMonitor = 1;
	}
	else
	{
		InputMonitor = 0;
	}
}

//�`��
void Title::Draw()
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
}