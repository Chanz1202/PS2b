#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// constants for window size.
const int window_height = 500;
const int window_side = 500;

const double gravity = 6.67e-11;

class universe: public sf::Drawable
{
public:

  // constructors
  universe();
  universe(double pos_x, double pos_y, double vel_x, double vel_y,
       double obj_mass, double radius, std::string file_name);

  // set radius and image position
  void set_radius(float radius);
  
  // to set the planet position
  void set_position();              

  friend double find_forcex(universe &Body1, universe &Body2);
  friend double find_forcey(universe &Body1, universe &Body2);
  void set_forces(double forcex, double forcey);

  void step(double time_t);

  // to take input from a file
  friend std::istream& operator>> (std::istream &input, universe &CelestialBody);

  // to debug
  friend std::ostream& operator<< (std::ostream &output, universe &CelestialBody);

private:

  // draw method
  void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;

  // member variables
  double _acc_x, _acc_y;
  double _for_x, _for_y;
  double _pos_x, _pos_y;
  double _vel_x, _vel_y;
  double _mass, _radius;
  std::string _filename;

  // image related objects
  sf::Image _image;
  sf::Sprite _sprite;
  sf::Texture _texture;
};
