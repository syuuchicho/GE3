#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include<wrl.h>
#include <vector>
#include<chrono>
#include<thread>
#include"WinApp.h"



//DirectX���
class DirectXCommon
{
public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	//�f�o�C�X���擾
	ID3D12Device* GetDevice()const { return device.Get(); }
	//�R�}���h���X�g���擾
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
private:
	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ菈��
	void UpdateFixFPS();
	/// <summary>
	/// �f�o�C�X������
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// �R�}���h������
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// �X���b�v�`�F�[��������
	/// </summary>
	void InitializeSwapchain();


	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

private:
	WinApp* winApp = nullptr;

	//�L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	//�����_�[�^�[�Q�b�g�r���[
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//�t�F���X
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	// �t�F���X�̐���
	UINT64 fenceVal = 0;

};

