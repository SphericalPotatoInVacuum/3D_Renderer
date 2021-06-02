#include <SFML/Graphics.hpp>
#include <YAR/Camera.hpp>
#include <YAR/Renderer.hpp>
#include <YAR/Screen.hpp>
#include <YAR/World.hpp>
#include <sstream>

class Application {
 public:
  Application(size_t width, size_t height);

  void run();

 private:
  size_t m_width;
  size_t m_height;
  sf::RenderWindow m_window;
  yar::Screen m_screen;
  std::vector<sf::Uint8> m_pixels;
  yar::Camera m_camera;

  yar::World m_world;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
  std::vector<yar::Object> objects;
  yar::Renderer m_renderer;
  size_t m_triangle_cnt = 0;
  sf::Font m_font;
  sf::Text m_text;
  std::stringstream ss;

  float m_init_time;

  std::vector<yar::Triangle> get_pyramid_carcas();
  std::vector<yar::Triangle> get_plane_carcas();

  void poll_events();
  void handle_key_press();
  void update_screen(const yar::Picture &picture);
};
