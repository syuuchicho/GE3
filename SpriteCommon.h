#pragma once
#include <DirectXMath.h>
#include <string>
#include "DirectXCommon.h"

//�X�v���C�g���ʕ�
class SpriteCommon
{
public:
	const size_t texturewidth = 256;
	const size_t textureheight = 256;
	const size_t imageDataCount = texturewidth * textureheight;

public:	//�����o�֐�
	//������
	void Initialize(DirectXCommon* dxCommon);

	//�`��
	void PreDraw();

	//Getter
	DirectXCommon* GetDirectXCommon() { return dxCommon; };

private:	//�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState>pipelineState;

	//���[�g�V�O�l�`���[
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature;

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap ;
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff ;


};

