#pragma once
#include<DirectXMath.h>
#include "SpriteCommon.h"
//�X�v���C�g
class Sprite
{
public:	//�����o�֐�
	//������
	void Initialize(SpriteCommon* spriteCommon);

	//�`��
	void Draw();
private:	//�����o�ϐ�
	SpriteCommon* spriteCommon = nullptr;

	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbview{};
};

