#include <iostream>

#include "lsystem.hh"

int main(void)
{
  rule_map koch_rules = { { 'F', "F+F-F-F+F" } };
  lsystem koch("F", koch_rules);
  
  for(int i = 0; i < 3; i++) {
    auto current = koch.evolve();
    std::cout << "Step #" << (i + 1) << ": "
	      << current 
	      << std::endl;
  }

  return EXIT_SUCCESS;
}
