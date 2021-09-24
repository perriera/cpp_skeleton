#include <iostream>
#include <list>
#include <iterator>
#include "catch.hpp"
#include "../include/CppWallet/TransactionInterface.hpp"

// using namespace std;

// using TransactionId = long;
// using TransactionIdList = std::list<TransactionId>;

//function for printing the elements in a list
void showlist(TransactionIdList g)
{
  for (long it : g) {
    std::cout << '\t' << it;
    std::cout << '\n';
  }
}

SCENARIO("Verify list <int>", "[list <int>]")
{

  TransactionIdList gqlist1, gqlist2;

  for (long i = 0; i < 10; ++i) {
    gqlist1.push_back(i * 2);
    gqlist2.push_front(i * 3);
  }
  std::cout << "\nList 1 (gqlist1) is : ";
  showlist(gqlist1);

  std::cout << "\nList 2 (gqlist2) is : ";
  showlist(gqlist2);

  std::cout << "\ngqlist1.front() : " << gqlist1.front();
  std::cout << "\ngqlist1.back() : " << gqlist1.back();

  std::cout << "\ngqlist1.pop_front() : ";
  gqlist1.pop_front();
  showlist(gqlist1);

  std::cout << "\ngqlist2.pop_back() : ";
  gqlist2.pop_back();
  showlist(gqlist2);

  std::cout << "\ngqlist1.reverse() : ";
  gqlist1.reverse();
  showlist(gqlist1);

  std::cout << "\ngqlist2.sort(): ";
  gqlist2.sort();
  showlist(gqlist2);
}
