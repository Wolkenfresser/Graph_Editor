#include "shape.h"
#include <vector>

int main() {
    // ������������ ��������� ������
    sf::RenderWindow window(sf::VideoMode(800, 600), "����������� ��������");

    std::vector<std::unique_ptr<Shape>> shapes;

    // ������ �������� ��������
    shapes.push_back(std::make_unique<Line>(100, 100, 200, 200));
    shapes.push_back(std::make_unique<Circle>(300, 300, 50));
    shapes.push_back(std::make_unique<Square>(500, 100, 50));
    shapes.push_back(std::make_unique<Rectangle>(100, 500, 50, 100));

    float moveSpeed = 5.0f; // �������� ����������� �����
    int activeShapeIndex = 0; // ������ �������� ������

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // ��������� �������� ��������� ����
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (size_t i = 0; i < shapes.size(); ++i) {
                    if (shapes[i]->contains(mousePos.x, mousePos.y)) {
                        activeShapeIndex = i;
                        break;
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && activeShapeIndex != -1) {
                // ���� ������� �����-�� ������ � ���������� ������� �������, ���������� ��������������� ��������
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    shapes[activeShapeIndex]->move(0, -moveSpeed);
                    break;
                case sf::Keyboard::Down:
                    shapes[activeShapeIndex]->move(0, moveSpeed);
                    break;
                case sf::Keyboard::Left:
                    shapes[activeShapeIndex]->move(-moveSpeed, 0);
                    break;
                case sf::Keyboard::Right:
                    shapes[activeShapeIndex]->move(moveSpeed, 0);
                    break;
                case sf::Keyboard::Equal: // ������� "="
                    shapes[activeShapeIndex]->resize(1.1f); // ��������� ������ �� 10%
                    break;
                case sf::Keyboard::Dash: // ������� "-"
                    shapes[activeShapeIndex]->resize(0.9f); // ��������� ������ �� 10%
                    break;
                case sf::Keyboard::R:
                    shapes[activeShapeIndex]->rotate(0.1f); // ���� ��������, ��������, 0.1 ������ (�������������� 5.7 ��������)
                    break;
                case sf::Keyboard::Delete:
                    // ������� ��������� ������, ���� ��� ����
                    if (activeShapeIndex >= 0 && activeShapeIndex < shapes.size()) {
                        shapes.erase(shapes.begin() + activeShapeIndex);
                        activeShapeIndex = -1; // ����� �������� ������ �� �������
                    }
                    break;
                case sf::Keyboard::C:
                    // ���������� ��������� ������, ���� ��� ����
                    if (activeShapeIndex >= 0 && activeShapeIndex < shapes.size()) {
                        // �������� ����� ��������� ������
                        std::unique_ptr<Shape> shapeCopy = shapes[activeShapeIndex]->clone();

                        // ���������� ����� � ������ �����
                        shapes.push_back(std::move(shapeCopy));
                    }
                    break;
                }
            }
        }

        window.clear();

        // ��������� ���� �����
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (i == activeShapeIndex && shapes[i]->isActive()) {
                // ������������ �������� ������ � ������ ������
                // ��������, ������� ������
                sf::Color originalColor = shapes[i]->getColor();
                shapes[i]->setColor(sf::Color::Red);
                shapes[i]->draw(window);
                shapes[i]->setColor(originalColor); // ���������� ������������ ����
            }
            else {
                shapes[i]->draw(window);
            }
        }

        window.display();
    }

    return 0;
}