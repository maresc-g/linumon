//
// Header.hh for  in /home/ansel_l/Documents/Pfa/work/Common
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Fri Nov 29 15:21:32 2013 laurent ansel
// Last update Mon Dec  9 14:37:20 2013 laurent ansel
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
  Header(unsigned int const idClient = 0, std::string const &protocole = "");
  Header(Header const &header);
  virtual ~Header();
  Header			&operator=(Header const &Header);
  unsigned int			getIdClient() const;
  std::string const		&getProtocole() const;
  void				setIdClient(unsigned int const id);
  void				setProtocole(std::string const &protocole);
  void				setAll(unsigned int const id, std::string const &protocole);
  virtual bool			serialization(Trame &trame);
  virtual bool			deserialization(Trame const &trame);
};

#endif
