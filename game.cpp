#include "game.h"
#include "VectorMath.h"

Game::Game() {

	std::cout << "Game created" << std::endl;
}

Game::~Game() {

	std::cout << "Game deleted" << std::endl;
}

void Game::Initialize() {
	
	Object::Initialize();

	m_dimensions = sf::Vector2f(1200.0, 800.0);
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_dimensions.x, m_dimensions.y), "Engine2");
	std::srand(time(NULL));

	//Load
	if (!robotoFont.loadFromFile("Roboto-Bold.ttf")) {
		std::cout << "Failed to font" << std::endl;
	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("Images/BrickCircle.png")) {
		std::cout << "Failed to load brick" << std::endl;
	}
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("Images/krabbyPatty.jpg")) {
		std::cout << "Failed to load burger" << std::endl;
	}

	//Spawn
	m_player = CreatePlayer(playerTexture, sf::Vector2f(100.0, 100.0), sf::Vector2f(100.0, 100.0));

	auto enemy1 = CreateEnemy(enemyTexture, sf::Vector2f(100.0, 100.0), sf::Vector2f(200.0, 200.0));
	m_enemyList.push_back(enemy1);

	for (int i = 0; i < 15; i++) {
		auto bullet = CreateBullet(bulletTexture, sf::Vector2f(50.0, 50.0), sf::Vector2f(std::rand() % 1000, std::rand() % 600));
		m_bulletList.push_back(bullet);
	}

	//Push
	m_entityList.push_back(m_player);
	for (auto enemy : m_enemyList) {
		m_entityList.push_back(enemy);
	}
	for (auto bullet : m_bulletList) {
		m_entityList.push_back(bullet);
	}
}

void Game::Destroy() {

	Object::Destroy();

	std::cout << "Game destroyed" << std::endl;

}

void Game::Run() {

	SetFramerate(60);
	while (m_window->isOpen()) {
		auto startTime = std::chrono::high_resolution_clock::now();
		HandleEvents();
		Update(dt);
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = startTime - endTime;

		if (deltaTime < m_targetTime) {
			auto remainingTime = m_targetTime - deltaTime - std::chrono::milliseconds(5);
			if (remainingTime > std::chrono::milliseconds(0)) {
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < m_targetTime) {}
			}
		}
		dt = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count();
		//std::cout << dt << std::endl;
	}
}

void Game::HandleEvents() {

	sf::Event event;

	while (m_window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_window->close();
			Destroy();
			break;
		case sf::Event::Resized:	
			break;
		case sf::Event::KeyPressed:
			m_inputBool = true;
			m_inputState.CheckKeyboardInputs();
		case sf::Event::KeyReleased:
			m_inputState.CheckKeyboardInputs();
		}
	}
}

void Game::Update(double in_dt)
{
	//Update
	for (auto entity : m_entityList) {
		entity->Update(in_dt);
	}

	//Check if out of screen
	if (!Math::CheckRectCollisions(m_player->GetPosition(), m_player->GetDimensions(), sf::Vector2f(m_dimensions.x/2, m_dimensions.y/2), m_dimensions)) {
		//Loop around
		if (m_player->GetPastDirection().x > 0) {
			m_player->SetPosition(sf::Vector2f(0 - (m_player->GetDimensions().x / 2), m_player->GetPosition().y));
		}
		else if (m_player->GetPastDirection().x < 0) {
			m_player->SetPosition(sf::Vector2f(m_dimensions.x + (m_player->GetDimensions().x / 2), m_player->GetPosition().y));
		}

		if (m_player->GetPastDirection().y < 0) {
			m_player->SetPosition(sf::Vector2f(m_player->GetPosition().x, m_dimensions.y + (m_player->GetDimensions().y / 2)));
		}
		else if (m_player->GetPastDirection().y > 0) {
			m_player->SetPosition(sf::Vector2f(m_player->GetPosition().x, 0 - (m_player->GetDimensions().y / 2)));
		}
	}

	//Detect Collisions:
	//Enemies
	for (auto enemy : m_enemyList) {
		//Enemy and player
		auto playerIsTouching = Math::CheckCircleCollisions(enemy->GetPosition(), enemy->GetDimensions().x / 2, m_player->GetPosition(), m_player->GetDimensions().x / 2); 
		m_player->SetIsTouchingEnemy(playerIsTouching);

		//Enemy and bullet
		for (auto bullet : m_bulletList) {
			if (bullet->GetState() == eBulletStates::shot && bullet->GetInstigator() != enemy) {
				if (Math::CheckCircleCollisions(bullet->GetPosition(), bullet->GetDimensions().x / 2, enemy->GetPosition(), enemy->GetDimensions().x / 2)) {
					enemy->OnBulletHit();

					if (IsValid(&*enemy) && enemy->GetHealth() <= 0) {
						enemy->Destroy();
					}
					if (IsValid(&*bullet)) {
						bullet->Destroy();
					}
				}
			}
		}
	}

	//Player
	for (auto bullet : m_bulletList) {
		if (bullet->GetState() == eBulletStates::neutral) {
			if (Math::CheckCircleCollisions(bullet->GetPosition(), bullet->GetDimensions().x / 2, m_player->GetPosition(), m_player->GetDimensions().x / 2)) {
				m_player->AddToAmmoList(bullet);
			}
		}
		else if (bullet->GetState() == eBulletStates::shot && bullet->GetInstigator() != m_player) {
			if (Math::CheckCircleCollisions(bullet->GetPosition(), bullet->GetDimensions().x / 2, m_player->GetPosition(), m_player->GetDimensions().x / 2)) {
				bullet->Destroy();
			}
		}
	}

	//Destroy Invalid Entitys
	auto EraseInvalid = [](auto& entityList) {
		entityList.erase(std::remove_if(entityList.begin(), entityList.end(), [](auto entity) {
			return !IsValid(&*entity);
		}), entityList.end());
	};

	EraseInvalid(m_entityList);
	EraseInvalid(m_enemyList);
	EraseInvalid(m_bulletList);
	

	//Inputs
	if (m_inputState.keySpacePressed) {
		m_player->Shoot();
	}

	if (m_inputState.keyUpPressed) {
		m_player->m_direction += sf::Vector2f(0, -1);
	}
	if (m_inputState.keyLeftPressed) {
		m_player->m_direction += sf::Vector2f(-1, 0);
	}
	if (m_inputState.keyDownPressed) {
		m_player->m_direction += sf::Vector2f(0, 1);
	}
	if (m_inputState.keyRightPressed) {
		m_player->m_direction += sf::Vector2f(1, 0);
	}

	m_player->Move(m_player->m_direction, m_player->GetSpeed() * in_dt);
}

void Game::Draw()
{
	m_window->clear(sf::Color(m_color[0], m_color[1], m_color[2]));

	//Text
	sf::Text text("text", robotoFont, 50);
	text.setPosition(700, 700);

	m_window->draw(text);

	//Entities
	for (auto entity : m_entityList) {
		entity->Draw(m_window);
	}

	m_window->display();
}

std::shared_ptr<Player> Game::CreatePlayer(sf::Texture& in_texture, const sf::Vector2f& in_dimensions, const sf::Vector2f& in_position) {
	auto player = SpawnWithSetup<Player>(shared_from_this(), [this, in_texture, in_dimensions, in_position](Player* in_player) {
		in_player->SetGame(shared_from_base<Game>());
		in_player->SetTexture(in_texture);
		in_player->SetDimensions(in_dimensions);
		in_player->SetPosition(in_position);
	});
	return player;
}

std::shared_ptr<Enemy> Game::CreateEnemy(sf::Texture& in_texture, const sf::Vector2f& in_dimensions, const sf::Vector2f& in_position) {
	auto enemy = SpawnWithSetup<Enemy>(shared_from_this(), [this, in_texture, in_dimensions, in_position](Enemy* in_enemy) {
		in_enemy->SetGame(shared_from_base<Game>());
		in_enemy->SetTexture(in_texture);
		in_enemy->SetDimensions(in_dimensions);
		in_enemy->SetPosition(in_position);
	});
	return enemy;
}

std::shared_ptr<Bullet> Game::CreateBullet(sf::Texture& in_texture, const sf::Vector2f& in_dimensions, const sf::Vector2f& in_position) {
	auto bullet = SpawnWithSetup<Bullet>(shared_from_this(), [this, in_texture, in_dimensions, in_position](Bullet* in_bullet) {
		in_bullet->SetTexture(in_texture);
		in_bullet->SetPosition(in_position);
		in_bullet->SetDimensions(in_dimensions);
	});
	return bullet;
}

////////////////////Input Class///////////////////
void Input::ClearInputs()
{
	keyUpPressed = false;
	keyLeftPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keySpacePressed = false;
}

void Input::CheckKeyboardInputs()
{
	ClearInputs();

	keyUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	keyLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	keyDownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	keyRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	keySpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}