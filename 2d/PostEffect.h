#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
class PostEffect
{
private://エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//Directx::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // サブクラス
// 頂点データ構造体
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};
	// 定数バッファTime
	struct ConstBufferData
	{
		float time;
		bool StartFlag = false;
	};// 定数バッファStartTime
	struct ConstBufferData2
	{
		bool EndFlag = false;
		float StartTime;
	};

public:

	//コンストラクタ
	PostEffect();
	//描画コマンドの発行
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void Initialize(ID3D12Device* device);


	//シーン描画前処理
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	//シーン描画後処理
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	void PostEffect::Update(float Times);

	//パイプライン生成
	void CreateGraphicsPipelineState();
	void SetPostFlag(bool StartFlag) { this->PostFlag = StartFlag; }
	bool GetPostFlag() const {
		return this->PostFlag;
	}
	
	void SetStartFlag(bool StartFlag) { this->Starrt = StartFlag; }
	bool GetStartFlag() const {
		return this->Starrt;
	}
	void SetEndFlag(bool Endflag) { this->End = Endflag; }
	void GetEndFlag(bool Endflag) {  Endflag; }
	void ResetTime();
	void ClearTime();
	float Time;

	bool PostFlag = false;
	// テクスチャバッファ
	ComPtr<ID3D12Resource>texBuff;
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//グラフィックスパイプライン
	ComPtr<ID3D12PipelineState>pipelineState;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature>rootSignature;

protected: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ワールド行列
	XMMATRIX matWorld{};
	// 色
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// デバイス
	static ID3D12Device* device;
	// 頂点数
	static const int vertNum = 4;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position{};
	// スプライト幅、高さ
	XMFLOAT2 size = { 100.0f, 100.0f };
private:
	//画面クリアカラー
	static const float clearColor[4];
	
	float Times;
	bool Starrt = false;
	bool End = false;
};

