#pragma once
#include<DirectXMath.h>
#include "SpriteCommon.h"
//スプライト
class Sprite
{
public:	//メンバ関数
	//初期化
	void Initialize(SpriteCommon* spriteCommon);

	//描画
	void Draw();
private:	//メンバ変数
	SpriteCommon* spriteCommon = nullptr;

	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbview{};
};

