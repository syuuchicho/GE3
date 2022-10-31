#pragma once
#include<windows.h>
#include<wrl.h>
#include<dinput.h>
#include"WinApp.h"
//#define DIRECTINPUT_VERSION     0x0800      //DirectInputのバージョン指定

class Input
{
public:
	//namespace省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	bool PushKey(BYTE keyNumber);
	/// <summary>
	/// キーのトリガーをチェック
	/// </summary>
	bool TriggerKey(BYTE keyNumber);
private:
	//WindowsAPI
	WinApp* winApp_ = nullptr;
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	// 全キーの入力状態を取得する
	BYTE key[256] = {};
	// 前回の全キー入力状態を取得する
	BYTE keyPre[256] = {};
};
