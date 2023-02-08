#pragma once
#include<DirectXMath.h>
#include "SpriteCommon.h"

//スプライト
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 720;

	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; //色(RGBA)
	};

	struct ConstBufferDataTransform
	{
		DirectX::XMMATRIX mat;//3D行列
	};

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
public:	//メンバ関数

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

	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

};

