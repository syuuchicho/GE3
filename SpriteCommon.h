#pragma once
#include <DirectXMath.h>
#include <string>
#include "DirectXCommon.h"

//スプライト共通部
class SpriteCommon
{
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
};

