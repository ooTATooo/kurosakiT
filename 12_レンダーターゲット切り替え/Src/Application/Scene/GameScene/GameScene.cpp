#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include "../../GameObject/Polygon/Polygon.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	AddObject(camera);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	AddObject(ground);

	std::shared_ptr<Tank> tank = std::make_shared<Tank>();
	AddObject(tank);

	std::shared_ptr<Polygon> poly = std::make_shared<Polygon>();
	AddObject(poly);

	camera->SetTarget(tank);
	tank->SetCamera(camera);
}
