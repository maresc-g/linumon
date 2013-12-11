//
// ReadWriteAction.hh for  in /home/ansel_l/Documents/Pfa/work
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Thu Dec  5 16:35:26 2013 laurent ansel
// Last update Thu Dec  5 17:06:55 2013 laurent ansel
//

#ifndef 			__READWRITEACTION_HH__
# define 			__READWRITEACTION_HH__

#include			<string>

class				ReadWriteAction
{
public:
  enum				eAction
    {
      READ,
      WRITE
    };
private:
  bool				_use;
  std::string			_protocole;
  enum eAction			_action;
public:
  ReadWriteAction(std::string const &proto, enum eAction const type);
  virtual ~ReadWriteAction();
  std::string const		&getProtocole() const;
  enum eAction			getAction() const;
  bool				isUse() const;
  void				setProtocole(std::string const &protocole);
  void				setAction(enum eAction const type);
  void				clear();
  void				use();
};

#endif
