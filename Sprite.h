#pragma once
#include<DirectXMath.h>
#include "SpriteCommon.h"

//�X�v���C�g
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 720;

	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; //�F(RGBA)
	};

	struct ConstBufferDataTransform
	{
		DirectX::XMMATRIX mat;//3D�s��
	};

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
public:	//�����o�֐�

	//������
	void Initialize(SpriteCommon* spriteCommon);

	//�X�V
	void Update();

	//�`��
	void Draw();
private:	//�����o�ϐ�
	//�X�v���C�g���
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };


	SpriteCommon* spriteCommon = nullptr;

	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbview{};

	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffMaterial = nullptr;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource>constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

};

