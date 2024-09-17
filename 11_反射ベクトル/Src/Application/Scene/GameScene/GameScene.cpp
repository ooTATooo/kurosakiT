#include "GameScene.h"
#include"../SceneManager.h"

#include "../../main.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include "../../GameObject/Character/MotoSan/MotoSan.h"
#include "../../GameObject/Character/YamaSan/YamaSan.h"
#include "../../GameObject/Reticle/Reticle.h"

void GameScene::Event()
{
	// 現在のオブジェクト数
	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("ObjectListSize:%d\n",m_objList.size());

}

void GameScene::Init()
{
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	AddObject(camera);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	AddObject(ground);

	std::shared_ptr<Tank> tank = std::make_shared<Tank>();
	AddObject(tank);

	std::shared_ptr<MotoSan> moto = std::make_shared<MotoSan>();
	moto->SetPos({ 10,0,10 });
	AddObject(moto);

	std::shared_ptr<YamaSan> yama = std::make_shared<YamaSan>();
	yama->SetPos({ -10,0,10 });
	AddObject(yama);

	std::shared_ptr<Reticle> reticle = std::make_shared<Reticle>();
	AddObject(reticle);

	moto->SetTarget(tank);
	yama->SetTarget(tank);
	camera->SetTarget(tank);
	tank->SetCamera(camera);
}
