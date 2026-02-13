#include "InputDeviceBase.h"
#include "InputFormat/InputFormatBase.h"
#include "../Utility/Math.h"

namespace
{
	// オーバーフロー対策の入力情報のログを残すフレーム数
	int kMaxLog = 255;
}

void InputDeviceBase::Initialize()
{
	// デバイス固有の初期化処理を呼ぶ
	InitializeDevice();

	// すべてのフォーマットをチェックする
	for (auto& format : mFormats)
	{
		// すべてのボタンをチェックする
		for (auto& button : format->GetButtonStringToKeyCode())
		{
			// 押下状態を初期化する
			mInputLog.emplace(button.first, 0);
		}
	}
}

void InputDeviceBase::Update()
{
	// デバイス固有の更新処理を呼ぶ
	UpdateDevice();
	
	// すべてのフォーマットをチェックする
	for (auto& format : mFormats)
	{
		// すべてのボタンをチェックする
		for (auto& button : format->GetButtonStringToKeyCode())
		{
			// 現在の押下状態を取得
			int log = mInputLog.at(button.first);

			// もし押されていたら
			if (format->CheckButtonState(button.first))
			{
				// もし前のフレームで押されていなかったらカウントを0にする
				log = std::max(0, log);
				// ボタンが押されたフレーム数をカウントアップ
				log++;
			}
			// もし押されていなかったら
			else
			// ゲーム開始1F目が押されていない瞬間にならないために0かチェック
			if (log != 0)
			{
				// もし前のフレームで押されていたらカウントを0にする
				log = std::min(0, log);
				// ボタンが押されたフレーム数をカウントダウン
				log--;
			}

			// オーバーフローを起こさないように値を収める
			log = Math::Clamp(log, -kMaxLog, kMaxLog);

			// 押下状態を更新
			mInputLog.at(button.first) = log;
		}
	}
}

bool InputDeviceBase::IsHeld(std::string button) const
{
	return mInputLog.at(button) > 0;
}

bool InputDeviceBase::IsPressed(std::string button) const
{
	return mInputLog.at(button) == 1;
}

bool InputDeviceBase::IsReleased(std::string button) const
{
	return mInputLog.at(button) == -1;
}

void InputDeviceBase::AddFormat(std::shared_ptr<InputFormatBase> format)
{
	mFormats.emplace_back(format);
}
