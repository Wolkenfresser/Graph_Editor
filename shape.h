#pragma once

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>

class Shape {
public:
    virtual ~Shape() {}
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(float dx, float dy) = 0;
    virtual bool isActive() const = 0;
    virtual void setActive(bool active) = 0;
    virtual void setColor(const sf::Color& color) = 0;
    virtual sf::Color getColor() const = 0;
    virtual void rotate(float angle) = 0;
    virtual void resize(float factor) = 0;
    virtual bool contains(float x, float y) = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void deleteShape() = 0;
};

class Line : public Shape {
public:
    Line(float x1, float y1, float x2, float y2);
    void draw(sf::RenderWindow& window) override;
    void move(float dx, float dy) override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setColor(const sf::Color& color) override;
    sf::Color getColor() const override;
    void rotate(float angle) override;
    void resize(float factor) override;
    bool contains(float x, float y) override;
    std::unique_ptr<Shape> clone() const override; 
    void setPosition(float x, float y) override;
    void deleteShape() override;
private:
    float m_x1, m_y1, m_x2, m_y2;
    bool m_active;
    sf::Color m_color;
};

class Circle : public Shape {
public:
    Circle(float x, float y, float radius, const sf::Color& color = sf::Color::White);
    void draw(sf::RenderWindow& window) override;
    void move(float dx, float dy) override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setColor(const sf::Color& color) override;
    sf::Color getColor() const override;
    void rotate(float angle) override;
    void resize(float factor) override;
    bool contains(float x, float y) override;
    std::unique_ptr<Shape> clone() const override; 
    void setPosition(float x, float y) override; 
    void deleteShape() override;
private:
    float m_x, m_y, m_radius;
    bool m_active;
    sf::Color m_color;
};

class Square : public Shape {
public:
    Square(float x, float y, float size, const sf::Color& color = sf::Color::White);
    void draw(sf::RenderWindow& window) override;
    void move(float dx, float dy) override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setColor(const sf::Color& color) override;
    sf::Color getColor() const override;
    void rotate(float angle) override;
    void resize(float factor) override;
    bool contains(float x, float y) override;
    std::unique_ptr<Shape> clone() const override; 
    void setPosition(float x, float y) override; 
    void deleteShape() override;
private:
    float m_x, m_y, m_size;
    bool m_active;
    sf::Color m_color;
    float m_rotation;
};

class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height, const sf::Color& color = sf::Color::White);
    void draw(sf::RenderWindow& window) override;
    void move(float dx, float dy) override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setColor(const sf::Color& color) override;
    sf::Color getColor() const override;
    void rotate(float angle) override;
    void resize(float factor) override;
    bool contains(float x, float y) override;
    std::unique_ptr<Shape> clone() const override; 
    void setPosition(float x, float y) override; 
    void deleteShape() override;
private:
    float m_x, m_y, m_width, m_height;
    bool m_active;
    sf::Color m_color;
    float m_rotation;
};