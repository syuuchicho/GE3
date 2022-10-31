#pragma once
#include<windows.h>
#include<wrl.h>
#include<dinput.h>
#include"WinApp.h"
//#define DIRECTINPUT_VERSION     0x0800      //DirectInput�̃o�[�W�����w��

class Input
{
public:
	//namespace�ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	bool PushKey(BYTE keyNumber);
	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	bool TriggerKey(BYTE keyNumber);
private:
	//WindowsAPI
	WinApp* winApp_ = nullptr;
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput;
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;
	// �S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};
	// �O��̑S�L�[���͏�Ԃ��擾����
	BYTE keyPre[256] = {};
};
