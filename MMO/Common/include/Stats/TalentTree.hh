//
// TalentTree.hh for TalentTree in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 12:39:07 2014 alexis mestag
// Last update Wed Mar 19 13:02:33 2014 alexis mestag
//

#ifndef				__TALENTTREE_HH__
# define			__TALENTTREE_HH__

# include			"Database/Persistent.hh"
# include			"Utility/Nameable.hh"
# include			"Stats/TalentModel.hh"
# include			"Utility/ISerialization.hh"

class				TalentTree : public Persistent, public Nameable, public ISerialization
{
  friend class			odb::access;

private:
  std::list<TalentModel const *>	_talents;

private:
  TalentTree();
  TalentTree(std::string const &name);
  TalentTree(TalentTree const &talentTree);

  TalentTree			&operator=(TalentTree const &rhs);

public:
  virtual ~TalentTree();

  std::list<TalentModel const *> const	&getTalents() const;
  void					setTalents(std::list<TalentModel const *> const &talents);

  virtual bool			serialization(Trame &trame) const;
  static TalentTree		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentTree)
#  pragma db member(TalentTree::name) virtual(std::string) get(getName()) set(setName(?)) unique type("VARCHAR(24)")
#  pragma db member(TalentTree::_talents) value_not_null
# endif

#endif
