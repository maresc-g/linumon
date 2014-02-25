//
// FactionRepository.hpp for FactionRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Feb 25 12:42:22 2014 alexis mestag
// Last update Tue Feb 25 12:52:16 2014 alexis mestag
//

#ifndef				__FACTIONREPOSITORY_HPP__
# define			__FACTIONREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Faction-odb.hxx"

template<>
class				Repository<Faction> : public BaseRepository<Faction>
{
  friend class			Singleton<Repository<Faction> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
    Faction			*getByName(std::string const &name) {
    Database::Transaction	t(Database::getInstance()->getDb()->begin());
    Database::Query<Faction>	query(Database::Query<Faction>::name == name);
    Database::Result<Faction>	result(Database::getInstance()->getDb()->query<Faction>(query));
    Faction			*ret = NULL;

    if (result.size())
      ret = result.begin().load();

    t.commit();
    return (ret);
  }
};

#endif
