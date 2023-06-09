#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
class PostEffect
{
private://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//Directx::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: // �T�u�N���X
// ���_�f�[�^�\����
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};
	// �萔�o�b�t�@Time
	struct ConstBufferData
	{
		float time;
		bool StartFlag = false;
	};// �萔�o�b�t�@StartTime
	struct ConstBufferData2
	{
		bool EndFlag = false;
		float StartTime;
	};

public:

	//�R���X�g���N�^
	PostEffect();
	//�`��R�}���h�̔��s
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void Initialize(ID3D12Device* device);


	//�V�[���`��O����
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	//�V�[���`��㏈��
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	void PostEffect::Update(float Times);

	//�p�C�v���C������
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
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource>texBuff;
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//�O���t�B�b�N�X�p�C�v���C��
	ComPtr<ID3D12PipelineState>pipelineState;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature>rootSignature;

protected: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���[���h�s��
	XMMATRIX matWorld{};
	// �F
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// �f�o�C�X
	static ID3D12Device* device;
	// ���_��
	static const int vertNum = 4;
	// Z�����̉�]�p
	float rotation = 0.0f;
	// ���W
	XMFLOAT2 position{};
	// �X�v���C�g���A����
	XMFLOAT2 size = { 100.0f, 100.0f };
private:
	//��ʃN���A�J���[
	static const float clearColor[4];
	
	float Times;
	bool Starrt = false;
	bool End = false;
};

