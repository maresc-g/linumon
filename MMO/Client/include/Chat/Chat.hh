//
// Chat.hh for  in /home/maresc_g/Projets/en_cours/linumon/MMO
// 
// Made by guillaume marescaux
// Login   <maresc_g@epitech.net>
// 
// Started on  Thu Feb  6 12:55:29 2014 guillaume marescaux
// Last update Wed Feb 19 14:55:09 2014 cyril jourdain
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
  bool				_newMessage;

public:

  // Ctor / Dtor
  Chat();
  virtual ~Chat();

  // Methods
  void				addMsg(std::string const &msg);
  std::list<std::string> const	&getMsgs(void) const;
  bool				getNewMessage() const;
  void				setNewMessage(bool);
};

#endif
