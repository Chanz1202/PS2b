/*
NAME: Hanuman Sai Chanukya Srinivas Chilamkuri
Course: COMP 2040
Instructor: Dr Rykalova
PS2b assignment
Due date: 10/11/2021
*/

#include "universe.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)   
  {
    // from here 3 arguments can be taken
    std::cout << "Usage: ./NBody [simulation time] [time step] < planets.txt\n";
    return -1;
  }

  // get the simulation time from command line arguments
  std::string sim_time(argv[1]);
  std::string step_time(argv[2]);
  std::string::size_type sz;     

  std::cout << "Simulation time: " << sim_time << "\n";
  std::cout << "Time Step: " << step_time << "\n\n";

  double simulation_time = 0;
  double simu_time = std::stod(sim_time, &sz);
  double time_step = std::stod(step_time, &sz);

  // to get first two numbers in text file
  std::string num_planets, radius;
  
  std::cin >> num_planets;
  std::cin >> radius;

  // to know number of planets and radius of them
  int number_planets = std::stoi(num_planets, &sz);
  double universe_radius = std::stod(radius, &sz);

  std::cout << "Num of planets: " << number_planets << std::endl;
  std::cout << "Radius: " << universe_radius << std::endl << std::endl;

  // create a vector of universe objects
  std::vector<universe> body_vector;

  // loop for planets in input file
  for(int i = 0; i < number_planets; i++)
  {
    // create a new object
    universe* tmp = new universe();

    // read input into the object
    std::cin >> *tmp;

    // set the radius and the planet positions
    tmp->set_radius(universe_radius);
    tmp->set_position();

    // save the object to the vector
    body_vector.push_back(*tmp);

    // test the object 
    std::cout << *tmp;
  }

  // creating SFML Window
  sf::RenderWindow window(sf::VideoMode(window_side, window_height), "The Solar System");

  // changing the framerate 
  window.setFramerateLimit(60);

  // background image
  sf::Image background_image;
  if (!background_image.loadFromFile("space.png"))
  {
   // exit if file doesn't exists
    return -1;    
  }

  // declare and load a font
  sf::Font time_font;
  time_font.loadFromFile("castellar.ttf");

  // text for displaying the simulation time.
  sf::Text time_text;

  // select the font
  time_text.setFont(time_font); 

  // set the character size in pixels
  time_text.setCharacterSize(14);     

  // to load the music file
  sf::Music music;
  if(!music.openFromFile("bgm.ogg"))
  {
    return -1;   
  }

  music.play();

  // load the image into a texture
  sf::Texture background_texture;
  background_texture.loadFromImage(background_image);

  // load the texture into a sprite
  sf::Sprite background_sprite;
  background_sprite.setTexture(background_texture);

  std::vector<universe>::iterator it;
  std::vector<universe>::iterator x, y;

  while (window.isOpen())
  {
    sf::Event event;

    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();

    window.draw(background_sprite);

    // update the time string
    time_text.setString("Elapsed time: " + std::to_string(simulation_time));

    window.draw(time_text);

    // calculate the net force on each universe object
    x = body_vector.begin();
    double force_x, force_y;

    // first loop goes through the whole universe vector 
    for(int a = 0; a < number_planets; a++)
    {
      y = body_vector.begin();
      force_x = 0;
      force_y = 0;
      
      for(int b = 0; b < number_planets; b++)
      {
        if(a != b)    
        {             
          force_x += find_forcex(*x, *y);
          force_y += find_forcey(*x, *y);
        }
        y++;
      }
      
      // to update the forces inside the current object
      x->set_forces(force_x, force_y);
      x++;
    }

    for(it = body_vector.begin(); it != body_vector.end(); it++)
    {
      window.draw(*it);
      std::cout << *it << std::endl;

      it->step(time_step);
      
      //set the image position
      it->set_position();  
    }

    window.display();

    // increasing simulation time variable 
    simulation_time += time_step;

    if(simulation_time == simu_time)
    {
      break;
    }
  }

 // to print velocities while running
  std::cout << "\n\n\n";
  for(it = body_vector.begin(); it != body_vector.end(); it++)
  {
    std::cout << *it << std::endl;
  }

  return 0;
}
