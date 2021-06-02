#include <Application.hpp>
#include <YAR/Color.hpp>
#include <YAR/Renderer.hpp>

Application::Application(size_t width, size_t height)
    : m_width(width),
      m_height(height),
      m_window(sf::VideoMode(width, height), "3D Renderer"),
      m_screen(width, height),
      m_pixels(4 * width * height),
      m_camera({0, 0.6f, 10.2f}, {0, 0, 0}, glm::radians(70.0f), 0.1f, 100.0f,
               (width + 0.f) / height) {
  sf::Clock clock;
  clock.restart();

  m_window.setKeyRepeatEnabled(false);

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

  triangles = get_plane_carcas();
  for (int x = -3; x <= 3; ++x) {
    for (int y = 0; y <= 6; ++y) {
      objects.push_back(
          yar::Object({2 * x, 2 * y, -17}, {-M_PI_2, 0, 0}, triangles));
      m_triangle_cnt += triangles.size();
    }
  }

  for (auto &object : objects) {
    m_world.add_object(object);
  }

  m_init_time = clock.getElapsedTime().asSeconds();
}

void Application::run() {
  sf::Clock clock;
  clock.restart();
  float last_time = 0;

  while (m_window.isOpen()) {
    poll_events();

    float current_time = clock.getElapsedTime().asSeconds();

    ss.str("");
    ss.precision(6);
    ss << "Init time: " << std::fixed << m_init_time << "s\n"
       << "Time per frame: " << std::fixed << (current_time - last_time)
       << "s\n"
       << "FPS: " << std::fixed << 1 / (current_time - last_time) << "\n"
       << "Triangle count: " << m_triangle_cnt;
    m_text.setString(ss.str());
    last_time = current_time;

    m_renderer.render(m_world, m_camera, &m_screen);
    update_screen(m_screen.get_picture());
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
                                     yar::Color::Red},
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
                                     yar::Color::Green},
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
                                     yar::Color::Blue},
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
                                     yar::Color::Yellow}};
}

std::vector<yar::Triangle> Application::get_plane_carcas() {
  return std::vector<yar::Triangle>{
      {{{-1, 0, -1}, {1, 0, 1}, {-1, 0, 1}}, yar::Color::White},
      {{{-1, 0, -1}, {1, 0, -1}, {1, 0, 1}}, yar::Color::White}};
}

void Application::poll_events() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        m_window.close();
        break;
      case sf::Event::KeyPressed:
        handle_key_press();
        break;
    }
  }
}

void Application::handle_key_press() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    m_camera.move({-0.2, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    m_camera.move({0.2, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    m_camera.move({0, 0.2, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    m_camera.move({0, -0.2, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    m_camera.move({0, 0, -0.2});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    m_camera.move({0, 0, 0.2});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    m_camera.rotate({M_PI / 32, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    m_camera.rotate({-M_PI / 32, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    m_camera.rotate({0, M_PI / 32, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    m_camera.rotate({0, -M_PI / 32, 0});
  }
}

void Application::update_screen(const yar::Picture &picture) {
  for (int x = 0; x < m_width; ++x) {
    for (int y = 0; y < m_height; ++y) {
      m_pixels[4 * (y * m_width + x)] = picture(x, y).r;
      m_pixels[4 * (y * m_width + x) + 1] = picture(x, y).g;
      m_pixels[4 * (y * m_width + x) + 2] = picture(x, y).b;
      m_pixels[4 * (y * m_width + x) + 3] = 255;
    }
  }
  m_texture.update(m_pixels.data());
}
