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
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	// テクスチャの最大枚数
	static const UINT spriteMax = 512;

	void Initialize(DirectXCommon* dxCommon);

	//テクスチャ読み込み
	void LoadTexture(UINT texnumber, const wchar_t* filename);

	//テクスチャバッファ取得
	ID3D12Resource* GetSpriteTexbuff(UINT texnumber, XMFLOAT2& outSize);

	XMFLOAT2 GetSpriteSize(UINT texnumber) const;


	// デスクリプタヒープをセット
	void SetDescriptorHeaps(ID3D12GraphicsCommandList* cmdList);

	// SRVをセット
	void SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT RootParameterIndex, UINT texnumber);

	ID3D12DescriptorHeap* GetDescHeap() { return descHeap.Get(); }
private:
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff[spriteMax];
	DirectXCommon* dxCommon = nullptr;
	XMFLOAT2 size = { 100.0f, 100.0f };
};