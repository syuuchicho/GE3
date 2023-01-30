#pragma once
#include <DirectXMath.h>
#include <string>
#include "DirectXCommon.h"

//�X�v���C�g���ʕ�
class SpriteCommon
{
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
};

