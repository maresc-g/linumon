//
// InitializeConnection.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Sun Dec  8 12:44:43 2013 laurent ansel
// Last update Mon Dec  9 14:39:20 2013 laurent ansel
//

#ifndef 			__INITIALIZECONNECTION_HH__
# define 			__INITIALIZECONNECTION_HH__

#include			<string>
#include			"Utility/ISerialization.hh"

class				InitializeConnection : public ISerialization
{
private:
  unsigned int			_id;
  bool				_tcp;
  bool				_udp;
public:
  InitializeConnection(unsigned int const id = 0, bool const tcp = false, bool const udp = false);
  InitializeConnection(InitializeConnection const &other);
  virtual ~InitializeConnection();
  InitializeConnection		&operator=(InitializeConnection const &other);
  unsigned int			getId() const;
  bool				getTcp() const;
  bool				getUdp() const;
  void				setId(unsigned int const id);
  void				setTcp(bool const tcp);
  void				setUdp(bool const udp);
  void				setAll(unsigned int const id, bool const tcp, bool const udp);
  virtual bool			serialization(Trame &trame);
  virtual bool			deserialization(Trame const &trame);
};

#endif
