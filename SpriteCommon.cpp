#include "SpriteCommon.h"

#include<d3dcompiler.h>
#include <cassert>

#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

void SpriteCommon::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result;
	this->dxCommon = dxCommon;

	imageData = new XMFLOAT4[imageDataCount];
	for (size_t i = 0; i < imageDataCount; i++)
	{
		imageData[i].x = 1.0f;
		imageData[i].y = 0.0f;
		imageData[i].z = 0.0f;
		imageData[i].w = 1.0f;
	}

	//テクスチャ
	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty =
		D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//リソース設定
	D3D12_RESOURCE_DESC textrueResouceDesc{};
	textrueResouceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textrueResouceDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textrueResouceDesc.Width = (UINT)texturewidth;		//幅
	textrueResouceDesc.Height = (UINT)textureheight;		//高さ
	textrueResouceDesc.DepthOrArraySize = 1;
	textrueResouceDesc.MipLevels = 1;
	textrueResouceDesc.SampleDesc.Count = 1;
	
	//テクスチャバッファの生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textrueResouceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));
	//テクスチャバッファにデータ転送
	result = texBuff->WriteToSubresource(
		0,
		nullptr,//全領域へコピー
		imageData,	//元データアドレス
		sizeof(XMFLOAT4) * texturewidth,//1ラインサイズ
		sizeof(XMFLOAT4) * imageDataCount//全サイズ
	);

	//元データ解放
	delete[]imageData;

	//SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;//RGBA float
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	dxCommon->GetDevice()->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);

	//シェーダー
	ID3DBlob* vsBlob = nullptr;
	ID3DBlob* psBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	//頂点シェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/SpriteVS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vsBlob, &errorBlob);
	//エラー
	if (FAILED(result)) {
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウインドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	//ピクセルシェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/SpritePS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&psBlob, &errorBlob);
	//エラー
	if (FAILED(result)) {
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウインドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
	};

	//グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//シェーダの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//標準設定

	//ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;		//背面をカリング
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;		//ポリゴン内塗りつぶし6
	pipelineDesc.RasterizerState.DepthClipEnable = true;				//深度クリッピングを有効に

	//ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;//RGBAすべてのチャンネルを描画
	//共通
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	//半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	//頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//その他の設定
	pipelineDesc.NumRenderTargets = 1;//描画対象は1っ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;//0~255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1;//1ピクセルにつき1回サンプリング

	//デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	descriptorRange.NumDescriptors = 1;			//一度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;		//テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[2] = {};
	//定数バッファ0番
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//定数バッファビュー
	rootParams[0].Descriptor.ShaderRegister = 0;				//定数バッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;					//デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//	すべてのシェーダから見える
	//テクスチャレジスタ0番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;	//種類
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;			//デスクリプタレンジ
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;						//デスクリプタレンジ数
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;				//全てのシェーダから見える

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;						//横繰り返し(タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;						//縦繰り返し(タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;						//奥行繰り返し(タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;		//ボーダーのときは黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;						//全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;										//ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;													//ミップマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;				//ピクセルシェーダからのみ使用可能

	//ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;
	rootSignatureDesc.NumParameters = _countof(rootParams);
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	//ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;

	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));

	result = dxCommon->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));

	rootSigBlob->Release();
	//パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature.Get();

	//パイプランステートの生成
	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}

void SpriteCommon::PreDraw()
{
	//プリミティブ形状の設定コマンド
	dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//パイプラインステートとルートシグネチャの設定コマンド
	dxCommon->GetCommandList()->SetPipelineState(pipelineState.Get());
	dxCommon->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());

	//デスクリプタ
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get()};
	dxCommon->GetCommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	
	//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
	//SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
}