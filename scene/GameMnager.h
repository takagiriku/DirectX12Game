#include"GameScene.h"
#include"GameBase.h"
#include"TitleScene.h"
#include<vector>


//�Q�[���}�l�W���[
class GameMnager : public GameBase
{
public:
	GameMnager* GetInstance();
public:
	//������
	void Initialize() override;

	//�I��
	virtual void Finalize() override;

	//���t���[��
	virtual void Update() override;

	//�`��
	virtual void Draw() override;
	void SetPostFlag(bool StartFlag) { this->PostFlag = StartFlag; }
	bool PostFlag = false;
protected:
	float time = 0;
	float Times = 0.f;

	
};
