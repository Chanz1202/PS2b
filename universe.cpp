#include "universe.hpp"

// default constructor
universe::universe()
{
  // it does nothing
  return;
}


// constructor with parameters
universe::universe(double pos_x, double pos_y, double vel_x, double vel_y, double obj_mass, double radius, std::string file_name)
{
  // set member variables
  _pos_x = pos_x;
  _pos_y = pos_y;
  _vel_x = vel_x;
  _vel_y = vel_y;
  _mass = obj_mass;
  _filename = file_name;

  // load the image into an image object
  if (!_image.loadFromFile(file_name))
  {
    return;    
  }

  // load the image into a texture
  _texture.loadFromImage(_image);

  // load the texture into a sprite
  _sprite.setTexture(_texture);

  _sprite.setPosition(sf::Vector2f(_pos_x, _pos_y));
}


// to set the universe radius
void universe::set_radius(float radius)
{
  _radius = radius;
  return;
}

// to set the forces for a given object
void universe::set_forces(double forcex, double forcey)
{
  _for_x = forcex;
  _for_y = forcey;
}


// finds the force between two universe objects
double find_forcex(universe &Body1, universe &Body2)
{
  
  double dx = Body2._pos_x - Body1._pos_x;
  double dy = Body2._pos_y - Body1._pos_y;
  double R2 = pow(dx, 2) + pow(dy, 2);
  double R = sqrt(R2);
  double force = (gravity * Body1._mass * Body2._mass) / R2;
  double for_x = force * (dx / R);

  std::cout << "Body1 Filename: " << Body1._filename << "\n";
  std::cout << "dx: " << dx << "\n";
  std::cout << "dy: " << dy << "\n";
  std::cout << "Force: " << force << "\n";
  std::cout << "Force(x) " << for_x << "\n";
  std::cout << "Gravity: " << gravity << "\n";
  std::cout << "Body1 Mass: " << Body1._mass << "\n";
  std::cout << "Body2 Mass: " << Body2._mass << "\n\n";

  return for_x;
}


// finds the force between two universe objects
double find_forcey(universe &Body1, universe &Body2)
{
  
  double dx = Body2._pos_x - Body1._pos_x;
  double dy = Body2._pos_y - Body1._pos_y;
  double R2 = pow(dx, 2) + pow(dy, 2);
  double R = sqrt(R2);
  double force = (gravity * Body1._mass * Body2._mass) / R2;
  double for_y = force * (dy / R);

  std::cout << "Body1 Filename: " << Body1._filename << "\n";
  std::cout << "dx: " << dx << "\n";
  std::cout << "dy: " << dy << "\n";
  std::cout << "Force: " << force << "\n";
  std::cout << "Force(y " << for_y << "\n";
  std::cout << "Gravity: " << gravity << "\n";
  std::cout << "Body1 Mass: " << Body1._mass << "\n";
  std::cout << "Body2 Mass: " << Body2._mass << "\n\n";

  return for_y;
}


void universe::step(double time_t)
{
 
  _acc_x = _for_x / _mass;
  _acc_y = _for_y / _mass;
  
  _vel_x = _vel_x + (_acc_x * time_t);
  _vel_y = _vel_y + (_acc_y * time_t);

  _pos_x = _pos_x + (_vel_x * time_t);
  _pos_y = _pos_y + (_vel_y * time_t);

}


// to set the planets position
void universe::set_position()
{

  double pos_x = ( (_pos_x / _radius) * (window_side / 2) ) + (window_side / 2);
  double pos_y = ( (_pos_y / _radius) * (window_height / 2) ) + (window_height / 2);

  // flip x and y positions for going counter-clockwise
  _sprite.setPosition(sf::Vector2f(pos_y, pos_x));
}


// drawable method
void universe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite);
}


// to take input from the file
std::istream& operator>> (std::istream &input, universe &CelestialBody)
{
  
  input >> CelestialBody._pos_x >> CelestialBody._pos_y;
  input >> CelestialBody._vel_x >> CelestialBody._vel_y;
  input >> CelestialBody._mass  >> CelestialBody._filename;

  // load the image into an image object
  if (!CelestialBody._image.loadFromFile(CelestialBody._filename))
  {
    return input;   
  }

  // load the image into a texture
  CelestialBody._texture.loadFromImage(CelestialBody._image);

  // load the texture into a sprite
  CelestialBody._sprite.setTexture(CelestialBody._texture);

  // to set the initial position
  CelestialBody._sprite.setPosition(sf::Vector2f(CelestialBody._pos_x, CelestialBody._pos_y));

  // to set the force and acceleration to 0
  CelestialBody._for_x = 0;
  CelestialBody._for_y = 0;
  CelestialBody._acc_x = 0;
  CelestialBody._acc_y = 0;

  return input;
}

std::ostream& operator<< (std::ostream &output, universe &CelestialBody)
{
  output << "Filename: " << CelestialBody._filename << std::endl;
  output << "Acceleration (x): " << CelestialBody._acc_x << std::endl;
  output << "Acceleration (y): " << CelestialBody._acc_y << std::endl;
  output << "Force (x): " << CelestialBody._for_x << std::endl;
  output << "Force (y): " << CelestialBody._for_y << std::endl;
  output << "Pos (x): " << CelestialBody._pos_x << std::endl;
  output << "Pos (y): " << CelestialBody._pos_y << std::endl;
  output << "Vel (x): " << CelestialBody._vel_x << std::endl;
  output << "Vel (y): " << CelestialBody._vel_y << std::endl;
  output << "Mass: " << CelestialBody._mass << std::endl;
  output << "Radius: " << CelestialBody._radius << std::endl << std::endl;

  return output;
}
