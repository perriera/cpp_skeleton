/**
 * GIVEN that a cryptocurrency wallet is a device, physical medium, program or a service which stores the public and/or private keys  for cryptocurrency transactions. WHEN we develop the interfaces[1][4] for this using a good mocking framework[2]THEN we can write the tests before the software, (test driven development[3])
 */

#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string
#include <extras/interfaces.hpp>

#include "../include/CppWallet/KeyPairInterface.hpp"
#include "catch.hpp"
#include "fakeit.hpp"

// interface WalletInterface
// {
//     virtual int foo(int) = 0;
//     virtual int bar(int, int) = 0;
// };

//
// https://github.com/eranpeer/FakeIt/wiki/Quickstart
//

using namespace std;
using namespace fakeit;

/**
 * mocked KeyPairInterface
 */

SCENARIO("Mock KeyPairInterface: generate, publicKey, publicKey", "[mock_keypair]")
{

  Mock<KeyPairInterface> mock;
  KeyPairPublicKey _x = "x";
  KeyPairPrivateKey _y = "y";
  KeyPairId _keyPairId = 0x4897374;
  KeyPairId _publicKeyId = 0x3433434;
  KeyPairId _privateKeyId = 0x534343;
  When(Method(mock, generate)).Return(_keyPairId);
  When(Method(mock, publicKey)).Return(_x);
  When(Method(mock, privateKey)).Return(_y);
  When(Method(mock, keyPairId)).Return(_keyPairId);
  When(Method(mock, publicKeyId)).Return(_publicKeyId);
  When(Method(mock, privateKeyId)).Return(_privateKeyId);

  KeyPairInterface &i = mock.get();
  std::list<std::string> seeds;
  seeds.push_back("a");
  seeds.push_back("b");
  seeds.push_back("c");
  REQUIRE(i.generate(seeds) == _keyPairId);
  REQUIRE(_keyPairId == i.keyPairId());
  REQUIRE(_publicKeyId == i.publicKeyId());
  REQUIRE(_privateKeyId == i.privateKeyId());
  REQUIRE(_x == i.publicKey());
  REQUIRE(_y == i.privateKey());
  Verify(Method(mock, generate));
  Verify(Method(mock, publicKey));
  Verify(Method(mock, privateKey));
}
