#include <Application.hpp>
#include <YAR/Renderer.hpp>

Application::Application(size_t width, size_t height)
    : m_width(width),
      m_height(height),
      m_window(sf::VideoMode(width, height), "3D Renderer"),
      m_screen(width, height),
      m_pixels(4 * width * height) {
  sf::Clock clock;
  clock.restart();

  m_texture.create(width, height);
  m_font;
  if (!m_font.loadFromFile("arial.ttf")) {
    _Exit(1);
  }
  m_text.setFont(m_font);

  std::vector<yar::Triangle> triangles = get_pyramid_carcas();
  for (int x = -3; x <= 3; ++x) {
    for (int z = -8; z <= 3; ++z) {
      objects.push_back(
          yar::Object({2 * x, 0, 2 * z}, {-3.14, 0, 0}, triangles));
      m_triangle_cnt += triangles.size();
    }
  }
  float aspect_ratio =
      static_cast<float>(width + 0.0) / static_cast<float>(height);
  m_camera = yar::Camera({0, 0.6f, 10.05f}, {0, 0, 0}, glm::radians(70.0f),
                         0.1f, 100.0f, aspect_ratio);
  for (auto &object : objects) {
    m_world.add_object(&object);
  }

  m_init_time = clock.getElapsedTime().asSeconds();
}

void Application::run() {
  sf::Clock clock;
  clock.restart();
  float last_time = 0;

  while (m_window.isOpen()) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          m_window.close();
          break;
        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_camera.move({-0.05, 0, 0});
            printf("\rfuck");
            fflush(stdout);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            m_camera.move({0.05, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            m_camera.move({0, 0.05, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            m_camera.move({0, -0.05, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            m_camera.move({0, 0, -0.05});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            m_camera.move({0, 0, 0.05});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            m_camera.rotate({M_PI / 64, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            m_camera.rotate({-M_PI / 64, 0, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            m_camera.rotate({0, M_PI / 64, 0});
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            m_camera.rotate({0, -M_PI / 64, 0});
          }
          break;
      }
    }

    float current_time = clock.getElapsedTime().asSeconds();

    ss.str("");
    ss.precision(6);
    ss << "Init time: " << std::fixed << m_init_time << "s\n"
       << "time per frame: " << std::fixed << (current_time - last_time)
       << "s\n"
       << "Triangle count: " << m_triangle_cnt;
    m_text.setString(ss.str());
    last_time = current_time;

    m_renderer.render(m_world, m_camera, m_screen);
    const yar::Color *colors = m_screen.get_picture().get_pixels();
    for (int i = 0; i < m_width * m_height; ++i) {
      m_pixels[4 * i] = colors[i].r;
      m_pixels[4 * i + 1] = colors[i].g;
      m_pixels[4 * i + 2] = colors[i].b;
      m_pixels[4 * i + 3] = 255;
    }
    m_texture.update(m_pixels.data());
    m_sprite.setTexture(m_texture);

    m_window.draw(m_sprite);
    m_window.draw(m_text);
    m_window.display();
  }
}

std::vector<yar::Triangle> Application::get_pyramid_carcas() {
  return std::vector<yar::Triangle>{{{{
                                          1,
                                          1,
                                          -1,
                                      },
                                      {
                                          0,
                                          -1,
                                          0,
                                      },
                                      {
                                          -1,
                                          1,
                                          -1,
                                      }},
                                     yar::Color{255, 0, 0}},
                                    {{{
                                          1,
                                          1,
                                          1,
                                      },
                                      {
                                          0,
                                          -1,
                                          0,
                                      },
                                      {
                                          1,
                                          1,
                                          -1,
                                      }},
                                     yar::Color{0, 255, 0}},
                                    {{{
                                          -1,
                                          1,
                                          1,
                                      },
                                      {
                                          0,
                                          -1,
                                          0,
                                      },
                                      {
                                          1,
                                          1,
                                          1,
                                      }},
                                     yar::Color{0, 0, 255}},
                                    {{{
                                          -1,
                                          1,
                                          -1,
                                      },
                                      {
                                          0,
                                          -1,
                                          0,
                                      },
                                      {
                                          -1,
                                          1,
                                          1,
                                      }},
                                     yar::Color{255, 255, 0}}};
}
