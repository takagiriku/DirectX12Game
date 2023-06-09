#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include <d3dx12.h>
#include <DirectXTex.h>
#include <base/DirectXCommon.h>
class SpriteManager
{
private:
	using XMMATRIX = DirectX::XMMATRIX;
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	// �e�N�X�`���̍ő喇��
	static const UINT spriteMax = 512;

	void Initialize(DirectXCommon* dxCommon);

	//�e�N�X�`���ǂݍ���
	void LoadTexture(UINT texnumber, const wchar_t* filename);

	//�e�N�X�`���o�b�t�@�擾
	ID3D12Resource* GetSpriteTexbuff(UINT texnumber, XMFLOAT2& outSize);

	XMFLOAT2 GetSpriteSize(UINT texnumber) const;


	// �f�X�N���v�^�q�[�v���Z�b�g
	void SetDescriptorHeaps(ID3D12GraphicsCommandList* cmdList);

	// SRV���Z�b�g
	void SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT RootParameterIndex, UINT texnumber);

	ID3D12DescriptorHeap* GetDescHeap() { return descHeap.Get(); }
private:
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff[spriteMax];
	DirectXCommon* dxCommon = nullptr;
	XMFLOAT2 size = { 100.0f, 100.0f };
};