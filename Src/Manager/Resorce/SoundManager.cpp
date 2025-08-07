#include <DxLib.h>
#include "../../Application.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();
}

SoundManager& SoundManager::GetInstance(void)
{
	return *instance_;
}

void SoundManager::Init(void)
{
	//BGM��SE�ɕ�����
	soundType_[SOUND_TYPE::BGM].push_back(SRC::TITLE_BGM);
	soundType_[SOUND_TYPE::SE].push_back(SRC::ENTER_SOUND);
	//�ő�Đ���������������
	for (int i = 0; i < static_cast<int>(SRC::MAX);i++)
	{
		//�������ł��ׂẲ���������1�����Ȃ�Ȃ��悤�ɂ���
		maxPlayNum.emplace(static_cast<SRC>(i), 1);
		playMap_.emplace(static_cast<SRC>(i), std::vector<std::shared_ptr<Sound>>{});
	}


	std::shared_ptr<Sound> res;

	res = std::make_unique<Sound>(Sound::TYPE::SOUND_2D, Application::PATH_SOUND_BGM + "TitleBGM.mp3");
	res->ChengeMaxVolume(1.0f);
	loadMap_.emplace(SRC::TITLE_BGM, std::move(res));
}

void SoundManager::Release(void)
{
	for (auto& p : loadMap_)
	{
		p.second->Release();
	}

	loadMap_.clear();
	InitSoundMem();
}

void SoundManager::Destroy(void)
{
	Release();
	loadMap_.clear();
	delete instance_;
}

bool SoundManager::Play(SRC src, Sound::TIMES times)
{
	
	const auto& lPair = loadMap_.find(src);
	if (lPair != loadMap_.end())
	{
		if (!lPair->second->CheckLoad())
		{
			lPair->second->Load();
		}
		if (playMap_[src].size() < maxPlayNum[src])
		{
			std::shared_ptr<Sound>sound(lPair->second);
			//sound = lPair->second;
			sound->DuplicateSound();
			bool isPlay = sound->Play(times);
			playMap_[src].push_back(sound);

			return isPlay;
		}
		else
		{
			for (auto& plays : playMap_[src])
			{
				if (plays->CheckMove())
				{
					continue;
				}
				if (plays->Play(times))
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

bool SoundManager::Play(SRC src, Sound::TIMES times, VECTOR pos, float radius)
{
	const auto& lPair = loadMap_.find(src);
	if (lPair != loadMap_.end())
	{
		if (!lPair->second->CheckLoad())
		{
			lPair->second->Load();
		}
		if (playMap_[src].size() < maxPlayNum[src])
		{
			std::shared_ptr<Sound>sound(lPair->second);
			//sound = lPair->second;
			sound->DuplicateSound();
			bool isPlay = sound->Play(pos, radius, times);
			playMap_[src].push_back(sound);

			return isPlay;
		}
		else
		{
			for (auto& plays : playMap_[src])
			{
				if (plays->CheckMove())
				{
					continue;
				}
				if (plays->Play(pos, radius, times))
				{
					return true;
				}
			}
			return false;
		}
		return lPair->second->Play(pos,radius,times);
	}
	return false;
}

void SoundManager::Stop(SRC src)
{
	const auto& lPair = playMap_.find(src);
	if (lPair != playMap_.end())
	{
		for (auto& sound : lPair->second)
		{
			sound->Stop();
		}
	}
}

bool SoundManager::CheckMove(SRC src)
{
	const auto& lPair = playMap_.find(src);
	if (lPair != playMap_.end())
	{
		for (auto& sound : lPair->second)
		{
			if (sound->CheckMove())
			{
				return true;
			}
		}
	}
	return false;

}

void SoundManager::ChengeVolume(SRC src, float per)
{
	const auto& lPair = playMap_.find(src);
	if (lPair != playMap_.end())
	{
		for (auto& sound : lPair->second)
		{
			sound->ChengeVolume(per);
		}
	}
}

void SoundManager::Set3DListenPosAndFrontPos(VECTOR pos, VECTOR frontPos)
{
	Set3DSoundListenerPosAndFrontPos_UpVecY(pos, frontPos);
}
