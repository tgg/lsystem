#ifndef LSYSTEM_HH
#define LSYSTEM_HH

#include <string>
#include <map>

typedef std::map<char, std::string> rule_map;

class lsystem
{
public:
  lsystem(const char* initial, rule_map& rules)
    : current_(initial), rules_(rules)
  {}

  const std::string& evolve();

private:
  std::map<char, std::string> rules_;
  std::string current_;
};

#endif // LSYSTEM_HH
