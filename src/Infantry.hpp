#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Infantry : public Entity {
  public:
  Infantry(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate);
  bool shoot();
};
