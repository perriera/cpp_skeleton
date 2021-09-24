#ifndef _TRANSACTIONINTERFACE_HPP
#define _TRANSACTIONINTERFACE_HPP

/**
 * TransactionInterface
 * 
 * BSAPI-1322:
 * 
 * GIVEN that a cryptocurrency wallet is a device, physical medium, program or a service which 
 *       stores the public and/or private keys  for cryptocurrency transactions. 
 * WHEN we develop the interfaces[1][4] for this using a good mocking framework[2]
 * THEN we can write the tests before the software, (test driven development[3])
 * 
 */

#include <iostream>
#include <list>
#include <memory>
#include <extras/interfaces.hpp>
#include "KeyPairInterface.hpp"

/**
  * @brief TransactionInterface
  * 
  * A KeyPair is essentially two strings, (one private, one public) that are generated
  * using a series of seeds, (plus other criteria such as time of day, etc, etc).
  * As long as each every KeyPair instance is unique, this interfacer will work.
  * 
  * PublicKey: https://en.wikipedia.org/wiki/Public-key_cryptography
  * PrivateKey: https://en.bitcoin.it/wiki/Private_key
  * 
  * CRC32 keys are RECOMMENDED for the formation of KeyPairId values.
  * The CRC32 will be generated using the entire contents of both the
  * public key value and the private key value. Hence, whenever we
  * are asked for the presense of a public or private key, we can do
  * a CRC32 operation on they value of either the public or private 
  * key and quickly determine the existance thereof.
  * 
  * In the case where we are only GIVEN the public key, we generate
  * a CRC32 on the given public key and search using that as the id.
  * 
  * In the case where we are only GIVEN the private key, we generate
  * a CRC32 on the given private key and search using that as the id.
  * 
  */

using TransactionId = long;
using TransactionIdList = std::list<TransactionId>;

interface TransactionInterface
{

  /**
    * @brief createTransaction()
    * 
    * Given the public key of someones wallet, and an amount of BTC you 
    * presumably own, create and sign (with a keypair in your wallet) a 
    * transaction to send said transaction to a BTC node using RPC (edited)
    * 
    * @return TransactionInterface
    * 
    */
  virtual const TransactionInterface &create(
    const KeyPairPublicKey &keyPairPublicKey, double amount) pure;

  /**
    * @brief retrieveTransaction()
    * 
    * Given the transaction ID, get all of the available information 
    * about a bitcoin transaction already on the bitcoin network.
    * 
    * @return TransactionInterface
    * 
    */
  virtual const TransactionInterface &retrieveOne(
    const TransactionId &transactionId) pure;

  /**
    * @brief retrieveTransactions()
    * 
    * Given a public key, get all transactions for a given keypair.
    * 
    * @return the KeyPairId of KeyPairInterface instance 
    * 
    */
  virtual const TransactionIdList &retrieveAll(
    const KeyPairPublicKey &keyPairPublicKey) pure;
};

  /** 
    * TODO: Hierarchical Deterministic (HD) Wallet
    * white_check_mark
    * eyes
    * raised_hands
    */


#endif// _TRANSACTIONINTERFACE_HPP
