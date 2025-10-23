#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  std::fstream fs;
  int val;

  fs.open("/sys/class/backlight/intel_backlight/brightness", std::fstream::in);
  fs >> val;
  fs.close();

  fs.open("/sys/class/backlight/intel_backlight/brightness", std::fstream::out);
  fs << atoi(argv[1]);
  fs.close();

  return 0;
}
