#include<iostream>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <conio.h>


using namespace sf;

float range(int player_x, int player_y, int player_a, const char map[], size_t map_w) {
	float c = 0;
	for (; c < 20; c += .05) {
		float x = player_x + c * cos(player_a);
		float y = player_y + c * sin(player_a);
		if (map[int(x) + int(y) * map_w] != ' ') break;
	}
	return c;
}

int main()
{	
	
	const size_t map_w = 16; // map width
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

	int player_x = 5;
	int player_y = 1;
	int player_a = 0;
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed) window.close();
			}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player_x = player_x - 1;
		} //первая координата Х отрицательна =>идём влево
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player_x = player_x + 1;
		} //первая координата Х положительна =>идём вправо
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player_y = player_y + 1;
		}
		//споминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player_y = player_y - 1;
		}

		const int numindex = sizeof(map) / sizeof(map[0]);
		int wide_tsikl = 0;
		int hight_tsikl = 0;
		//цикл для обзора
		for (int i = 0; i < )
		float range_map = range(player_x, player_y, player_a, map, map_w);
		for (int i = 0; i < numindex; ++i) {
			hight_tsikl = hight_tsikl + 1;
			if (i % 16 == 0) {
				wide_tsikl++;
				hight_tsikl = 1;
			}
			if (wide_tsikl % 17 == 0) {
				wide_tsikl = 1;
			}

			RectangleShape rectangle(Vector2f(16.f, 15.f));
			RectangleShape rectangle2(Vector2f(5.f, 5.f));
			rectangle.move(hight_tsikl * 16, wide_tsikl * 15);

			//std::cout << wide_tsikl << " " << hight_tsikl << std::endl;
			// Устанавливаем ему цвет
			if (map[i] == ' ') {
				rectangle.setFillColor(Color(0, 0, 0));
			}
				
			if (map[i] != ' ') {
				rectangle.setFillColor(Color(175, 180, 240));
			}
			if (player_x + player_y * map_w == i - 1) {				
				rectangle2.move(hight_tsikl * 16, wide_tsikl * 15);
			}
				
				
			window.draw(rectangle);
			window.draw(rectangle2);
			
			
		}
		// Отрисовка окна	
		window.display();
	}

	return 0;
}