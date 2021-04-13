#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <YAR/Picture.hpp>
#include <YAR/Renderer.hpp>
#include <string>

const size_t WIDTH = 640;
const size_t HEIGHT = 480;

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
  sf::Texture texture;
  texture.create(WIDTH, HEIGHT);
  sf::Sprite sprite;
  yar::Picture picture;
  sf::Uint8 pixels[WIDTH * HEIGHT * 4];
  yar::Renderer renderer(WIDTH, HEIGHT);
  sf::Clock clock;
  float last_time = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
      }
    }

    float current_time = clock.restart().asSeconds();
    float fps = 1 / (current_time - last_time);
    printf("FPS: %10.10g\r", fps);

    const yar::Color *colors = renderer.render().get_pixels();
    for (int i = 0; i < WIDTH * HEIGHT * 4; i += 4) {
      pixels[i] = colors[i / 4].r;
      pixels[i + 1] = colors[i / 4].g;
      pixels[i + 2] = colors[i / 4].b;
      pixels[i + 3] = 255;
    }

    texture.update(pixels);
    sprite.setTexture(texture);

    window.clear();
    window.draw(sprite);
    window.display();
  }

  return 0;
}
