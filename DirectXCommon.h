#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include<wrl.h>
#include <vector>
#include<chrono>
#include<thread>
#include"WinApp.h"



//DirectX基盤
class DirectXCommon
{
public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	//デバイスを取得
	ID3D12Device* GetDevice()const { return device.Get(); }
	//コマンドリストを取得
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
private:
	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定処理
	void UpdateFixFPS();
	/// <summary>
	/// デバイス初期化
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// コマンド初期化
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// スワップチェーン初期化
	/// </summary>
	void InitializeSwapchain();


	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

private:
	WinApp* winApp = nullptr;

	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	//レンダーターゲットビュー
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// フェンスの生成
	UINT64 fenceVal = 0;

};

