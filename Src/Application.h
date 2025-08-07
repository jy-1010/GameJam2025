#pragma once
#include <string>
// クラスの前方宣言
class FPS;

class Application
{
public:
	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1500;	// スクリーン横幅;
	static constexpr int SCREEN_SIZE_Y = 960;	// スクリーン縦幅;

	// データパス関連
//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	//static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND_BGM;
	static const std::string PATH_SOUND_SE;

	// シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Application(); instance_->Init(); } }
	static Application& GetInstance(void) { return *instance_; }
	static void DeleteInstance(void) { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

	void Init(void);	// 初期化
	void Run(void);		// ゲームループの開始
	void Release(void);	// 解放

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const { return isInitFail_; };

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const { return isReleaseFail_; };

	void End(void) { isEnd_ = true; }

private:
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application(void);

	// デストラクタも同様
	~Application(void);

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	// FPS
	FPS* fps_;

	bool isEnd_;
};
