#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include"SpriteManager.h"

// スプライト
class Sprite
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

protected: // サブクラス

	// 頂点データ構造体
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};
	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

	class Base
	{
	public:
		static void GraphicsPipeline();
		//protected:
			// メンバ関数
		SpriteManager* SpriteMan = nullptr;
		DirectXCommon* dxcommon = nullptr;
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootSignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelineState;
		//射影行列
		XMMATRIX matProjection{};
	};

public: // 静的メンバ関数
	// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	// 描画後処理
	static void PostDraw();

public: // メンバ関数


	void Initialize();

	static void StaticInitialize(DirectXCommon* dxcommon, SpriteManager* SpriteMan);
	void Create(UINT texNumber);
	// 角度の設定
	void SetRotation(float rotation);
	// 座標の設定
	void SetPosition(XMFLOAT2 position);
	// サイズの設定
	void SetSize(XMFLOAT2 size);
	//アルファ値の設定
	void SetAlpha(float alpha) { color.w = alpha; }
	// アンカーポイントの設定
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	// 左右反転の設定
	void SetIsFlipX(bool isFlipX);
	// 上下反転の設定
	void SetIsFlipY(bool isFlipY);
	// テクスチャ範囲設定
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

	// 座標の取得
	const XMFLOAT2& GetPosition() { return position; }
	void Draw();
	// 頂点データ転送
	void TransferVertices();

protected: // 静的メンバ変数
	static Base* base;
	// テクスチャの最大枚数
	const int srvCount = 512;
	// 頂点数
	static const int vertNum = 4;
	// デバイス
	ID3D12Device* device;

protected: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// テクスチャ番号
	UINT texNumber = 0;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position{};
	// スプライト幅、高さ
	XMFLOAT2 size = { 100.0f, 100.0f };
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0, 0 };
	// ワールド行列
	XMMATRIX matWorld{};
	// 色
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// テクスチャ始点
	XMFLOAT2 texBase = { 0, 0 };
	// テクスチャ幅、高さ
	XMFLOAT2 texSize = { 100.0f, 100.0f };
	float tex_x = 0.0f;     //テクスチャ左上　X座標
	float tex_y = 0.0f;     //テクスチャ左上　Y座標
	float tex_width = 100.0f; //テクスチャ横幅
	float tex_height = 100.0f;//テクスチャ縦幅

};
