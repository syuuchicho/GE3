#pragma once
#include<DirectXMath.h>
#include "SpriteCommon.h"

//スプライト
class Sprite
{
public:	//メンバ関数

	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; //色(RGBA)
	};

	//初期化
	void Initialize(SpriteCommon* spriteCommon);

	//更新
	void Update();

	//描画
	void Draw();
private:	//メンバ変数
	//スプライト情報
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };


	SpriteCommon* spriteCommon = nullptr;

	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbview{};

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffMaterial = nullptr;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

};

