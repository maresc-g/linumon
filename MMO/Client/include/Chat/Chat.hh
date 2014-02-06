//
// Chat.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 12:55:29 2014 guillaume marescaux
// Last update Thu Feb  6 13:00:51 2014 guillaume marescaux
//

#ifndef 			__CHAT_HH__
# define 			__CHAT_HH__

#include			<list>
#include			<string>

class				Chat
{
private:

  Chat(Chat const &);
  Chat				&operator=(Chat const &);

private:

  // Attributes
  std::list<std::string>	*_msgs;

public:

  // Ctor / Dtor
  Chat();
  virtual ~Chat();

  // Methods
  void				addMsg(std::string const &msg);
  std::list<std::string> const	&getMsgs(void) const;
};

#endif
