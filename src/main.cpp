#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <YAR/Picture.hpp>
#include <YAR/Renderer.hpp>
#include <cmath>
#include <string>

const size_t WIDTH = 1000;
const size_t HEIGHT = 1000;

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
  sf::Texture texture;
  texture.create(WIDTH, HEIGHT);
  sf::Sprite sprite;
  yar::Picture picture;
  sf::Uint8 pixels[WIDTH * HEIGHT * 4];
  yar::World world;
  std::vector<yar::Triangle> triangles = {
      {{{1, 1, -1, 1}, {0, -1, 0, 1}, {-1, 1, -1, 1}}, yar::Color{255, 0, 0}},
      {{{1, 1, 1, 1}, {0, -1, 0, 1}, {1, 1, -1, 1}}, yar::Color{0, 255, 0}},
      {{{-1, 1, 1, 1}, {0, -1, 0, 1}, {1, 1, 1, 1}}, yar::Color{0, 0, 255}},
      {{{-1, 1, -1, 1}, {0, -1, 0, 1}, {-1, 1, 1, 1}},
       yar::Color{255, 255, 0}}};
  yar::Object object({-2, 0, 2}, {-3.14, 0, 0}, triangles);
  yar::Object object3({2, 0, -1}, {-3.14, 0, 0}, triangles);
  yar::Object object2({0, -1, 0}, {0, 0, 0},
                      std::vector<yar::Triangle>{
                          {{{-10, 0, 5, 1}, {10, 0, 5, 1}, {-10, 0, -10, 1}},
                           yar::Color{255, 255, 255}},
                          {{{10, 0, 5, 1}, {10, 0, -10, 1}, {-10, 0, -10, 1}},
                           yar::Color{255, 255, 255}}});
  float aspect_ratio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
  yar::Camera camera({0, -0.6f, 5.05f}, {0, 0, 0}, glm::radians(70.0f), 0.1f,
                     15.0f, aspect_ratio);
  world.add_object(&object);
  world.add_object(&object2);
  world.add_object(&object3);
  yar::Renderer renderer(world, camera, WIDTH, HEIGHT);
  sf::Clock clock;
  clock.restart();
  float last_time = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.move({-0.05, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.move({0.05, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.move({0, 0.05, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.move({0, -0.05, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            camera.move({0, 0, -0.05});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            camera.move({0, 0, 0.05});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.rotate({M_PI / 64, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.rotate({-M_PI / 64, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.rotate({0, 0, M_PI / 64});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.rotate({0, 0, -M_PI / 64});
          }
          break;
      }
    }

    float current_time = clock.getElapsedTime().asSeconds();
    float fps = 1 / (current_time - last_time);
    // printf("\r%6.2f", fps);
    last_time = current_time;

    // object.set_rotation({0, 1 * current_time, 0});

    // printf("FPS: %10.10g\r", fps);

    const yar::Color *colors = renderer.render().get_pixels();
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
      pixels[4 * i] = colors[i].r;
      pixels[4 * i + 1] = colors[i].g;
      pixels[4 * i + 2] = colors[i].b;
      pixels[4 * i + 3] = 255;
    }
    texture.update(pixels);
    sprite.setTexture(texture);

    window.draw(sprite);
    window.display();
  }

  return 0;
}
