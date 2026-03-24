#pragma once

#include <DxLib.h>
#include <nlohmann/json.hpp>

namespace Sound
{
	enum class BGM
	{
		Title,
		InGame,
		Result,
		Max
	};

	enum class SE
	{
		CreateWire,
		SwitchBranch,
		LightUp,
		Destination,
		GameStart,
		Confirm,
		MenuMove,
		ReadyDraw,
		RankUp,
		ShowRank,
		Countdown,
		Finish,
		Pause,
		Max
	};
}

using json = nlohmann::json;

class SoundManager
{
public:

	static SoundManager& GetInstance();

	~SoundManager() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="id">再生したいSEのID</param>
	/// <param name="freq">再生周波数</param>
	/// <param name="playType">再生方法</param>
	void PlaySE(Sound::SE id, float freq = -1, int playType = DX_PLAYTYPE_BACK);

	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="id"></param>
	void PlayBGM(Sound::BGM id);

	/// <summary>
	/// 再生中のBGMの停止
	/// </summary>
	void StopBGM();

	/// <summary>
	/// 読み込んだデータの解放
	/// </summary>
	void Release();

private:

	/// <summary>
	/// コンストラクタ
	/// シングルトンパターンのクラスならprivateにして生成できないようにする
	/// </summary>
	SoundManager();

	// シングルトンパターンのクラスでは、コピーできないように「禁止」する
	// コピー禁止 Class a = b; / Class a(b);
	SoundManager(const SoundManager&) = delete;
	// コピー代入禁止	a = b;
	SoundManager& operator=(const SoundManager&) = delete;
	// ムーブ禁止		
	SoundManager(SoundManager&&) = delete;
	// ムーブ代入禁止
	SoundManager& operator=(SoundManager&&) = delete;

	/// <summary>
	/// 音の読み込み
	/// </summary>
	/// <param name="handle">読み込んだ音を格納するハンドルの配列</param>
	/// <param name="number">読み込む音の数</param>
	/// <param name="key">jsonファイルの読み込みたいキーの名前</param>
	void LoadSound(int handle[], int number, const char* key);

	/// <summary>
	/// BGMのクロスフェード処理
	/// </summary>
	void CrossFading();

	/// <summary>
	/// サウンドデータへの参照を持ったjsonファイル
	/// </summary>
	json m_pathJson;

	/// <summary>
	/// SEのハンドル
	/// </summary>
	int m_seHandles[static_cast<int>(Sound::SE::Max)];

	/// <summary>
	/// BGMのハンドル
	/// </summary>
	int m_bgmHandles[static_cast<int>(Sound::BGM::Max)];

	/// <summary>
	/// 再生中のBGMハンドル
	/// </summary>
	int m_currentBgmHandle;

	/// <summary>
	/// 次に再生するBGMハンドル
	/// </summary>
	int m_nextBgmHandle;

	/// <summary>
	/// 再生中のBGMの音量
	/// </summary>
	int m_currentBgmVolume;

	/// <summary>
	/// 次に再生するBGMの音量
	/// </summary>
	int m_nextBgmVolume;

	/// <summary>
	/// クロスフェード処理を行うかどうか
	/// </summary>
	bool m_isCrossFading;
};
