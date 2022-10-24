#pragma once
#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION     0x0800      //DirectInputのバージョン指定
#include<dinput.h>

class Input
{
public:
	//namespace省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(HINSTANCE hInstance, HWND hwnd);
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
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	// 全キーの入力状態を取得する
	BYTE key[256] = {};
	// 前回の全キー入力状態を取得する
	BYTE keyPre[256] = {};
};
