#pragma once
#include "enemy.h"
#include "player.h"
#include <chrono>
#include <thread>

class Input {
public:
	void ClearInputs();
	void CheckKeyboardInputs();

	bool keyRightPressed = false;
	bool keyLeftPressed = false;
	bool keyUpPressed = false;
	bool keyDownPressed = false;
	bool keySpacePressed = false;
};

class Game : public Object {
public:
	Game();
	~Game();
	void Initialize();
	void Destroy();

	void Run();
	void HandleEvents();
	void Update(double in_dt);
	void Draw();
	
	std::shared_ptr<Player> CreatePlayer(sf::Texture& in_texture, const sf::Vector2f& in_position);
	std::shared_ptr<Enemy> CreateEnemy(sf::Texture& in_texture, const sf::Vector2f in_position);

	double GetFramerate() const { return dt; }
	std::shared_ptr<Player> GetPlayer() const { return m_player; }
	sf::Vector2f GetDimensions() const { return m_dimensions;  }

	void SetFramerate(int in_framerate) { m_targetTime = std::chrono::milliseconds(1000 / in_framerate); }
	void SetWindowSize(const sf::Vector2u& in_size) { m_window->setSize(in_size); }
private:
	std::shared_ptr<sf::RenderWindow> m_window;
	std::chrono::milliseconds m_targetTime;
	double dt = 1.0;

	std::shared_ptr<Player> m_player;

	std::vector<std::shared_ptr<Entity>> m_entityList;
	std::vector<std::shared_ptr<Bullet>> m_bulletList;
	std::vector<std::shared_ptr<Enemy>> m_enemyList;
	std::vector<std::shared_ptr<Bullet>> m_bulletDestroyList;
	std::vector<std::shared_ptr<Enemy>> m_enemyDestroyList;

	std::vector<int> m_color{ 0, 255, 0 };
	sf::Vector2f m_dimensions;
	sf::Font robotoFont;

	Input m_inputState;
	bool m_inputBool;
};