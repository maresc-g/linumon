//
// TalentTreeLoader.hh for TalentTreeLoader in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 19 13:34:16 2014 alexis mestag
// Last update Wed Mar 19 14:54:56 2014 alexis mestag
//

#ifndef				__TALENTTREELOADER_HH__
# define			__TALENTTREELOADER_HH__

# include			<list>
# include			"Loader/ILoader.hh"
# include			"Stats/TalentTree.hh"
# include			"Trame/Trame.hh"

class				TalentTrees
{
public:
  typedef TalentTree		value;

private:
  std::list<TalentTree *>	*_talentTrees;

public:
  TalentTrees();
  virtual ~TalentTrees();

  std::list<TalentTree *> const	&getTalentTrees() const;

  void				addTalentTree(TalentTree *talentTree);

  TalentTree			*getTalentTree(std::string const &name) const;
  TalentTree			*getTalentTree(unsigned int const id) const;
};

class				TalentTreeLoader : public ILoader<TalentTrees>
{
private:
  TalentTrees			*_talentTrees;

public:
  TalentTreeLoader();
  virtual ~TalentTreeLoader();

  virtual bool			serialization(Trame &trame) const;
  virtual bool			deserialization(Trame &trame);

  virtual TalentTrees const	&getLoaderContent() const;
  virtual TalentTrees::value	*getValue(std::string const &name) const;
  virtual TalentTrees::value	*getValue(unsigned int const id) const;
};

#endif
