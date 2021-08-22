#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace sf;

const int map_w = 17; // map width
const int map_h = 17; // map height

void raycasting() {

}
void range(float player_x, float player_y, const char map[map_w][map_h], int i, float j, RectangleShape& ground, RenderWindow& window, float nastroyka) {
	for (float c = 1; c < 20; c += 0.05) {
		float x = player_x + c * cos(j / 180 * 3.145926);
		float y = player_y + c * sin(j / 180 * 3.145926);
		if (map[int(x)][int(y)] != ' ')
		{
			RectangleShape line_with_thickness(Vector2f(20.f, 600 / c));
			line_with_thickness.setFillColor(Color(225 - 15 * c, 225 - 15 * c, 225 - 15 * c));
			line_with_thickness.move(i * 20, 300 - 300 / c);
			window.draw(line_with_thickness);
			break;
		}
	}
}

float ukaz_karti_x(float player_a, float length) {
	return cos(player_a / 180 * 3.145926) * length;
}
float ukaz_karti_y(int player_a, float length) {
	return sin(player_a / 180 * 3.145926) * length;
}

int main()
{
	const char map[map_w][map_h] =
	{
		{"0000222222220000"},
		{"1              0"},
		{"1      11111   0"},
		{"1     0        0"},
		{"0     0  1110000"},
		{"0     3        0"},
		{"0   10000      0"},
		{"0   0   11100  0"},
		{"0   0   0      0"},
		{"0   0   1  00000"},
		{"0       1      0"},
		{"2       1      0"},
		{"0       0      0"},
		{"0 0000000      0"},
		{"0              0"},
		{"0002222222200000"}
	};

	RenderWindow window(VideoMode(800, 800), "raycasting");
	RectangleShape ground(Vector2f(60.f, 600.f));
	float player_x = 5;
	float player_y = 1;
	float player_a = 0;
	float nastroyka = 1;
	const float shag = 0.01;

	while (window.isOpen())
	{
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player_x += shag * cos((player_a + 90) / 180 * 3.145926);
			player_y += shag * sin((player_a + 90) / 180 * 3.145926);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player_x += shag * cos((player_a - 90) / 180 * 3.145926);
			player_y += shag * sin((player_a - 90) / 180 * 3.145926);
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player_x += shag * cos(player_a / 180 * 3.145926);
			player_y += shag * sin(player_a / 180 * 3.145926);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player_x -= shag * cos(player_a / 180 * 3.145926);
			player_y -= shag * sin(player_a / 180 * 3.145926);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) player_a = player_a - 0.5;
		if (Keyboard::isKeyPressed(Keyboard::E)) player_a = player_a + 0.5;

		if (Keyboard::isKeyPressed(Keyboard::T)) nastroyka = nastroyka - 1;
		if (Keyboard::isKeyPressed(Keyboard::R)) nastroyka = nastroyka + 1;

		float length_ukazatel = 50;
		int j = 0;
		int i = 0;
		for (float j = player_a - 30; j <= player_a + 30; j++) {
			i++;
			range(player_x, player_y, map, i, j, ground, window, nastroyka);
		}

		for (int i = 0; i < map_h; ++i) {
			for (int j = 0; j < map_w; ++j)
			{
				RectangleShape rectangle(Vector2f(16.f, 16.f));
				RectangleShape rectangle2(Vector2f(5.f, 5.f));

				rectangle.move(i * 16, j * 16);

				if (map[j][i] == ' ') rectangle.setFillColor(Color(0, 0, 0));
				else rectangle.setFillColor(Color(175, 180, 240));

				window.draw(rectangle);
			}
		}
		// Отрисовка окна	
		window.display();
	}
	return 0;

}