#pragma once

#define DIRECTINPUT_VERSION 0x0800          // DirectInput�̃o�[�W�����w��

#include <Windows.h>
#include <wrl.h>
#include <dinput.h>
// ����
class Input
{
public:
	
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �ÓI�����o�ϐ�
	static Input* GetInstance();

public: // �����o�֐�
	
	// ������
	bool Initialize(HINSTANCE hInstance, HWND hwnd);

	// ���t���[������
	void Update();

	// �L�[�̉������`�F�b�N
	bool Push(BYTE keyNumber);

	// �L�[�̃g���K�[���`�F�b�N
	bool Trigger(BYTE keyNumber);

	


private: // �����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devKeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

};

