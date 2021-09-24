#ifndef _WALLETINTERFACE_HPP
#define _WALLETINTERFACE_HPP

/**
 * @brief WalletInterface
 * 
 * BSAPI-1322:
 * 
 * GIVEN that a cryptocurrency wallet is a device, physical medium, program or a service which 
 *       stores the public and/or private keys  for cryptocurrency transactions. 
 * WHEN we develop the interfaces[1][4] for this using a good mocking framework[2]
 * THEN we can write the tests before the software, (test driven development[3])
 * 
 * While the interfaces were mocked up using C++, the plan is implement this interface
 * in a Python environment. So, the logical equivalent of the interface keyword would
 * be the logical next step to porting these interfaces.
 * 
 * @see https://realpython.com/python-interface/
 * 
 */

#include <iostream>
#include <list>
#include <extras/interfaces.hpp>
#include "KeyPairInterface.hpp"


/**
  * @brief WalletInterface
  * 
  * Defines the CRUD interface for storing KeyPairs into a Bitcoin Wallet
  * 
  */
interface WalletInterface
{

  /**
    * @brief store()
    * 
    * Store a KeyPairInterface instance
    * 
    * @note If a KeyPair already exists in the Wallet, then this
    * method is required to throw an exception to that effect, (as
    * there is no such thing as updating a KeyPair instance). 
    * 
    * @return the KeyPairId of KeyPairInterface instance 
    * @exception KeyPairAlreadyExistsException
    * 
    */
  virtual KeyPairId store(const KeyPairInterface &privateKey) pure;

  /**
    * @brief retrieve()
    * 
    * @return retrieve a KeyPairInterface instance, (using the keyPairId value)
    * @exception KeyPairNotFoundInterface
    * 
    */
  virtual const KeyPairInterface &retrieve(const KeyPairId &keyPairId) const pure;

  /**
    * @brief remove()
    * 
    * Remove a KeyPairInterface instance, (using the keyPairId value)
    * @exception KeyPairNotFoundInterface
    * 
    */
  virtual void remove(const KeyPairId &keyPairId) pure;

  /**
    * @brief list()
    * 
    * @note It would have been an ideal to return a const reference
    * to a list of KeyPairInterfaces or KeyPairIds, (from a memory caching
    * perspective). However, we will assume that the number of KeyPairIds
    * that will be stored in a given Wallet can be represented in memory,
    * (as this is a less error prone design). However, this interface 
    * (while it has to be an autorhity), can be improved later if the
    * need arises. 
    * 
    * @return a list of all KeyPairId values stored in the Wallet
    * 
    */
  virtual KeyPairIdList list() const pure;

  /**
    * @brief find...()
    * 
    * @note depending on what information we need from the wallet
    * the following find methods are implemented. 
    * 
    * @return a KeyPairInterface using a variety of parameter types
    * @exception KeyPairNotFoundInterface
    * 
    */
  virtual const KeyPairInterface &findByKeyPair(const KeyPairInterface &keyPairInterface) const pure;
  virtual const KeyPairInterface &findByKeyPairId(const KeyPairId &KeyPairId) const pure;
  virtual const KeyPairInterface &findByPublicKey(const KeyPairPublicKey &keyPairPublicKey) const pure;
  virtual const KeyPairInterface &findByPublicKeyId(const KeyPairId &KeyPairId) const pure;
  virtual const KeyPairInterface &findByPrivateKey(const KeyPairPrivateKey &keyPairPrivateKey) const pure;
  virtual const KeyPairInterface &findByPrivateKeyId(const KeyPairId &KeyPairId) const pure;
};

/**
 * @brief KeyPairNotFoundException
 * 
 */
class KeyPairNotFoundException extends std::exception
{
  std::string _msg;

public:
  KeyPairNotFoundException(const KeyPairId &KeyPairId)
    : _msg(std::to_string(KeyPairId)) {}

  const char *what() const noexcept override
  {
    return _msg.c_str();
  };
};

/**
 * @brief KeyPairNotFoundException
 * 
 */
class KeyPairAlreadyExistsException extends std::exception
{
  std::string _msg;

public:
  KeyPairAlreadyExistsException(const KeyPairId &KeyPairId)
    : _msg(std::to_string(KeyPairId)) {}

  const char *what() const noexcept override
  {
    return _msg.c_str();
  };
};

#endif// _WALLETINTERFACE_HPP
