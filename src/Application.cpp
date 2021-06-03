#include <Application.hpp>
#include <YAR/Color.hpp>
#include <YAR/Renderer.hpp>
#include <fstream>

Application::Application(size_t width, size_t height)
    : m_width(width),
      m_height(height),
      m_window(sf::VideoMode(width, height), "3D Renderer"),
      m_screen(width, height),
      m_pixels(4 * width * height),
      m_camera({0, 0, 5.f}, {0, 0, 0}, glm::radians(70.0f), 0.1f, 100.0f,
               (width + 0.f) / height) {
  sf::Clock clock;
  clock.restart();

  m_window.setKeyRepeatEnabled(false);

  m_texture.create(width, height);

  m_font;
  if (!m_font.loadFromFile("resources/arial.ttf")) {
    _Exit(1);
  }
  m_text.setFont(m_font);

  std::vector<yar::Triangle> triangles;
  parse_off_object("resources/teapot.off", &triangles);
  m_triangle_cnt += triangles.size();

  objects.push_back(yar::Object({-0.5f, -0.6f, 0}, {-M_PI_2, 0, 0}, triangles));

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

    // m_camera.set_position(glm::vec3{std::sin(M_PI * current_time) * 3, 0,
    //                                 std::cos(M_PI * current_time) * 3});
    // m_camera.set_rotation(glm::vec3(0, M_PI * current_time, 0));

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
    m_camera.rotate({M_PI / 16, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    m_camera.rotate({-M_PI / 16, 0, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    m_camera.rotate({0, M_PI / 16, 0});
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    m_camera.rotate({0, -M_PI / 16, 0});
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

void Application::parse_off_object(const std::string &filename,
                                   std::vector<yar::Triangle> *triangles) {
  std::ifstream fin(filename);
  std::string off;
  fin >> off;
  int vert_cnt, face_cnt, edge_cnt;
  fin >> vert_cnt >> face_cnt >> edge_cnt;
  std::vector<glm::vec3> vertices(vert_cnt);
  for (auto &v : vertices) {
    fin >> v.x >> v.y >> v.z;
  }
  for (int i = 0; i < face_cnt; ++i) {
    int n;
    fin >> n;
    std::vector<int> idx(n);
    for (int &x : idx) {
      fin >> x;
    }
    for (int j = 0; j < n - 2; ++j) {
      triangles->push_back(
          {{vertices[idx[j + 2]], vertices[idx[j + 1]], vertices[idx[0]]},
           yar::Color::White * ((rand() + 0.f) / RAND_MAX / 4 + 0.75f)});
    }
  }
}
