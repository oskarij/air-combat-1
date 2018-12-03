#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
class Bullet : public Entity {
 public:
  Bullet(b2World &w, b2Body &b, const sf::Texture &t, const sf::Vector2f &position, float speed, int bullets, int bombs, int firerate);

};
