/**
  *   @file Level.cpp
  *   @brief Source code for class Level.cpp
  */

#include "Level.hpp"

/*  Class Level */

/* Constructor */
Level::Level()
{
  // Constuct empty LevelEntity
  current_entity = std::make_shared<LevelEntity>();
}

/* Set level_y_limit */
void Level::setYLimit(float y_limit)
{
  level_y_limit = y_limit;
}


/* Check if position free */
bool Level::CheckPosition(float x, float y, float width, float height, LevelEntity *cmp)
{
  sf::Rect<float> cmp_rect = sf::Rect<float>(x, y, width, height);
  // Go through LevelEntities and check all four corners
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    // Remark many check are needed bacause entity sizes can be anything
    // Thus, entites can be partially or complitely inside each other

    if ( it->get() != cmp)
    {
      float entity_width = (*it)->getWidth();
      float entity_height = (*it)->getHeight();
      sf::Vector2f entity_pos = (*it)->getPosition();

      // Check whether enity is inside cmp_rect
      if (cmp_rect.contains(entity_pos.x, entity_pos.y))
      {
        // Entity top left corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width, entity_pos.y))
      {
        // Top right corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x, entity_pos.y + height))
      {
        // Bottom left corner inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width, entity_pos.y + entity_height))
      {
        // Botton right inside
        return false;
      }
      else if (cmp_rect.contains(entity_pos.x + entity_width/2, entity_pos.y + entity_height/2))
      {
        // Center inside (complitely inside cmp_rect)
        return false;
      }
      if ( (*it)->isInside(x, y) )
      {
        // Top left corner inside some other LevelEntity
        return false;
      }
      else if ( (*it)->isInside(x + width, y) )
      {
        // Right top corner inside some other LevelEntity
        return false;

      }
      else if ( (*it)->isInside(x, y + height) )
      {
        // Left bottom corner inside some other LevelEntity
        return false;
      }
      else if ( (*it)->isInside(x + width, y + height) )
      {
        // Right bottom corner inside some other LevelEntity
        return false;

      }

    }
  }

  return true;
}



/* Try to remove an entity */
void Level::EraseEntity(float x, float y)
{
  // Go through all LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ( (*it)->isInside(x, y) )
    {
      if ((*it)->getType() == GROUND_ENTITY)
      {
        RemoveGround(*it);
      }
      // Remove this entity
      level_entities.erase(it);
      break;
    }
  }
}


/* Add LevelEntity */
void Level::addEntity(float x, float y, int entity_type)
{
  // Check that x and y are non negative, y_limit check needs to be done
  // in called methods (e.g. AddInfantry) itself
  if (x < 0)
  {
    x = 0;
  }
  if (y < 0)
  {
    y = 0;
  }

  // Go through all entity_type and try to create correct LevelEntity
  if (entity_type == FRIENDLY_INFANTRY)
  {
    AddEntity(x, y, FRIENDLY_INFANTRY, infantry_width, infantry_height, friendly_infantry_path);
  }
  else if (entity_type == HOSTILE_INFANTRY)
  {
    AddEntity(x, y, HOSTILE_INFANTRY, infantry_width, infantry_height, hostile_infantry_path);
  }
  else if (entity_type == FRIENDLY_PLANE)
  {
    AddEntity(x, y, FRIENDLY_PLANE, plane_width, plane_height, friendly_plane_path);
  }
  else if (entity_type == HOSTILE_PLANE)
  {
    AddEntity(x, y, HOSTILE_PLANE, plane_width, plane_height, hostile_plane_path);
  }
  else if (entity_type == FRIENDLY_AA)
  {
    AddEntity(x, y, FRIENDLY_AA, AA_width, AA_height, friendly_AA_path);
  }
  else if (entity_type == HOSTILE_AA)
  {
    AddEntity(x, y, HOSTILE_AA, AA_width, AA_height, hostile_AA_path);
  }
  else if (entity_type == FRIENDLY_HANGAR)
  {
    AddEntity(x, y, FRIENDLY_HANGAR, hangar_width, hangar_height, friendly_hangar_path);
  }
  else if (entity_type == HOSTILE_HANGAR)
  {
    AddEntity(x, y, HOSTILE_HANGAR, hangar_width, hangar_height, hostile_hangar_path);
  }
  else if (entity_type == FRIENDLY_BASE)
  {
    AddEntity(x, y, FRIENDLY_BASE, base_width, base_height, friendly_base_path);
  }
  else if (entity_type == HOSTILE_BASE)
  {
    AddEntity(x, y, HOSTILE_BASE, base_width, base_height, hostile_base_path);
  }
  else if (entity_type == TREE_ENTITY)
  {
    AddEntity(x, y, TREE_ENTITY, tree_width, tree_height, tree_path);
  }
  else if (entity_type == ROCK_ENTITY)
  {
    AddEntity(x, y, ROCK_ENTITY, rock_width, rock_height, rock_path);
  }
  else if(entity_type == ERASE_ENTITY )
  {
    EraseEntity(x, y);
  }
  else if (entity_type == GROUND_ENTITY)
  {
    AddGround(x, y);
  }
}




/* Try to add an infantry entity */
void Level::AddEntity(float x, float y, int entity_type, float entity_width, float entity_height, std::string entity_img)
{
  current_entity_height = entity_height;

  unsigned correct_y = GetGroundLevel(x, entity_width, entity_height);
  if ((entity_type != FRIENDLY_PLANE) && (entity_type != HOSTILE_PLANE))
  {
    y = correct_y;
  }
  else if (y + entity_height > level_y_limit)
  {
    // This makes sure that planes are not placed 'under' level
    y = level_y_limit - entity_height;
  }
  else if (y < 0)
  {
    y = 0;
  }

  if ( current_entity->getType() == entity_type && current_entity->getPositioned() == false )
  {
    // Try to position current_entity
    if ( CheckPosition(x, y, entity_width, entity_height, current_entity.get()) )
    {
      // position ok
      current_entity->setPosition(x, y);
      current_entity->setPositioned(true);
      current_entity->setFullyConstructed();
      if (current_entity->getType() == FRIENDLY_PLANE)
      {
        // Only one allowed per level
        RemoveSpecificEntities(FRIENDLY_PLANE, current_entity);
      }

    }
  }
  else if (current_entity->getType() == entity_type || current_entity->getType() == NO_ENTITY)
  {
    // Construct new entity_type LevelEntity
    current_entity = std::make_shared<LevelEntity>(x, y, entity_width, entity_height,
                    entity_img, entity_type);
    level_entities.push_back(current_entity);

  }
  else
  {
    // Remove current_entity from level_entities
    removeCurrent();
    // Construct new entity_type LevelEntity

    current_entity = std::make_shared<LevelEntity>(x, y, entity_width, entity_height,
                    entity_img, entity_type);
    level_entities.push_back(current_entity);

  }
}


/* Try to move current_entity */
void Level::moveCurrentEntity(float x, float y)
{
  if (current_entity->getType() == GROUND_ENTITY && current_entity->getStretchable())
  {
    // Stretch Ground entity
    current_entity->stretch(x, y);
  }
  else if (! current_entity->getPositioned())
  {
    // Don't move entity outside level area
    if (x >= 0)
    {
      unsigned correct_y = GetGroundLevel(x, current_entity->getWidth(), current_entity_height);
      if ((current_entity->getType() == (FRIENDLY_PLANE)) || (current_entity->getType() ==  HOSTILE_PLANE))
      {
        if (y < 0)
        {
          y = 0;
        }
        else if (y + current_entity_height > level_y_limit)
        {
          y = level_y_limit - current_entity_height;
        }
        current_entity->setPosition(x, y);
      }
      else
      {
        // Other entities cannot be moved freely
        current_entity->setPosition(x, correct_y);
      }

    }
 }
}

/*  Remove current_entity from level_entities */
void Level::removeCurrent()
{
  if (current_entity->getFullyConstructed() && current_entity->getType() != NO_ENTITY)
  {
    // Don't remove just assign an empty entity
    current_entity = std::make_shared<LevelEntity>();
  }
  else if (current_entity->getType() != NO_ENTITY)
  {
    // Remove the entity
    for (auto it = level_entities.begin(); it != level_entities.end(); it++)
    {
      if ( current_entity == (*it))
      {
        level_entities.erase(it);
        // Construct an empty current_entity
        current_entity = std::make_shared<LevelEntity>();
        break;
      }
    }
  }

}

/*  Draw Level */
void Level::drawLevel(sf::RenderWindow &window)
{
  // Draw all LevelEntities
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    window.draw( (**it) );
  }
}

/* Try to flip LevelEntity */
void Level::flipEntity(float x, float y)
{
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    if ((*it)->isInside(x, y))
    {
      (*it)->flipLevelEntity();
      break;
    }
  }
}

/*  Level print, friend operation */
std::ostream& operator<<(std::ostream &os, const Level &level)
{
  // Output all LevelEntities in order
  for (auto it = level.level_entities.begin(); it != level.level_entities.end(); it++)
  {
    int type = (*it)->getType();
    // First write entity type code
    switch (type)
    {
      case FRIENDLY_PLANE:
        os << "BlueAirplane";
        break;
      case HOSTILE_PLANE:
        os << "RedAirplane";
        break;
      case FRIENDLY_INFANTRY:
        os << "BlueInfantry";
        break;
      case HOSTILE_INFANTRY:
        os << "RedInfantry";
        break;
      case FRIENDLY_AA:
        os << "BlueAntiAircraft";
        break;
      case HOSTILE_AA:
        os << "RedAntiAircraft";
        break;
      case FRIENDLY_HANGAR:
        os << "BlueHangar";
        break;
      case HOSTILE_HANGAR:
        os << "RedHangar";
        break;
      case FRIENDLY_BASE:
        os << "BlueBase";
        break;
      case HOSTILE_BASE:
        os << "RedBase";
        break;
      case TREE_ENTITY:
        os << "Tree";
        break;
      case ROCK_ENTITY:
        os << "Rock";
        break;
      case GROUND_ENTITY:
        os << "Ground";
        break;
    }
    if (type != NO_ENTITY)
    {
      // Add separator
      os << ";";
      // Write entity x and y positions with separator
      sf::Vector2f pos = (*it)->getPosition();
      os << pos.x << ";" << pos.y << ";";
      // Write orientation and add line feed
      os << (*it)->getOrientation() << ";";
      // Write width and height (only needed for Ground)
      os << (*it)->getWidth() << ";" << (*it)->getHeight() << std::endl;
    }
  }

  return os;
}

/*  Save Level to file */
bool Level::saveToFile(std::string level_name, std::string description, bool truncate)
{
  std::ofstream file;
  std::string filename = "../data/level_files/" + level_name + ".txt";
  if (truncate)
  {
    // Delete possible old content
    file.open(filename,  std::ios::out | std::ios::trunc);
  }
  else
  {
    // Check if file exists

    if (std::experimental::filesystem::exists(filename))
    {
      // File already exists
      return false;
    }
    file.open(filename,  std::ios::out);
  }

  if (file.is_open())
  {
    // First write level_name
    file << level_name << std::endl;
    // Second write description with /* start tag and */ end tag
    file << "/* " << description << " */" << std::endl;

    // Now write Level to file
    file << *this;
    file.close();

    return true;
  }

  // File opening failed
  return false;

}

/*  Add Ground entities */
void Level::AddGround(float x, float y)
{
  // Basic checks
  if (x < 0)
  {
    x = 0;
  }

  if (current_entity->getType() == NO_ENTITY)
  {
    unsigned correct_y = GetGroundLevel(x, ground_width, ground_height);

    // Construct new Ground LevelEntity
    current_entity = std::make_shared<LevelEntity> (x, correct_y, ground_width, ground_height,
                      ground_path, GROUND_ENTITY);
    current_entity->setNonFlippable();
    level_entities.push_back(current_entity);
    current_entity_height = ground_height;
  }
  else if (!current_entity->getPositioned())
  {
    unsigned correct_y = GetGroundLevel(x, ground_width, ground_height);
    current_entity->setPosition(x, correct_y);
    current_entity->setPositioned(true);
  }
  else if (current_entity->getStretchable())
  {
   // Deactivate stretching
   current_entity->setStretchable(false);
  }
  else
  {
    // Try to activate stretching
    current_entity->activateStretching(x, y);
  }
}

/*  Set ground fully_constructed and update ground_level */
bool Level::finishAddingGround()
{
  if (current_entity->getType() == GROUND_ENTITY)
  {
    current_entity->setFullyConstructed();
    // Update ground_level
    unsigned x = (unsigned) current_entity->getX();
    unsigned max_x = x + (unsigned) current_entity->getWidth();
    unsigned y = (unsigned) current_entity->getY();
    for (; x < max_x; x++)
    {
      auto it = ground_level.find(x);
      if (it == ground_level.end())
      {
        // No ground below
        ground_level[x] = y;
      }
      else
      {
        if (y < it->second)
        {
          ground_level[x] = y;
        }
      }

    }
    // Add to grounds
    grounds.push_back(current_entity);
    RemoveEntitiesBelow(current_entity->getX(), current_entity->getY(),
                        current_entity->getWidth(), current_entity->getHeight());
    removeCurrent(); // assigns NO_ENTITY to current_entity
    return true;
  }
  return false;
}

/*  Get ground level below entity */
unsigned Level::GetGroundLevel(float entity_x, float entity_width, float entity_height)
{
  unsigned min_y = level_y_limit;
  for (unsigned x = (unsigned) entity_x; x <= (unsigned) entity_x + entity_width; x++)
  {
    // Get ground level
    auto it = ground_level.find(x);
    if (it != ground_level.end())
    {
      if (it->second != 0)
      {
        if (it->second -1 < min_y)
        {
          // -1 places objects one pixel apart so that they arent on top of each other
          min_y = it->second -1;
        }
      }

    }
  }
  if ((unsigned)entity_height < min_y)
  {
    return min_y - entity_height;
  }
  else
  {
    // Entity cannot be placed correctly on the screen, just draw entity
    // on level low corner (probably best of the bad options)
    return level_y_limit - entity_height;
  }

}


/*  Remove LevelEntities below Ground */
void Level::RemoveEntitiesBelow(float x, float y, float width, float height)
{
  float x_max = x + width;
  float y_max = y + height;
  bool erased = false;
  for (auto it = level_entities.begin(); it != level_entities.end();)
  {
    erased = false;
    if ((*it)->getType() != GROUND_ENTITY)
    {
      float cmp_x = (*it)->getX();
      float cmp_y = (*it)->getY();
      float cmp_x_max = cmp_x + (*it)->getWidth();
      float cmp_y_max = cmp_y + (*it)->getHeight();

      if ( (x <= cmp_x && cmp_x <= x_max) || (cmp_x < x && cmp_x_max > x) ||
            (cmp_x_max > x_max && cmp_x < x_max) )
      {
        // 1. complitely inside; 2. right corner inside; 3. left corner inside
        if ( (y <= cmp_y && cmp_y <= y_max) || (cmp_y < y && cmp_y_max > y) ||
            (cmp_y_max > y_max && cmp_y < y_max) )
        {
          // 1. complitely inside; 2. top corner inside; 3. lower corner inside
          it = level_entities.erase(it);
          erased = true;
        }
      }
    }
    if (! erased)
    {
      it ++;
    }
  }
}

/*  Update ground_level */
void Level::RemoveGround(std::shared_ptr<LevelEntity> ground)
{
  unsigned x = (unsigned) ground->getX();
  unsigned y = (unsigned) ground->getY();
  unsigned x_max = x + (unsigned) ground->getWidth();
  for (; x < x_max; x++)
  {
    auto it = ground_level.find(x);

    if (it != ground_level.end())
    {
      if (y == it->second)
      {
        // This is the current ground level defining entity
        ground_level[x] = GetNewGroundLevel(x, ground);
      }
    }
  }
  // Remove from grounds
  for (auto it = grounds.begin(); it != grounds.end(); it++)
  {
    if ((*it) == ground)
    {
      grounds.erase(it);
      break;
    }
  }

}

/* Get new ground level */
unsigned Level::GetNewGroundLevel(unsigned x, std::shared_ptr<LevelEntity> ground)
{
  unsigned y_max = level_y_limit;
  for (auto it = grounds.begin(); it != grounds.end(); it++)
  {
    if ((*it) != ground)
    {
      unsigned cmp_x = (unsigned) (*it)->getX();
      unsigned cmp_x_max =  cmp_x + (unsigned) (*it)->getWidth();
      if ( cmp_x <= x && cmp_x_max > x)
      {
        if ((*it)->getY() < y_max)
        {
          // New y_max
          y_max = (*it)->getY();
        }
      }
    }

  }
  return y_max;
}


/*  Remove specific LevelEntities */
void Level::RemoveSpecificEntities(int type, std::shared_ptr<LevelEntity> not_removed)
{
  for (auto it = level_entities.begin(); it != level_entities.end();)
  {
    if ((*it)->getType() == type && (*it) != not_removed)
    {
      it = level_entities.erase(it);
    }
    else
    {
      it++;
    }
  }
}

/*  Get Level width */
float Level::getLevelWidth()
{
  float x_max = 0;
  for (auto it = level_entities.begin(); it != level_entities.end(); it++)
  {
    float x_tmp = (*it)->getX() + (*it)->getWidth();
    if (x_tmp > x_max)
    {
      x_max = x_tmp;
    }
  }
  return x_max;
}
