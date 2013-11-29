//
// Header.hh for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:21:32 2013 laurent ansel
// Last update Fri Nov 29 15:33:33 2013 laurent ansel
//

#ifndef 			__HEADER_HH__
# define 			__HEADER_HH__

#include			<string>
#include			"Utility/ISerialization.hh"

class				Header : public ISerialization
{
private:
  unsigned int			_idClient;
  std::string			_protocole;
public:
  Header(unsigned int const idClient, std::string const &protocole);
  virtual ~Header();
  unsigned int			getIdClient() const;
  std::string const		&getProtocole() const;
  void				setIdClient(unsigned int const id);
  void				setProtocole(std::string const &protocole);
  virtual bool			serialization(Trame &trame);
  virtual bool			deserialization(Trame const &trame);
};

#endif
