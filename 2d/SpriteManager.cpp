#include "SpriteManager.h"
#include<cassert>

using namespace DirectX;

void SpriteManager::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result;
	this->dxCommon = dxCommon;

	// デスクリプタヒープを生成	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = spriteMax;
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//生成
	if (FAILED(result)) { assert(0); }
}

void SpriteManager::LoadTexture(UINT texnumber, const wchar_t* filename)
{
	HRESULT result;
	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) { assert(0); }

	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出
	 // 正しいテクスチャの幅と高さを取得
	UINT width = metadata.width;
	UINT height = metadata.height;
	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// テクスチャ用バッファの生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texBuff[texnumber]));
	if (FAILED(result)) { assert(0); }

	// テクスチャバッファにデータ転送
	result = texBuff[texnumber]->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,  // 1ラインサイズ
		(UINT)img->slicePitch // 1枚サイズ
	);
	if (FAILED(result)) { assert(0); }

	// シェーダリソースビュー作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = texBuff[texnumber]->GetDesc();

	srvDesc.Format = metadata.format;//RGBA
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dxCommon->GetDevice()->CreateShaderResourceView(texBuff[texnumber].Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), texnumber, dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV))
	);
	// スプライトのサイズを設定
	size = { (float)width, (float)height };
}

ID3D12Resource* SpriteManager::GetSpriteTexbuff(UINT texnumber, XMFLOAT2& outSize)
{
	outSize = { 0.0f, 0.0f }; // デフォルトのサイズ

	if (texnumber >= spriteMax)
	{
		// 無効なテクスチャ番号
		return nullptr;
	}

	if (!texBuff[texnumber])
	{
		// テクスチャがロードされていない
		return nullptr;
	}

	outSize = GetSpriteSize(texnumber); // スプライトのサイズを取得してoutSizeに格納

	return texBuff[texnumber].Get();
}

XMFLOAT2 SpriteManager::GetSpriteSize(UINT texnumber) const
{
	if (texnumber >= spriteMax || !texBuff[texnumber])
	{
		// 無効なテクスチャ番号またはロードされていないテクスチャ
		return { 0.0f, 0.0f };
	}

	const D3D12_RESOURCE_DESC& resDesc = texBuff[texnumber]->GetDesc();
	return { static_cast<float>(resDesc.Width), static_cast<float>(resDesc.Height) };
}





void SpriteManager::SetDescriptorHeaps(ID3D12GraphicsCommandList* cmdList)
{
	//デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void SpriteManager::SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT RootParameterIndex, UINT texnumber)
{
	//SRVのサイズを取得
	UINT sizeSRV = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//デスクリプタテーブルの先頭を取得
	D3D12_GPU_DESCRIPTOR_HANDLE start = descHeap->GetGPUDescriptorHandleForHeapStart();

	//SRVのGPUハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE handle = CD3DX12_GPU_DESCRIPTOR_HANDLE(start, texnumber, sizeSRV);

	//SRVをセット
	cmdList->SetGraphicsRootDescriptorTable(RootParameterIndex, handle);
}