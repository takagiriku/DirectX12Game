#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")

Input* Input::GetInstance()
{
	static Input instance;

	return &instance;
}

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	assert(!dinput);

	// DirectInputオブジェクトの生成	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) { assert(0); }
	// キーボードデバイスの生成	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);
	if (FAILED(result)) { assert(0); }
	// 入力データ形式のセット
	result = devKeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	if (FAILED(result)) { assert(0); }
	// 排他制御レベルのセット
	result = devKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) { assert(0); }
	return true;
}

void Input::Update()
{
	HRESULT result;

	{// キーボード
		result = devKeyboard->Acquire();	// キーボード動作開始

		// 前回のキー入力を保存
		memcpy(keyPre, key, sizeof(key));

		// キーの入力
		result = devKeyboard->GetDeviceState(sizeof(key), key);
	}

}

bool Input::Push(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	if (key[keyNumber]) {
		return true;
	}

	return false;
}

bool Input::Trigger(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	return false;
}

