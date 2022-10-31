#pragma once
#include<Windows.h>
//#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定


//WindowsAPI
class WinApp
{
public://静的メンバー関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://静的メンバー変数
	 // ウィンドウ横幅
	static const int window_width = 1280;
	//ウインドウ縦幅
	static const int window_height = 720;

public://メンバ関数
	//初期化
	void Initialize();
	//更新
	void Update();
	//終了
	void Finalize();

	//メッセージ処理
	bool ProcessMessage();

	//getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance()const { return w.hInstance; }
private://メンバ変数
	HWND hwnd = nullptr;
	WNDCLASSEX w{};
};

