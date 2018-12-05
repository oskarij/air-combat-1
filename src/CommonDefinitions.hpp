/**
 *   @file CommonDefinitions.hpp
 *   @brief Header for CommonDefinitions class
 */
#pragma once

/* Includes */

#include <string>
#include <vector>
#include <map>
namespace Game
{
  extern const int WIDTH;
  extern const int HEIGHT;
  extern const float GRAVITY;
  extern const float TOPIXELS;
  extern const float TOMETERS;

  enum TYPE_ID
    {
      airplane,
      antiaircraft,
      base,
      hangar,
      infantry,
      bullet,
      ground,
      rock,
      tree,
      type_id_end
    };
  
  enum TEAM_ID
    {
      all_friend,
      all_enemy,
      blue,
      red,
      team_id_end
    };

    enum ACTIONS
      {
	move_left,
	move_right,
	move_up,
	move_down,
	shoot,
	bomb,
	actions_end
      };
}

namespace Paths
{
  enum PATHS
    {
      fonts,
      img,
      level_files,
      logs,
      paths_end
    };
  extern std::vector<std::string> Paths;
  
}

namespace Textures
{
  enum ID
    {
      BlueAirplane_alpha,
      BlueAirplane,
      BlueAntiAircraft_alpha,
      BlueAntiAircraft,
      BlueBase_alpha,
      BlueBase,
      BlueHangar_alpha,
      BlueHangar,
      BlueInfantry_alpha,
      BlueInfantry,
      Bullet_alpha,
      erase,
      Ground_alpha,
      Ground,
      infantry,
      left_arrow,
      plane,
      RedAirplane_alpha,
      RedAirplane,
      RedAntiAircraft_alpha,
      RedAntiAircraft,
      RedBase_alpha,
      RedBase,
      RedHangar_alpha,
      RedHangar,
      RedInfantry_alpha,
      RedInfantry,
      right_arrow,
      Rock_alpha,
      Rock,
      std_button,
      Tree_alpha,
      Tree,
      id_end      
    };
  extern std::vector<std::string> TextureFiles;
extern std::map<std::string, Textures::ID> alphaTextures;
}

