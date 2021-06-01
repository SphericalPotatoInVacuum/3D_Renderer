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
  yar::World m_world;
  yar::Camera m_camera;
  sf::RenderWindow m_window;
  sf::Texture m_texture;
  std::vector<sf::Uint8> m_pixels;
  sf::Sprite m_sprite;
  yar::Picture m_picture;
  std::vector<yar::Object> objects;
  yar::Renderer m_renderer;
  yar::Screen m_screen;
  size_t m_width;
  size_t m_height;
  size_t m_triangle_cnt = 0;
  sf::Font m_font;
  sf::Text m_text;
  std::stringstream ss;

  float m_init_time;

  std::vector<yar::Triangle> get_pyramid_carcas();
  std::vector<yar::Triangle> get_plane_carcas();
};
