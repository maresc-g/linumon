//
// CircularBufferManager.hh for  in /home/ansel_l/Documents/Rtype/work/Server
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Mon Oct 28 23:59:10 2013 laurent ansel
// Last update Thu Nov 28 16:58:44 2013 laurent ansel
//

#ifndef 			__CIRCULARBUFFERMANAGER_HH__
# define 			__CIRCULARBUFFERMANAGER_HH__

#include			<map>
#include			<utility>
#include			"Utility/Singleton.hpp"
#include			"Mutex/Mutex.hpp"
#include			"CircularBuffer.hh"

class				CircularBufferManager : public Singleton<CircularBufferManager>
{
  friend class			Singleton<CircularBufferManager>;

public:
  enum				eTypeBuffer
    {
      READ_BUFFER,
      WRITE_BUFFER
    };
private:
  std::map<enum eTypeBuffer, CircularBuffer *>	*_buffer;
  Mutex				*_mutex;
  CircularBufferManager();
  virtual ~CircularBufferManager();
public:
  void				pushTrame(Trame *trame, enum eTypeBuffer const type);
  void				pushFrontTrame(Trame *trame, enum eTypeBuffer const type);
  Trame	const			&getTrame(enum eTypeBuffer const type) const;
  Trame				*popTrame(enum eTypeBuffer const type) const;
  Trame				*popTrame(unsigned int const id, std::string const &proto, enum eTypeBuffer const type) const;
  void				deleteTrame(unsigned int const id);
};

#endif
