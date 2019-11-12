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

	// パッド１とキーボードから入力を得る
	i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// エッジを取った入力をセット
	// Input.key = i & Input.input;
	key = i & input;
	// 入力状態の保存
	//Input.input = i;
	input = i;
}

int Input::GetKey()
{
	return input;
}
