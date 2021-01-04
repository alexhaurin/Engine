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

	//Load
	if (!robotoFont.loadFromFile("Roboto-Bold.ttf")) {
		std::cout << "Failed to font" << std::endl;
	}

	sf::Texture m_playerTexture;
	if (!m_playerTexture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("Images/BrickCircle.png")) {
		std::cout << "Failed to load brick" << std::endl;
	}

	//Spawn
	m_player = CreatePlayer(m_playerTexture, sf::Vector2f(100.0, 100.0));
	auto enemy1 = CreateEnemy(enemyTexture, sf::Vector2f(200.0, 200.0));
	auto enemy2 = CreateEnemy(enemyTexture, sf::Vector2f(300.0, 300.0));

	//Push
	m_enemyList.push_back(enemy1);
	m_enemyList.push_back(enemy2);

	m_entityList.push_back(m_player);
	for (auto enemy : m_enemyList) {
		m_entityList.push_back(enemy);
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

	m_color[0] = 0;
	m_color[1] = 255;

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

	//Detect Collisions
	for (auto enemy : m_enemyList) {
		if (Math::CheckCircleCollisions(enemy->GetPosition(), enemy->GetDimensions().x/2, m_player->GetPosition(), m_player->GetDimensions().x/2)) {

			m_player->SetIsTouchingEnemy(true);
			m_color[0] = 255;
			m_color[1] = 0;
		}
		else {
			m_player->SetIsTouchingEnemy(false);
		}
	}

	for (auto enemy : m_enemyList) {
		for (auto bullet : m_bulletList) {
			if (Math::CheckCircleCollisions(bullet->GetPosition(), bullet->GetDimensions().x/2, enemy->GetPosition(), enemy->GetDimensions().x/2)) {
				m_color[2] = 200;
				if (IsValid(&*enemy)) {
					enemy->Destroy();
				}
				if (IsValid(&*bullet)) {
					bullet->Destroy();
				}
			}
			else {
				m_color[2] = 0;
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
		auto bullet = (m_player->Shoot());
		m_bulletList.push_back(bullet);
		m_entityList.push_back(bullet);
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

std::shared_ptr<Player> Game::CreatePlayer(sf::Texture& in_texture, const sf::Vector2f& in_position) {
	auto m_player = SpawnWithSetup<Player>(shared_from_this(), [this, in_texture, in_position](Player* in_player) {
		in_player->SetGame(shared_from_base<Game>());
		in_player->SetTexture(in_texture);
		in_player->SetPosition(in_position);
		in_player->SetDimensions(sf::Vector2f(100.0, 100.0));;
	});
	return m_player;
}

std::shared_ptr<Enemy> Game::CreateEnemy(sf::Texture& in_texture, const sf::Vector2f in_position) {
	auto enemy = SpawnWithSetup<Enemy>(shared_from_this(), [this, in_texture, in_position](Enemy* in_enemy) {
		in_enemy->SetGame(shared_from_base<Game>());
		in_enemy->SetTexture(in_texture);
		in_enemy->SetPosition(in_position);
		in_enemy->SetDimensions(sf::Vector2f(100.0, 100.0));;
	});
	return enemy;
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