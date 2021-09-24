#ifndef _KEYPAIRINTERFACE_HPP
#define _KEYPAIRINTERFACE_HPP

/**
 * WalletInterface
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

using KeyPairId = long;
using KeyPairIdList = std::list<KeyPairId>;
using KeyPairPublicKey = std::string;
using KeyPairPrivateKey = std::string;
using KeyPairSeed = std::string;
using KeyPairSeedList = std::list<std::string>;

/**
  * @brief KeyPairInterface
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
interface KeyPairInterface
{

  //
  //
  //

  /**
     * @brief generates a public/private key pair
     * 
     * https://ssd.eff.org/en/module/deep-dive-end-end-encryption-how-do-public-key-encryption-systems-work
     * 
     */
  virtual KeyPairId generate(const KeyPairSeedList &seeds) const pure;

  /**
     * @brief KeyPairId()
     * @note this value is ideal for table storage 
     * @return KeyPairId of both the public key and private key
     */
  virtual const KeyPairId &keyPairId() const pure;

  /**
     * @brief publicKey()
     * @return std::string of public key
     */
  virtual const KeyPairPublicKey &publicKey() const pure;

  /**
     * @brief publicKeyId()
     * @note this value is ideal for retrieving public keys only
     * @return std::string of public key
     */
  virtual const KeyPairId &publicKeyId() const pure;

  /**
     * @brief privateKey()
     * @return std::string of private key
     */
  virtual const KeyPairPrivateKey &privateKey() const pure;

  /**
     * @brief privateKeyId()
     * @note this value is ideal for retrieving private keys only
     * @return KeyPairId of both the private key only
     */
  virtual const KeyPairId &privateKeyId() const pure;
};

#endif// _KEYPAIRINTERFACE_HPP
