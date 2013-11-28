//
// main.cpp for test in /home/mestag_a/Documents/Projets/Tek3/Babel/Common
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Nov 25 22:24:20 2013 alexis mestag
// Last update Tue Nov 26 01:01:45 2013 alexis mestag
//

#include		<iostream>
#include		"Mutex/Mutex.hpp"
#include		"Thread/Thread.hpp"

void			*bite(void *data)
{
  int			x = 30000;

  std::cout << "I'm the thread and I'm waiting for " << x << std::endl;
  Sleep(x);
  return (NULL);
}

int			main()
{
	char	c;
  Thread		t;

  std::cout << "Creating thread" << std::endl;
  t.create(&bite, NULL);
  std::cout << "Launching thread" << std::endl;
  t.start();
  std::cout << "Waiting for 5 seconds" << std::endl;
  Sleep(5000);
  std::cout << "Joining thread" << std::endl;
  t.join();
  std::cout << "Done" << std::endl;
  std::cin >> c;
  return (0);
}
