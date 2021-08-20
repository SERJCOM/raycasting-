#include<iostream>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <conio.h>


using namespace sf;

void raycasting() {

}

void range(float player_x, float player_y, float player_a, const char map[], size_t map_w, int i, float j, RectangleShape ground, RenderWindow& window, float nastroyka) {
	for (float c = 1; c < 20; c += 0.05) {
		
		float x = player_x + c * cos(j * 0.0175);
		float y = player_y + c * sin(j * 0.0175);
		
		if (map[int(x) + int(y) * map_w] != ' ')
		{
			RectangleShape lutch(Vector2f(3, y * nastroyka));
			RectangleShape line_with_thickness(Vector2f(20.f, 600 / c));
			line_with_thickness.setFillColor(Color(15 * (c + 20), 180, 140));
			line_with_thickness.move(i * 20, 300 - 300 / c);
			lutch.move(player_x * 16, player_y * 16);
			lutch.rotate(j - 60);
			window.draw(lutch);
			window.draw(line_with_thickness);
			break;
		}
	}
}

float ukaz_karti_x(float player_a, float length) {
	return cos(player_a * 0.0175) * length;
}
float ukaz_karti_y(int player_a, float length) {
	return sin(player_a * 0.0175) * length;
}

int main()
{	
	
	float map_w = 16; // map width
	const size_t map_h = 16; // map height
	const char map[] = "0000222222220000"\
		"1              0"\
		"1      11111   0"\
		"1     0        0"\
		"0     0  1110000"\
		"0     3        0"\
		"0   10000      0"\
		"0   0   11100  0"\
		"0   0   0      0"\
		"0   0   1  00000"\
		"0       1      0"\
		"2       1      0"\
		"0       0      0"\
		"0 0000000      0"\
		"0              0"\
		"0002222222200000"; // our game map

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 800), "raycasting");
	RectangleShape ground(Vector2f(60.f, 600.f));

	int range_mas[60];
	float player_x = 5;
	float player_y = 1;
	float player_a = 0;
	float nastroyka = 1;
	const float shag = 0.5;
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		window.clear(Color(250, 220, 100, 0));
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player_x = player_x - shag*cos(player_a * 0.0175);
		} //первая координата Х отрицательна =>идём влево
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player_x = player_x + shag * cos(player_a * 0.0175);
		} //первая координата Х положительна =>идём вправо
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player_y = player_y + shag * sin(player_a * 0.0175);
		}
		
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player_y = player_y - shag * sin(player_a * 0.0175);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			player_a = player_a - 0.5;
		}
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			player_a = player_a + 0.5;
		}
		if (Keyboard::isKeyPressed(Keyboard::T)) {
			nastroyka = nastroyka - 1;
			
		}
		std::cout <<"НАСТРОЙКА" << nastroyka << std::endl;
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			nastroyka = nastroyka + 1;
		}

		const int numindex = 256;
		float wide_tsikl = 0;
		float hight_tsikl = 0;
		float length_ukazatel = 50;
		int j = 0;
		
		for (float i = 0; i < numindex; ++i) {
			hight_tsikl = hight_tsikl + 1;
			
			
			if (int(i) % 16 == 0) {
				wide_tsikl++;
				hight_tsikl = 1.0;
			}
			if (int(wide_tsikl) % 17 == 0) {
				wide_tsikl = 1.0;
			}
			RectangleShape rectangle(Vector2f(16.f, 15.f));
			RectangleShape rectangle2(Vector2f(5.f, 5.f));
			
			rectangle.move(hight_tsikl * 16, wide_tsikl * 15);
			
			if (map[int(i)] == ' ') {
				rectangle.setFillColor(Color(0, 0, 0));
			}
			if (map[int(i)] != ' ') {
				rectangle.setFillColor(Color(175, 180, 240));
			}
			
			//window.draw(rectangle3);
			window.draw(rectangle);
			window.draw(rectangle2);
			
		}
		
		int i = 0;
		for (float j = player_a; j < player_a + 60; j++) {
			i++;
			range(player_x, player_y, player_a, map, map_w, i, j, ground, window, nastroyka);
		}
		// Отрисовка окна	
		window.display();
	}
	return 0;
}
