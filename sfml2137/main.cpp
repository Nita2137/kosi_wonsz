//#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Main.hpp>
//#include <SFML/Network.hpp>
//#include <ogg>
#include <iostream>
//#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>
#include <math.h>
#include "Ball.h"
#include "Square.h"

using namespace sf;
using namespace std;

bool isOver = false;
int score = 7;

void Death()
{
	if (score == 100) { cout << "***win***" << endl; }
	else cout << "***game over***" << endl;
	cout << "***score: " << score << " ***" << endl;
	isOver = true;
}



int main()
{
	int windowX = 900, windowY = 900;
	RenderWindow win{ VideoMode(windowX, windowY), "DVD" };
	win.setFramerateLimit(100);
	Event e;

	Font font;
	if (!font.loadFromFile("C:/Windows/fonts/arial.ttf"))
		cout << "CRITICAL error can't load font" << endl;
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(200);
	scoreText.setFillColor(Color(70,70,70));
	scoreText.setStyle(Text::Bold);
	scoreText.setOrigin(-20, 0);
	queue<Vector2i> snakePos;
	int applesCount = 5;
	vector<Vector2i> applesPos(applesCount);
	Vector2f snakeSize = Vector2f(30, 30);
	Color snakeColorHead = Color(74, 237, 104);
	vector<Color> appleColor = { Color::Red }; //Color::Blue };
	vector<Color> snakeColors = { Color(0, 100, 18), Color(0, 150, 28) }; //, Color::Yellow, Color::Red, Color::Blue, Color::Green};
	SoundBuffer eatingAudio;
	Sound audio;
	map<char, String> snakeHeadPath;
	snakeHeadPath['u'] = "resources/textures/kosiHead_u.png";
	snakeHeadPath['d'] = "resources/textures/kosiHead_d.png";
	snakeHeadPath['r'] = "resources/textures/kosiHead_r.png";
	snakeHeadPath['l'] = "resources/textures/kosiHead_l.png";
	String applePath = "resources/textures/dudus.png";
	String snakePath = "resources/textures/kosiBody.png";
	char direction = 'd';
	snakePos.push(Vector2i(300, 240));
	snakePos.push(Vector2i(300, 210));
	snakePos.push(Vector2i(300, 180));
	snakePos.push(Vector2i(300, 150));
	snakePos.push(Vector2i(300, 120));
	snakePos.push(Vector2i(300, 90));
	snakePos.push(Vector2i(300, 60));
	snakePos.push(Vector2i(0, 0));

	if (!eatingAudio.loadFromFile("resources/audio/eating.ogg")) { cout << "CRITICAL can't load audio 'eating.ogg'" << endl; }
	audio.setBuffer(eatingAudio);

	int clockInterval = 10;
	int clock = 0;
	while (true)
	{
		if (score == 100) { Death(); }
		if (score % 10 == 0 && score != 100 && clockInterval !=  10-score/10) {
			clockInterval = 10 - score / 10;
			cout << "new logic interval: " << clockInterval << endl;
		}
		

		clock++;
		win.clear(Color::Black);
		win.pollEvent(e);

		if (e.type == Event::Closed) { win.close(); break; }
		
		//audio.play();

		//logic
		int newPosX = 0;
		int newPosY = 0;
		if (Keyboard::isKeyPressed(Keyboard::Up) && direction != 'd') { direction = 'u'; }
		else if (Keyboard::isKeyPressed(Keyboard::Down) && direction != 'u') { direction = 'd'; }
		else if (Keyboard::isKeyPressed(Keyboard::Left) && direction != 'r') { direction = 'l'; }
		else if (Keyboard::isKeyPressed(Keyboard::Right) && direction != 'l') { direction = 'r'; }
		
		if (direction == 'u')
			newPosY = -snakeSize.x;
		else if (direction == 'd')
			newPosY = snakeSize.x;
		else if (direction == 'l')
			newPosX = -snakeSize.x;
		else if (direction == 'r')
			newPosX = snakeSize.x;
		//
		
			scoreText.setString(to_string(score));
			win.draw(scoreText);
			//

			//spawning apple
			for (int i = 0; i < applesCount; i++)
			{
				if (applesPos[i] == Vector2i(0, 0))
				{
					bool isOK = false;
					Vector2i choosedPos;
					while (isOK != true)
					{
						isOK = true;
						int tryX = (rand() % windowY / (int)snakeSize.y) * snakeSize.y;
						int tryY = (rand() % windowY / (int)snakeSize.y) * snakeSize.y;
						queue<Vector2i> spawnPos = snakePos;
						vector<Vector2i> spawnVector;
						choosedPos = Vector2i(tryX, tryY);
						int spawnPosLength = spawnPos.size();
						for (int j = 0; j < spawnPosLength; j++) {
							spawnVector.push_back(spawnPos.front());
							spawnPos.pop();
						}
						for (int j = 0; j < spawnPosLength; j++)
						{
							if (choosedPos == spawnVector[j]) { isOK = false; }
						}
						for (int j = 0; j < applesPos.size(); j++)
						{
							if (choosedPos == applesPos[j]) { isOK = false; }
						}
					}
					applesPos[i] = choosedPos;
					cout << "spawned new dudus Xpos: " << applesPos[i].x << " Ypos: " << applesPos[i].y << endl;
				}
				win.draw(Square(applesPos[i].x, applesPos[i].y, snakeSize, appleColor[i % appleColor.size()], applePath));
			}
			//eating
			for (int i = 0; i < applesCount; i++)
			{
				queue<Vector2i> spawnPos = snakePos;
				vector<Vector2i> spawnVector;
				Vector2i choosedPos = applesPos[i];
				int spawnPosLength = spawnPos.size();
				for (int i = 0; i < spawnPosLength; i++) {
					spawnVector.push_back(spawnPos.front());
					spawnPos.pop();
				}
				for (int j = 0; j < spawnPosLength; j++)
				{
					if (choosedPos == spawnVector[j]) {
						score++; applesPos[i] = Vector2i(0, 0);
						snakePos.push(Vector2i(0, 0));
						//audio.setBuffer(eatingAudio);
						audio.play();
						//snakeColors.push_back(Color::Red);
					}
				}
			}
			//

			//checking death
			if (snakePos.front().x < 0 || snakePos.front().x > windowX) { Death(); }
			if (snakePos.front().y < 0 || snakePos.front().y > windowY) { Death(); }
			queue<Vector2i> deathPos = snakePos;
			vector<Vector2i> deathVector;
			int deathPosLength = deathPos.size();
			for (int i = 0; i < deathPosLength; i++) {
				deathVector.push_back(deathPos.front());
				deathPos.pop();
			}
			for (int i = 0; i < deathPosLength; i++)
			{
				for (int j = 0; j < deathPosLength; j++)
				{
					if (deathVector[i] == deathVector[j] && i != j)
						Death();
				}
			}

			while (isOver == true)
			{
				Event closeEvent;
				win.pollEvent(closeEvent);
				if (closeEvent.type == Event::Closed) { win.close(); return 0; }
			}
			//

			//drawing
			if (clock == clockInterval)
			{
				clock = 0;
				queue<Vector2i> newSnakePos;
				win.draw(Square(snakePos.front().x + newPosX, snakePos.front().y + newPosY,
					snakeSize, snakeColorHead, snakeHeadPath[direction]));
				newSnakePos.push(Vector2i(snakePos.front().x + newPosX, snakePos.front().y + newPosY));
				//cout << "snake length: " << snakePos.size() << " dir: " << direction << " newX: " << newPosX << " newY: " << newPosY << " X: " <<
				//	snakePos.front().x << " Y: " << snakePos.front().y << endl;
				int snakePosLength = snakePos.size();
				for (int j = 0; j < snakePosLength - 1; j++)
				{
					win.draw(Square(snakePos.front().x, snakePos.front().y, snakeSize, snakeColors[j % snakeColors.size()], snakePath));
					//cout << "drawed shape at: X:" << snakePos.front().x << " Y: " << snakePos.front().y << endl;
					newSnakePos.push(snakePos.front());
					snakePos.pop();
				}
				snakePos.pop();
				//

				int newSnakePosLength = newSnakePos.size();
				for (int i = 0; i < newSnakePosLength; i++)
				{
					snakePos.push(newSnakePos.front());
					newSnakePos.pop();
				}
				//cout << "newPos len: " << newSnakePos.size() << " Pos len:" << snakePos.size() << endl;/
			}
			else
			{
				//clock = 0;
				queue<Vector2i> newSnakePos;
				int snakePosLength = snakePos.size();
				win.draw(Square(snakePos.front().x, snakePos.front().y, snakeSize, snakeColorHead, snakeHeadPath[direction]));
				newSnakePos.push(snakePos.front());
				snakePos.pop();
				for (int j = 0; j < snakePosLength-1; j++)
				{
					win.draw(Square(snakePos.front().x, snakePos.front().y, snakeSize, snakeColors[j % snakeColors.size()], snakePath));
					//cout << "drawed shape at: X:" << snakePos.front().x << " Y: " << snakePos.front().y << endl;
					newSnakePos.push(snakePos.front());
					snakePos.pop();
				}

				int newSnakePosLength = newSnakePos.size();
				for (int i = 0; i < newSnakePosLength; i++)
				{
					snakePos.push(newSnakePos.front());
					newSnakePos.pop();
				}
			}
			win.display();
	}

	return 0;
}