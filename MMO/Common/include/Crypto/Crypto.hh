//
// Crypto.hh for  in /home/ansel_l/Documents/Pfa/testCrypto
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Dec  9 20:03:39 2013 laurent ansel
// Last update Tue Dec 10 10:25:56 2013 laurent ansel
//

#ifndef 			__CRYPTO_HH__
# define 			__CRYPTO_HH__

#include			<iostream>
#include			<string>
#include			<iomanip>
#include			<cryptopp/modes.h>
#include			<cryptopp/aes.h>
#include			<cryptopp/filters.h>
#include			"Utility/Singleton.hpp"

#define	KEY			"monastereonline!"

class				Crypto : public Singleton<Crypto>
{
  friend class			Singleton<Crypto>;

private:
  byte				_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
  byte				_iv[CryptoPP::AES::BLOCKSIZE];
  CryptoPP::AES::Encryption	*_crypt;
  CryptoPP::AES::Decryption	*_decrypt;
  CryptoPP::CBC_Mode_ExternalCipher::Encryption	*_encryption;
  CryptoPP::CBC_Mode_ExternalCipher::Decryption	*_decryption;
  Crypto();
  virtual ~Crypto();
public:
  bool				encryption(std::string const &text, std::string &result);
  bool				decryption(std::string const &text, std::string &result);
};

#endif
