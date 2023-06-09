#include "SpriteManager.h"
#include<cassert>

using namespace DirectX;

void SpriteManager::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result;
	this->dxCommon = dxCommon;

	// �f�X�N���v�^�q�[�v�𐶐�	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = spriteMax;
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//����
	if (FAILED(result)) { assert(0); }
}

void SpriteManager::LoadTexture(UINT texnumber, const wchar_t* filename)
{
	HRESULT result;
	// WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) { assert(0); }

	const Image* img = scratchImg.GetImage(0, 0, 0); // ���f�[�^���o
	 // �������e�N�X�`���̕��ƍ������擾
	UINT width = metadata.width;
	UINT height = metadata.height;
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// �e�N�X�`���p�o�b�t�@�̐���
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&texBuff[texnumber]));
	if (FAILED(result)) { assert(0); }

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texBuff[texnumber]->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		img->pixels,    // ���f�[�^�A�h���X
		(UINT)img->rowPitch,  // 1���C���T�C�Y
		(UINT)img->slicePitch // 1���T�C�Y
	);
	if (FAILED(result)) { assert(0); }

	// �V�F�[�_���\�[�X�r���[�쐬
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texBuff[texnumber]->GetDesc();

	srvDesc.Format = metadata.format;//RGBA
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	dxCommon->GetDevice()->CreateShaderResourceView(texBuff[texnumber].Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), texnumber, dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV))
	);
	// �X�v���C�g�̃T�C�Y��ݒ�
	size = { (float)width, (float)height };
}

ID3D12Resource* SpriteManager::GetSpriteTexbuff(UINT texnumber, XMFLOAT2& outSize)
{
	outSize = { 0.0f, 0.0f }; // �f�t�H���g�̃T�C�Y

	if (texnumber >= spriteMax)
	{
		// �����ȃe�N�X�`���ԍ�
		return nullptr;
	}

	if (!texBuff[texnumber])
	{
		// �e�N�X�`�������[�h����Ă��Ȃ�
		return nullptr;
	}

	outSize = GetSpriteSize(texnumber); // �X�v���C�g�̃T�C�Y���擾����outSize�Ɋi�[

	return texBuff[texnumber].Get();
}

XMFLOAT2 SpriteManager::GetSpriteSize(UINT texnumber) const
{
	if (texnumber >= spriteMax || !texBuff[texnumber])
	{
		// �����ȃe�N�X�`���ԍ��܂��̓��[�h����Ă��Ȃ��e�N�X�`��
		return { 0.0f, 0.0f };
	}

	const D3D12_RESOURCE_DESC& resDesc = texBuff[texnumber]->GetDesc();
	return { static_cast<float>(resDesc.Width), static_cast<float>(resDesc.Height) };
}





void SpriteManager::SetDescriptorHeaps(ID3D12GraphicsCommandList* cmdList)
{
	//�f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void SpriteManager::SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT RootParameterIndex, UINT texnumber)
{
	//SRV�̃T�C�Y���擾
	UINT sizeSRV = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�f�X�N���v�^�e�[�u���̐擪���擾
	D3D12_GPU_DESCRIPTOR_HANDLE start = descHeap->GetGPUDescriptorHandleForHeapStart();

	//SRV��GPU�n���h�����擾
	D3D12_GPU_DESCRIPTOR_HANDLE handle = CD3DX12_GPU_DESCRIPTOR_HANDLE(start, texnumber, sizeSRV);

	//SRV���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(RootParameterIndex, handle);
}