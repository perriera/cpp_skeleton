#include <fstream>
#include <iostream> // std::cout
#include <sstream>  // std::stringstream
#include <string>   // std::string

#include "../include/CppWallet/HelloWorld.hpp"
#include "catch.hpp"

using namespace std;

SCENARIO("Verify HelloWorld", "[HelloWorld]")
{

  HelloWorld helloWorld;
  REQUIRE(helloWorld.say_hello() == "Hello, world");
}
