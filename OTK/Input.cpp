#include "Input.h"
#include "DxLib.h"

Input::Input()
	:input(0),key(0)
{
}

Input::~Input()
{
}

void Input::Update()
{
	int i;

	// �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
	i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �G�b�W����������͂��Z�b�g
	// Input.key = i & Input.input;
	key = i & input;
	// ���͏�Ԃ̕ۑ�
	//Input.input = i;
	input = i;
}

int Input::GetKey()
{
	return input;
}
