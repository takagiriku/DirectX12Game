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

	// DirectInput�I�u�W�F�N�g�̐���	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) { assert(0); }
	// �L�[�{�[�h�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);
	if (FAILED(result)) { assert(0); }
	// ���̓f�[�^�`���̃Z�b�g
	result = devKeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	if (FAILED(result)) { assert(0); }
	// �r�����䃌�x���̃Z�b�g
	result = devKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) { assert(0); }
	return true;
}

void Input::Update()
{
	HRESULT result;

	{// �L�[�{�[�h
		result = devKeyboard->Acquire();	// �L�[�{�[�h����J�n

		// �O��̃L�[���͂�ۑ�
		memcpy(keyPre, key, sizeof(key));

		// �L�[�̓���
		result = devKeyboard->GetDeviceState(sizeof(key), key);
	}

}

bool Input::Push(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	if (key[keyNumber]) {
		return true;
	}

	return false;
}

bool Input::Trigger(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	return false;
}

