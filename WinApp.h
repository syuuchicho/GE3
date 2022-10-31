#pragma once
#include<Windows.h>
//#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��


//WindowsAPI
class WinApp
{
public://�ÓI�����o�[�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://�ÓI�����o�[�ϐ�
	 // �E�B���h�E����
	static const int window_width = 1280;
	//�E�C���h�E�c��
	static const int window_height = 720;

public://�����o�֐�
	//������
	void Initialize();
	//�X�V
	void Update();
	//�I��
	void Finalize();

	//���b�Z�[�W����
	bool ProcessMessage();

	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance()const { return w.hInstance; }
private://�����o�ϐ�
	HWND hwnd = nullptr;
	WNDCLASSEX w{};
};

