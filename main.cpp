#include "shape.h"
#include <vector>

int main() {
    // Отрисовываем выбранную фигуру
    sf::RenderWindow window(sf::VideoMode(800, 600), "Графический редактор");

    std::vector<std::unique_ptr<Shape>> shapes;

    // Пример создания объектов
    shapes.push_back(std::make_unique<Line>(100, 100, 200, 200));
    shapes.push_back(std::make_unique<Circle>(300, 300, 50));
    shapes.push_back(std::make_unique<Square>(500, 100, 50));
    shapes.push_back(std::make_unique<Rectangle>(100, 500, 50, 100));

    float moveSpeed = 5.0f; // Скорость перемещения фигур
    int activeShapeIndex = 0; // Индекс активной фигуры

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Получение текущего положения мыши
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (size_t i = 0; i < shapes.size(); ++i) {
                    if (shapes[i]->contains(mousePos.x, mousePos.y)) {
                        activeShapeIndex = i;
                        break;
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && activeShapeIndex != -1) {
                // Если выбрана какая-то фигура и происходит нажатие клавиши, обработать соответствующее действие
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
                case sf::Keyboard::Equal: // клавиша "="
                    shapes[activeShapeIndex]->resize(1.1f); // увеличить размер на 10%
                    break;
                case sf::Keyboard::Dash: // клавиша "-"
                    shapes[activeShapeIndex]->resize(0.9f); // уменьшить размер на 10%
                    break;
                case sf::Keyboard::R:
                    shapes[activeShapeIndex]->rotate(0.1f); // Угол вращения, например, 0.1 радиан (приблизительно 5.7 градусов)
                    break;
                case sf::Keyboard::Delete:
                    // Удалить выбранную фигуру, если она есть
                    if (activeShapeIndex >= 0 && activeShapeIndex < shapes.size()) {
                        shapes.erase(shapes.begin() + activeShapeIndex);
                        activeShapeIndex = -1; // После удаления фигура не выбрана
                    }
                    break;
                case sf::Keyboard::C:
                    // Скопируйте выбранную фигуру, если она есть
                    if (activeShapeIndex >= 0 && activeShapeIndex < shapes.size()) {
                        // Создание копии выбранной фигуры
                        std::unique_ptr<Shape> shapeCopy = shapes[activeShapeIndex]->clone();

                        // Добавление копии в вектор фигур
                        shapes.push_back(std::move(shapeCopy));
                    }
                    break;
                }
            }
        }

        window.clear();

        // Отрисовка всех фигур
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (i == activeShapeIndex && shapes[i]->isActive()) {
                // Отрисовываем активную фигуру с другим цветом
                // Например, красным цветом
                sf::Color originalColor = shapes[i]->getColor();
                shapes[i]->setColor(sf::Color::Red);
                shapes[i]->draw(window);
                shapes[i]->setColor(originalColor); // Возвращаем оригинальный цвет
            }
            else {
                shapes[i]->draw(window);
            }
        }

        window.display();
    }

    return 0;
}