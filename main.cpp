#include<iostream>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <conio.h>
#include<cmath>

using namespace sf;

void raycasting() {

}

void range(float player_x, float player_y, float player_a, const char map[], size_t map_w, int i, float j, RectangleShape ground, RenderWindow& window, float vertical, int space, Texture texture) {
	float past_len = 0;
	
	for (float c = 1; c < 20; c += 0.05) {
		
		float x = player_x + c * cos(j * 0.0175);
		float y = player_y + c * sin(j * 0.0175);
		float tseliy_x;
		if (map[int(x) + int(y) * map_w] != ' ')
		{	
			float part_x = x;
			RectangleShape lutch(Vector2f(3, y ));
			RectangleShape line_with_thickness(Vector2f(20.f, 600/ c));
			if (map[int(x) + int(y) * map_w] == '1'){ line_with_thickness.setFillColor(Color(100, 120, 3)); }
			if (map[int(x) + int(y) * map_w] == '2') { line_with_thickness.setFillColor(Color(73, 26, 144)); }
			else{ 
				line_with_thickness.setTexture(&texture, false);
				line_with_thickness.setTextureRect(IntRect(0, 0, 65 * (part_x - int(part_x)), 65));
			}
			line_with_thickness.move(i * 20, 300 - (300 - space * 300)/ c);
			
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
	float vertical = 0;
	const float shag = 0.1;
	int space = 0;
	Texture texture;
	texture.loadFromFile("D:\\step.png");
	
	
	
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		space = 0;
		window.clear(Color(0, 0, 0, 0));
		
		Event event;
		
		
		// Отрисовка спрайта	 
		
		while (window.pollEvent(event))
		{if (event.type == Event::Closed) window.close();}
		if (Keyboard::isKeyPressed(Keyboard::A)) {player_x = player_x - shag*cos((player_a + 30) * 0.0175);player_y = player_y + shag * sin((player_a + 30) * 0.0175);} 
		if (Keyboard::isKeyPressed(Keyboard::D)) {player_x = player_x + shag * cos((player_a + 30) * 0.0175);player_y = player_y - shag * sin((player_a + 30) * 0.0175);}
		if (Keyboard::isKeyPressed(Keyboard::W)) {player_y = player_y + shag * sin((player_a + 30) * 0.0175);player_x = player_x + shag * cos((player_a + 30) * 0.0175);}
		if (Keyboard::isKeyPressed(Keyboard::S)) { player_y = player_y - shag * sin((player_a + 30) * 0.0175);player_x = player_x - shag * cos((player_a + 30) * 0.0175); }
		if (Keyboard::isKeyPressed(Keyboard::Q)) {player_a = player_a - 0.5;}
		if (Keyboard::isKeyPressed(Keyboard::E)) {player_a = player_a + 0.5;}
		std::cout << shag * cos(player_a * 0.0175) << " " <<  shag * sin(player_a * 0.0175) << std::endl;
		//настройка
		if (Keyboard::isKeyPressed(Keyboard::R)) { vertical = vertical + 1;}
		if (Keyboard::isKeyPressed(Keyboard::T)) { vertical = vertical - 1; }
		if (Keyboard::isKeyPressed(Keyboard::Space)) {space = 1;}

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
			range(player_x, player_y, player_a, map, map_w, i, j, ground, window, vertical,space, texture);
		}
		/* 
		RectangleShape shape1(Vector2f(100, 100));
		
		shape1.move(0, 0);
		shape1.setFillColor(Color(225, 225, 225));
		window.draw(shape1);*/
		// Отрисовка окна	
		window.display();
	}
	return 0;
}
