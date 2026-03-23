#include "SoundManager.h"
#include <DxLib.h>
#include <cassert>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Utility/Math.h"

namespace
{
	// サウンドデータへの参照を持ったファイルパス
	const char* const kSoundDataPath = "Resources\\SoundPath.json";

	const char* const kFolderPath = "folderPath";
	const char* const kSEFilePath = "seFilePath";
	const char* const kBGMFilePath = "bgmFilePath";

	// デフォルトの音量
	constexpr int kDefaultVolume = 160;

	// BGMの遷移速度
	constexpr int kBGMFadeSpeed = 4;

	// 最大音量
	constexpr int kMaxVolume = 255;
	// 最小音量
	constexpr int kMinVolume = 0;
}

SoundManager::SoundManager() :
	m_seHandles{ 0 },
	m_bgmHandles{ 0 },
	m_currentBgmHandle(-1),
	m_nextBgmHandle(-1),
	m_currentBgmVolume(kMaxVolume),
	m_nextBgmVolume(kMinVolume)
{
	// ハンドルを初期化
	for (auto& se : m_seHandles)
	{
		se = -1;
	}

	for (auto& bgm : m_bgmHandles)
	{
		bgm = -1;
	}

	// サウンドデータのjsonファイルを読み込む
	std::ifstream fIn(kSoundDataPath);

	// 読み込みに失敗していたら警告
	assert(fIn && "サウンドデータのjsonファイルが開けませんでした");

	// jsonのデータを取得
	fIn >> m_pathJson;

	// サウンドデータを読み込む
	LoadSound(m_seHandles, static_cast<int>(Sound::SE::Max), kSEFilePath);
	LoadSound(m_bgmHandles, static_cast<int>(Sound::BGM::Max), kBGMFilePath);
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;

	return instance;
}

void SoundManager::Update()
{
	// クロスフェード処理
	CrossFading();

	// BGMが再生されていたら音量を設定
	if (m_currentBgmHandle != -1) ChangeVolumeSoundMem((kDefaultVolume * m_currentBgmVolume) / kMaxVolume, m_currentBgmHandle);
	// 次のBGMが再生されていたら音量を設定
	if (m_nextBgmHandle != -1) ChangeVolumeSoundMem((kDefaultVolume * m_nextBgmVolume) / kMaxVolume, m_nextBgmHandle);
}

void SoundManager::PlaySE(Sound::SE id, int playType)
{
	int handle = m_seHandles[static_cast<int>(id)];

	// 読み込めていないIDなら即時return
	assert(handle != -1 && "読み込みに失敗したSEを再生しようとしています");
	if (handle == -1) return;

	// SEの再生
	PlaySoundMem(handle, playType);
}

void SoundManager::PlayBGM(Sound::BGM id)
{
	// すでに再生していたら停止する
	// 多重再生を防ぐ
	//StopBGM();

	int handle = m_bgmHandles[static_cast<int>(id)];

	// 現在再生中のBGMと同じBGMを再生しようとしたら処理を行わない
	if (m_currentBgmHandle == handle) return;

	// 読み込めていないIDなら即時return
	assert(handle != -1 && "読み込みに失敗したBGMを再生しようとしています");
	if (handle == -1) return;

	// 再生中のBGMハンドルの更新
	// BGMが再生されていなかったら
	if (m_currentBgmHandle == -1)
	{
		m_currentBgmHandle = handle;

		// BGMの再生
		PlaySoundMem(m_currentBgmHandle, DX_PLAYTYPE_LOOP);
	}
	// BGMが再生されていたら
	else
	{
		// クロスフェードを開始する
		m_nextBgmHandle = handle;

		m_currentBgmVolume = kMaxVolume;
		m_nextBgmVolume = kMinVolume;

		m_isCrossFading = true;

		// BGMの再生
		PlaySoundMem(m_nextBgmHandle, DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopBGM()
{
	// BGMが再生しているか確認
	if (m_currentBgmHandle == -1) return;

	// BGMの停止
	StopSoundMem(m_currentBgmHandle);

	m_currentBgmHandle = -1;
}

void SoundManager::Release()
{
	for (auto& se : m_seHandles)
	{
		if (se == -1) continue;

		// SEデータの削除
		DeleteSoundMem(se);

		// ハンドルを初期値にしておく
		se = -1;
	}

	for (auto& bgm : m_bgmHandles)
	{
		if (bgm == -1) continue;

		// SEデータの削除
		DeleteSoundMem(bgm);

		// ハンドルを初期値にしておく
		bgm = -1;
	}
}

void SoundManager::LoadSound(int handle[], int number, const char* key)
{
	// フォルダーパスを取得
	std::string folderPath = m_pathJson["folderPath"];

	for (int i = 0; i < number; i++)
	{
		// データパスを取得
		std::string dataPath = m_pathJson[key][i];

		// ファイルパスを作成 フォルダ + データ名
		std::string filePath = folderPath + dataPath;

		// SEの読み込み
		handle[i] = LoadSoundMem(filePath.c_str());

		// 読み込みが失敗していたら警告
		assert(handle[i] != -1 && "音の読み込みに失敗しました");
		if (handle[i] == -1) continue;

		// ボリュームの設定
		ChangeVolumeSoundMem(kDefaultVolume, handle[i]);
	}
}

void SoundManager::CrossFading()
{
	// クロスフェード処理を行わないなら処理を停止
	if (!m_isCrossFading) return;

	// 現在のBGMの音量を最小に遷移する
	m_currentBgmVolume = Math::Approach(m_currentBgmVolume, kMinVolume, kBGMFadeSpeed);
	// 次に再生するBGMの音量を最大に遷移する
	m_nextBgmVolume = Math::Approach(m_nextBgmVolume, kMaxVolume, kBGMFadeSpeed);

	// 次に再生するBGMが最大音量になったら
	if (m_nextBgmVolume >= kMaxVolume)
	{
		StopBGM();

		m_currentBgmHandle = m_nextBgmHandle;
		m_nextBgmHandle = -1;

		m_currentBgmVolume = kMaxVolume;

		m_isCrossFading = false;
	}
}
