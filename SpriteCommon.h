#pragma once
#include <DirectXMath.h>
#include <string>
#include "DirectXCommon.h"

//スプライト共通部
class SpriteCommon
{
public:
	const size_t texturewidth = 256;
	const size_t textureheight = 256;
	const size_t imageDataCount = texturewidth * textureheight;

public:	//メンバ関数
	//初期化
	void Initialize(DirectXCommon* dxCommon);

	//描画
	void PreDraw();

	//Getter
	DirectXCommon* GetDirectXCommon() { return dxCommon; };

private:	//メンバ変数
	DirectXCommon* dxCommon = nullptr;
	
	//パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipelineState;

	//ルートシグネチャー
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature;

	//設定を元にSRV用デスクリプタヒープを生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap ;
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff ;


};

