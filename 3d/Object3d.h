#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "CollisionInfo.h"
#include"DirectXCommon.h"
class BaseCollider;

// 3Dオブジェクト
class Object3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // サブクラス


	class Base
	{
		
	public:
		static void GraphicsPipeline(DirectXCommon* dxCommon);
		
		// メンバ関数
		DirectXCommon* dxcommon = nullptr;
		// カメラ
		Camera* camera = nullptr;
		// ライト
		Light* light = nullptr;

		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootSignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelineState;
		
	};

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		float alpha;
		XMFLOAT3 cameraPos; // カメラ座標（ワールド座標）
	};

public: // 静的メンバ関数
	// 静的初期化
	static void StaticInitialize(DirectXCommon* dxCommon);

	// カメラのセット
	static void SetCamera(Camera* camera) { base->camera = camera; }
	// ライトグループのセット
	static void SetLightGroup(Light* light) { base->light = light; }

	// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	// 描画後処理
	static void PostDraw();

	// 3Dオブジェクト生成
	static Object3d* Create(Model* model = nullptr);

public: // メンバ関数
	// コンストラクタ
	Object3d() = default;

	// デストラクタ
	virtual ~Object3d();

	// 初期化
	virtual bool Initialize();

	// 毎フレーム処理
	virtual void Update();

	// 描画
	virtual void Draw();

	// 行列の更新
	void UpdateWorldMatrix();
	// モデルを取得
	inline Model* GetModel() { return model; }
	// モデルのセット
	void SetModel(Model* model) { this->model = model; }
	// 座標の設定
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	// 座標の取得
	const XMFLOAT3& GetPosition() { return position; }
	//回転の設定
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	// 回転の取得
	const XMFLOAT3& GetRotation() { return rotation; }

	// ワールド行列の取得
	const XMMATRIX& GetMatWorld() { return matWorld; }
	// コライダーのセット
	void SetCollider(BaseCollider * collider);

	// 衝突時コールバック関数
	virtual void OnCollision(const CollisionInfo & info) {}

	// ワールド座標を取得
	XMFLOAT3 GetWorldPosition();

	// スケールの設定
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	//アルファ値の設定
	void SetAlpha(float alpha) { color.w = alpha; }
	
	float GetAlpha() { return color.w; }
	
	//色の設定
	void SetColor(XMFLOAT3 color) { color = color; }
	
	const XMFLOAT4& GetColor() { return color; }

	// ビルボードフラグのセット
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	
	

protected: // メンバ変数
	static Base* base;
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,90,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	// モデル
	Model* model = nullptr;
	// ビルボード
	bool isBillboard = false;
	// コライダー
	BaseCollider* collider = nullptr;
};
