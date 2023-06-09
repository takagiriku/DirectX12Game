#pragma once

#include <string>
#include <vector>
#include <DirectXMath.h>

// レベルデータ
struct LevelData {
	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 平行移動
		DirectX::XMVECTOR translation;
		// 回転角
		DirectX::XMVECTOR rotation;
		// スケーリング
		DirectX::XMVECTOR scaling;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects;
	
};



// レベルデータのローダー
class LevelLoader {

	
public:// 定数
	// デフォルトの読み込みディレクトリ
	static const std::string kDefaultBaseDirectory;
	// ファイル拡張子
	static const std::string kExtension;
	//static std::vector<LevelData*> levelDataList;
	

public:// メンバ関数
	static std::vector<LevelData*> LoadFile(const std::vector<std::string>& fileNames);
};

