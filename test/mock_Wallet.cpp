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

#include "../include/CppWallet/WalletInterface.hpp"
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

/**
 * mocked store
 */

SCENARIO("Mock WalletInterface: store", "[mock_wallet]")
{
  KeyPairId correct_answer = 0x4897374;
  const auto &keyPair = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, store)).Return(correct_answer);

  WalletInterface &i = mock.get();
  REQUIRE(i.store(keyPair) == correct_answer);
  Verify(Method(mock, store));
}

/**
 * mocked retrieve
 */

SCENARIO("Mock WalletInterface: retrieve", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, retrieve)).AlwaysDo([&correct_answer](const KeyPairId &) {
    return correct_answer;
  });

  KeyPairId keyPairId;

  WalletInterface &i = mock.get();
  REQUIRE(i.retrieve(keyPairId) == correct_answer);
  Verify(Method(mock, retrieve));
}

/**
 * mocked remove
 */

SCENARIO("Mock WalletInterface: remove", "[mock_wallet]")
{
  Mock<WalletInterface> mock;
  When(Method(mock, remove)).AlwaysDo([](const KeyPairId &) {});

  KeyPairId keyPairId;

  WalletInterface &i = mock.get();
  i.remove(keyPairId);
  Verify(Method(mock, remove));
}

/**
 * mocked list
 */

SCENARIO("Mock WalletInterface: list", "[mock_wallet]")
{
  KeyPairIdList keyPaidList;
  const KeyPairIdList &correct_answer = keyPaidList;
  Mock<WalletInterface> mock;
  When(Method(mock, list)).AlwaysDo([&keyPaidList]() { return keyPaidList; });

  keyPaidList.push_back(KeyPairId());
  keyPaidList.push_back(KeyPairId());
  WalletInterface &i = mock.get();
  REQUIRE(i.list() == correct_answer);
  Verify(Method(mock, list));
}

/**
 * mocked KeyPairNotFoundException
 */

SCENARIO("Mock WalletInterface: KeyPairNotFoundException", "[mock_wallet]")
{
  Mock<WalletInterface> mock;
  When(Method(mock, remove)).Throw(KeyPairNotFoundException(KeyPairId()));

  WalletInterface &i = mock.get();
  REQUIRE_THROWS_AS(i.remove(KeyPairId()), KeyPairNotFoundException);
  Verify(Method(mock, remove));
}

/**
 * mocked KeyPairAlreadyExistsException
 */

SCENARIO("Mock WalletInterface: KeyPairAlreadyExistsException", "[mock_wallet]")
{
  Mock<WalletInterface> mock;
  When(Method(mock, store)).Throw(KeyPairAlreadyExistsException(KeyPairId()));

  WalletInterface &i = mock.get();
  REQUIRE_THROWS_AS(i.store(MockKeyPair()), KeyPairAlreadyExistsException);
  Verify(Method(mock, store));
}

/**
 * mocked findByKeyPair
 */

SCENARIO("Mock WalletInterface: findByKeyPair", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByKeyPair)).AlwaysDo([&correct_answer](const KeyPairInterface &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByKeyPair(correct_answer) == correct_answer);
  Verify(Method(mock, findByKeyPair));
}

/**
 * mocked findByKeyPairId
 */

SCENARIO("Mock WalletInterface: findByKeyPairId", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByKeyPairId)).AlwaysDo([&correct_answer](const KeyPairId &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByKeyPairId(KeyPairId()) == correct_answer);
  Verify(Method(mock, findByKeyPairId));
}

/**
 * mocked findByPublicKey
 */

SCENARIO("Mock WalletInterface: findByPublicKey", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByPublicKey)).AlwaysDo([&correct_answer](const KeyPairPublicKey &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByPublicKey(KeyPairPublicKey()) == correct_answer);
  Verify(Method(mock, findByPublicKey));
}

/**
 * mocked findByPublicKeyId
 */

SCENARIO("Mock WalletInterface: findByPublicKeyId", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByPublicKeyId)).AlwaysDo([&correct_answer](const KeyPairId &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByPublicKeyId(KeyPairId()) == correct_answer);
  Verify(Method(mock, findByPublicKeyId));
}

/**
 * mocked findByPrivateKey
 */

SCENARIO("Mock WalletInterface: findByPrivateKey", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByPrivateKey)).AlwaysDo([&correct_answer](const KeyPairPublicKey &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByPrivateKey(KeyPairPublicKey()) == correct_answer);
  Verify(Method(mock, findByPrivateKey));
}

/**
 * mocked findByPrivateKeyId
 */

SCENARIO("Mock WalletInterface: findByPrivateKeyId", "[mock_wallet]")
{
  const auto &correct_answer = MockKeyPair();
  Mock<WalletInterface> mock;
  When(Method(mock, findByPrivateKeyId)).AlwaysDo([&correct_answer](const KeyPairId &) {
    return correct_answer;
  });

  WalletInterface &i = mock.get();
  REQUIRE(i.findByPrivateKeyId(KeyPairId()) == correct_answer);
  Verify(Method(mock, findByPrivateKeyId));
}
