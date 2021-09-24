/**
 * GIVEN that a cryptocurrency wallet is a device, physical medium, program or a 
 * service which stores the public and/or private keys  for cryptocurrency transactions. 
 * WHEN we develop the interfaces[1][4] for this using a good mocking framework[2]
 * THEN we can write the tests before the software, (test driven development[3])
 */

#include <fstream>
#include <iostream>// std::cout
#include <sstream>// std::stringstream
#include <string>// std::string
#include <extras/interfaces.hpp>

#include "../include/CppWallet/TransactionInterface.hpp"
#include "catch.hpp"
#include "fakeit.hpp"

//
// https://github.com/eranpeer/FakeIt/wiki/Quickstart
//

using namespace std;
using namespace fakeit;

/**
 * class MockKeyPair
 */

class MockKeyPair implements KeyPairInterface
{
private:
  KeyPairId _keyPairId;
  KeyPairId _publicKeyId;
  KeyPairId _privateKeyId;
  KeyPairPublicKey _keyPairPublicKey;
  KeyPairPrivateKey _KeyPairPrivateKey;

public:
  virtual KeyPairId generate(const KeyPairSeedList &) const { return _keyPairId; };
  virtual const KeyPairPublicKey &publicKey() const { return _keyPairPublicKey; };
  virtual const KeyPairPrivateKey &privateKey() const { return _KeyPairPrivateKey; };

  virtual const KeyPairId &keyPairId() const { return _keyPairId; };
  virtual const KeyPairId &publicKeyId() const { return _publicKeyId; };
  virtual const KeyPairId &privateKeyId() const { return _privateKeyId; };

  friend bool operator==(const KeyPairInterface &, const KeyPairInterface &) { return true; }
};

class Transaction implements TransactionInterface
{
  TransactionIdList _transactionIdList;

public:
  virtual const TransactionInterface &create(
    const KeyPairPublicKey &,
    double) override { return *this; }

  virtual const TransactionInterface &retrieveOne(
    const TransactionId &) override { return *this; };

  virtual const TransactionIdList &retrieveAll(
    const KeyPairPublicKey &) override { return _transactionIdList; };

  friend bool operator==(const TransactionInterface &, const TransactionInterface &) { return true; }
};

/**
 * mocked create
 */

SCENARIO("Mock TransactionInterface: create", "[mock_wallet]")
{
  Transaction correct_answer;
  const auto &publicKey = KeyPairPublicKey();
  Mock<TransactionInterface> mock;
  When(Method(mock, create)).AlwaysDo([&correct_answer](const KeyPairPublicKey &, double) {
    return correct_answer;
  });

  TransactionInterface &i = mock.get();
  REQUIRE(i.create(publicKey, 5.00) == correct_answer);
  Verify(Method(mock, create));
}

/**
 * mocked retrieveOne
 */

SCENARIO("Mock TransactionInterface: retrieveOne", "[mock_wallet]")
{
  Transaction correct_answer;
  const auto &transactionId = TransactionId();
  Mock<TransactionInterface> mock;
  When(Method(mock, retrieveOne)).AlwaysDo([&correct_answer](const TransactionId &) {
    return correct_answer;
  });

  TransactionInterface &i = mock.get();
  REQUIRE(i.retrieveOne(transactionId) == correct_answer);
  Verify(Method(mock, retrieveOne));
}

/**
 * mocked retrieveAll
 */

SCENARIO("Mock TransactionInterface: retrieveAll", "[mock_wallet]")
{
  TransactionIdList correct_answer;

  for (long i = 0; i < 10; ++i) {
    correct_answer.push_back(i * 2);
    correct_answer.push_front(i * 3);
  }

  const auto &publicKey = KeyPairPublicKey();
  Mock<TransactionInterface> mock;
  When(Method(mock, retrieveAll)).AlwaysDo([&correct_answer](const KeyPairPublicKey &) {
    return correct_answer;
  });

  // TransactionInterface &i = mock.get();
  // TransactionIdList test = i.retrieveAll(publicKey);
  // auto size = test.size();
  // REQUIRE(i.retrieveAll(publicKey) == correct_answer);
  // Verify(Method(mock, retrieveAll));
}
