#include "shape.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Line::Line(float x1, float y1, float x2, float y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_active(false), m_color(sf::Color::White) {}

void Line::draw(sf::RenderWindow& window) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(m_x1, m_y1), m_color),
        sf::Vertex(sf::Vector2f(m_x2, m_y2), m_color)
    };

    window.draw(line, 2, sf::Lines);
}

void Line::move(float dx, float dy) {
    m_x1 += dx;
    m_y1 += dy;
    m_x2 += dx;
    m_y2 += dy;
}

bool Line::isActive() const {
    return m_active;
}

void Line::setActive(bool active) {
    m_active = active;
}

void Line::setColor(const sf::Color& color) {
    m_color = color;
}

sf::Color Line::getColor() const {
    return m_color;
}

void Line::rotate(float angle) {
    float centerX = (m_x1 + m_x2) / 2;
    float centerY = (m_y1 + m_y2) / 2;

    float newX1 = centerX + (m_x1 - centerX) * cos(angle) - (m_y1 - centerY) * sin(angle);
    float newY1 = centerY + (m_x1 - centerX) * sin(angle) + (m_y1 - centerY) * cos(angle);
    float newX2 = centerX + (m_x2 - centerX) * cos(angle) - (m_y2 - centerY) * sin(angle);
    float newY2 = centerY + (m_x2 - centerX) * sin(angle) + (m_y2 - centerY) * cos(angle);

    m_x1 = newX1;
    m_y1 = newY1;
    m_x2 = newX2;
    m_y2 = newY2;
}

void Line::resize(float factor) {
    float centerX = (m_x1 + m_x2) / 2;
    float centerY = (m_y1 + m_y2) / 2;

    m_x1 = centerX + (m_x1 - centerX) * factor;
    m_y1 = centerY + (m_y1 - centerY) * factor;
    m_x2 = centerX + (m_x2 - centerX) * factor;
    m_y2 = centerY + (m_y2 - centerY) * factor;
}

bool Line::contains(float x, float y) {
    float numerator = fabs((m_y2 - m_y1) * x - (m_x2 - m_x1) * y + m_x2 * m_y1 - m_y2 * m_x1);
    float denominator = sqrt(pow(m_y2 - m_y1, 2) + pow(m_x2 - m_x1, 2));
    float distance = numerator / denominator;
    const float epsilon = 0.0001f; // выбираем значение погрешности
    return distance < epsilon;
}

void Line::setPosition(float x, float y) {
    float dx = x - m_x1;
    float dy = y - m_y1;
    m_x1 = x;
    m_y1 = y;
    m_x2 += dx;
    m_y2 += dy;
}

std::unique_ptr<Shape> Line::clone() const {
    return std::make_unique<Line>(*this); // Создание копии объекта Line
}

void Line::deleteShape() {
    m_active = false;
}

Circle::Circle(float x, float y, float radius, const sf::Color& color)
    : m_x(x), m_y(y), m_radius(radius), m_active(true), m_color(color) {}

void Circle::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(m_radius);
    circle.setPosition(m_x - m_radius, m_y - m_radius);
    circle.setFillColor(m_color);
    window.draw(circle);
}

void Circle::move(float dx, float dy) {
    m_x += dx;
    m_y += dy;
}

bool Circle::isActive() const {
    return m_active;
}

void Circle::setActive(bool active) {
    m_active = active;
}

void Circle::setColor(const sf::Color& color) {
    m_color = color;
}

sf::Color Circle::getColor() const {
    return m_color;
}

void Circle::rotate(float angle) {
    // Круг не изменяет свою форму при вращении
}

void Circle::resize(float factor) {
    m_radius *= factor;
}

bool Circle::contains(float x, float y) {
    float dx = x - m_x;
    float dy = y - m_y;
    return dx * dx + dy * dy <= m_radius * m_radius;
}

std::unique_ptr<Shape> Circle::clone() const {
    return std::make_unique<Circle>(*this); // Create a copy of the Circle object
}

void Circle::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

void Circle::deleteShape() {
    delete this;
}

Square::Square(float x, float y, float size, const sf::Color& color)
    : m_x(x), m_y(y), m_size(size), m_active(true), m_color(color), m_rotation(0.1f) {}

void Square::draw(sf::RenderWindow& window) {
    sf::RectangleShape square(sf::Vector2f(m_size, m_size));
    square.setPosition(m_x, m_y);
    square.setFillColor(m_color);
    square.setRotation(m_rotation);
    window.draw(square);
}

void Square::move(float dx, float dy) {
    m_x += dx;
    m_y += dy;
}

bool Square::isActive() const {
    return m_active;
}

void Square::setActive(bool active) {
    m_active = active;
}

void Square::setColor(const sf::Color& color) {
    m_color = color;
}

sf::Color Square::getColor() const {
    return m_color;
}

void Square::rotate(float angle) {
    m_rotation += 10 * angle;
}

void Square::resize(float factor) {
    m_size *= factor;
}

bool Square::contains(float x, float y) {
    return x >= m_x && x <= m_x + m_size &&
        y >= m_y && y <= m_y + m_size;
}

std::unique_ptr<Shape> Square::clone() const {
    return std::make_unique<Square>(*this); // Create a copy of the Square object
}

void Square::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

void Square::deleteShape() {
    delete this;
}

Rectangle::Rectangle(float x, float y, float width, float height, const sf::Color& color)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_active(true), m_color(color), m_rotation(0.1f) {}

void Rectangle::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.setPosition(m_x, m_y);
    rectangle.setFillColor(m_color);
    rectangle.setRotation(m_rotation);
    window.draw(rectangle);
}

void Rectangle::move(float dx, float dy) {
    m_x += dx;
    m_y += dy;
}

bool Rectangle::isActive() const {
    return m_active;
}

void Rectangle::setActive(bool active) {
    m_active = active;
}

void Rectangle::setColor(const sf::Color& color) {
    m_color = color;
}

sf::Color Rectangle::getColor() const {
    return m_color;
}

void Rectangle::rotate(float angle) {
    m_rotation += 10 * angle;
}

void Rectangle::resize(float factor) {
    m_width *= factor;
    m_height *= factor;
}

bool Rectangle::contains(float x, float y) {
    return x >= m_x && x <= m_x + m_width &&
        y >= m_y && y <= m_y + m_height;
}

std::unique_ptr<Shape> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this); // Create a copy of the Rectangle object
}

void Rectangle::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

void Rectangle::deleteShape() {
    delete this;
}