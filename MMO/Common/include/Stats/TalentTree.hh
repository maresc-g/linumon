//
// TalentTree.hh for TalentTree in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jan 31 12:39:07 2014 alexis mestag
// Last update Mon Feb  3 13:43:15 2014 laurent ansel
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
  TalentModel const		*_talent;

private:
  TalentTree();
  TalentTree(std::string const &name);
  TalentTree(TalentTree const &talentTree);

  TalentTree			&operator=(TalentTree const &rhs);

public:
  virtual ~TalentTree();

  TalentModel const		&getTalent() const;
  void				setTalent(TalentModel const &talent);

  virtual bool			serialization(Trame &trame) const;
  static TalentTree		*deserialization(Trame const &trame);
};

# ifdef	ODB_COMPILER
#  pragma db object(TalentTree)
# endif

#endif
