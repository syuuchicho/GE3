﻿#include"Input.h"
#include"Winapp.h"
#include"DirectXCommon.h"
#include"Sprite.h"
#include <DirectXMath.h>

#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

#pragma region 基盤システムの初期化

    //MSG msg{};

#pragma region WindowsAPI初期化処理
    WinApp* winApp = nullptr;
    winApp = new WinApp();
    winApp->Initialize();
#pragma endregion

#pragma region 入力初期化処理
    Input* input;
    input = new Input();
    input->Initialize(winApp);
#pragma endregion

#pragma region DirectX初期化処理
    //ポインタ
    DirectXCommon* dxCommon = nullptr;
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);
#pragma endregion 

#pragma region スプライト共通部

    SpriteCommon* spriteCommon = nullptr;
    //スプライト共通部の初期化
    spriteCommon = new SpriteCommon;
    spriteCommon->Initialize(dxCommon);
#pragma endregion

#pragma endregion 

#pragma region 最初のシーンの初期化

    Sprite* sprite = new Sprite();
    sprite->Initialize(spriteCommon);
#pragma endregion 


    // ゲームループ
    while (true) {
#pragma region 基盤システムの更新


        //Windowsのメッセージ処理
        if (winApp->ProcessMessage())
        {
            //ゲームループ
            break;
        }
        //入力の更新
        input->Update();
#pragma endregion 基盤システムの更新

#pragma region 最初のシーンの更新

#pragma endregion 
        //描画前処理
        dxCommon->PreDraw();
        spriteCommon->PreDraw();
#pragma region 最初のシーンの描画
        sprite->Draw();
#pragma endregion 
        //描画後処理
        dxCommon->PostDraw();
        // DirectX毎フレーム処理　ここまで
    }
#pragma region 最初のシーンの終了
    //Sprite
    delete sprite;

#pragma endregion 

#pragma region 基盤システムの終了
    delete spriteCommon;
    //WindowsAPIの終了処理
    delete dxCommon;
    //SpriteCommon
    delete input;
    //DirectXCommon
    winApp->Finalize();
    //WindowsAPIの解放
    delete winApp;
#pragma endregion 
    return 0;
}