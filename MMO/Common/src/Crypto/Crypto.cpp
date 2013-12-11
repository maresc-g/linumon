//
// Crypto.cpp for  in /home/ansel_l/Documents/Pfa/testCrypto
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Dec  9 23:29:39 2013 laurent ansel
// Last update Tue Dec 10 11:16:47 2013 laurent ansel
//

#include			"Crypto/Crypto.hh"

Crypto::Crypto():
  _crypt(NULL),
  _decrypt(NULL),
  _encryption(NULL),
  _decryption(NULL)
{
  memcpy(_key, KEY, CryptoPP::AES::DEFAULT_KEYLENGTH);
  memset(_iv, 0x0, CryptoPP::AES::BLOCKSIZE);
  _crypt = new CryptoPP::AES::Encryption(_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  _encryption = new CryptoPP::CBC_Mode_ExternalCipher::Encryption(*_crypt, _iv);
  _decrypt = new CryptoPP::AES::Decryption(_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  _decryption = new CryptoPP::CBC_Mode_ExternalCipher::Decryption(*_decrypt, _iv);
}

Crypto::~Crypto()
{
  delete _encryption;
  delete _decryption;
  delete _crypt;
  delete _decrypt;
}

bool				Crypto::encryption(std::string const &text, std::string &result)
{
  try
    {
      CryptoPP::StreamTransformationFilter	encryptor(*_encryption, new CryptoPP::StringSink(result));
      encryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.size());
      encryptor.MessageEnd();
    }
  catch (CryptoPP::Exception const e)
    {
      std::cout << "ERROR encryption" << std::endl;
      return (false);
    }
  return (true);
}

bool				Crypto::decryption(std::string const &text, std::string &result)
{
  try
    {
      CryptoPP::StreamTransformationFilter	decryptor(*_decryption, new CryptoPP::StringSink(result));
      decryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.size());
      decryptor.MessageEnd();
    }
  catch (CryptoPP::Exception const e)
    {
      std::cout << "ERROR decryption" << std::endl;
      return (false);
    }
  return (true);
}
