#include <SFML/Graphics.hpp>
using namespace sf; // подключаем пространство имен sf

Color* fillColor = new Color(255, 255, 255);
Color* lineColor = new Color(0, 0, 0);
Color* textColor = new Color(255, 255, 255);
Color* backgroundColor = new Color(190, 190, 190);

void setTextColor(int r, int g, int b, int alf = 255) {
	delete textColor;
	textColor = new Color(r, g, b, alf);
}

void setFillColor(int r, int g, int b, int alf = 255) {
	delete fillColor;
	fillColor = new Color(r, g, b, alf);
}

void setLineColor(int r, int g, int b, int alf = 255) {
	delete lineColor;
	lineColor = new Color(r, g, b, alf);
}

void setBackgroundColor(int r, int g, int b, int alf = 255) {
	delete backgroundColor;
	backgroundColor = new Color(r, g, b, alf);
}

void clear(RenderWindow& w) {
	w.clear(*backgroundColor);
}

void pause(int millisec) {
	sleep((milliseconds(millisec)));
}

void circle(RenderWindow& w, float diametr, float x, float y, float line = 0) {
	CircleShape circle(diametr / 2);
	circle.setFillColor(*fillColor);
	circle.setOutlineThickness(line);
	circle.setOutlineColor(*lineColor); // устанавливаем цвет контура
	circle.move(x, y); // перемещаем наш круг для корректного отображения в окне
	w.draw(circle); // отрисовка круга
}

void figure(RenderWindow& w, float diametr, int k, float x, float y, float line = 0) {
	CircleShape circle(diametr / 2, k);
	circle.setFillColor(*fillColor);
	circle.setOutlineThickness(line);
	circle.setOutlineColor(*lineColor); // устанавливаем цвет контура
	circle.move(x, y); // перемещаем наш круг для корректного отображения в окне
	w.draw(circle); // отрисовка круга
}

void rectangle(RenderWindow& w, float width, float height, float x, float y, float line = 0) {
	RectangleShape rectangle(Vector2f(width, height));
	// Перемещаем его в нижний ряд справа от многоугольника
	rectangle.move(x, y);
	rectangle.setFillColor(*fillColor);
	rectangle.setOutlineThickness(line);
	rectangle.setOutlineColor(*lineColor);
	w.draw(rectangle);
}

//void drawtext(RenderWindow& w, const char* txt, int size) {
//	sf::Text text;
//	text.setString("txt");
//	text.setCharacterSize(30);
//	text.setPosition(50,50);
//	text.setStyle(sf::Text::Bold);
//	text.setFillColor(*textColor);
//	// Draw it
//	w.draw(text);
//}

