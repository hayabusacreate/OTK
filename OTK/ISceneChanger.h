#pragma once

typedef enum
{
	eScene_Title,    //�^�C�g��
	eScene_GamePlay, //�Q�[���v���C
	eScene_Ending,   //�G���f�B���O
	eScene_GameOver, //�Q�[���I�[�o�[
	eScene_None      //�Ȃ�
} eScene;


//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//�w��V�[���ɕύX����
	virtual void ChangeScene(eScene nextScene) = 0;
};
