#include "Sprite.h"

using namespace DirectX;
using namespace Microsoft::WRL;
void Sprite::Initialize(SpriteCommon* spriteCommon)
{
	HRESULT result;
	this->spriteCommon = spriteCommon;
	//���_�f�[�^
	XMFLOAT3 vertices[] = {
		{-0.5f,-0.5f,0.0f},
		{-0.5f,+0.5f,0.0f},
		{+0.5f,-0.5f,0.0f},
	};
	//���_�f�[�^�S�̂̃T�C�Y=���_�f�[�^����̃T�C�Y*���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3)*_countof(vertices));

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};	//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;//���_�f�[�^
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//���_�o�b�t�@�̐���
	ID3D12Resource* vertBuff = nullptr;
	result = spriteCommon->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
assert(SUCCEEDED(result));

//�]��
XMFLOAT3* vertMap = nullptr;
result = vertBuff->Map(0, nullptr, (void**)&vertMap);

//�S���_�ɑ΂���
for (int i = 0; i < _countof(vertices); i++){
	vertMap[i] = vertices[i];	//���W���R�s�[
}
//�q���������
vertBuff->Unmap(0, nullptr);

vbview.BufferLocation = vertBuff->GetGPUVirtualAddress();
vbview.SizeInBytes = sizeVB;
vbview.StrideInBytes = sizeof(vertices[0]);

}

void Sprite::Draw()
{
	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbview);

	//�`��R�}���h
	spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(3, 1, 0, 0);

}