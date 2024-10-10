#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	// 暗くする
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 1,-1,1 }, { 0,0,0 });
	KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 0.1,0.1,0.1,1 });

	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	AddObject(camera);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	AddObject(ground);

	std::shared_ptr<Tank> tank = std::make_shared<Tank>();
	AddObject(tank);

	camera->SetTarget(tank);
	tank->SetCamera(camera);
}
