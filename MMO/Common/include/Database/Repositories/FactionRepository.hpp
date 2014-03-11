//
// FactionRepository.hpp for FactionRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Feb 25 12:42:22 2014 alexis mestag
// Last update Mon Mar 10 20:29:01 2014 alexis mestag
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
  Faction			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<Faction>	query(Database::Query<Faction>::name == name);
    Database::Result<Faction>	result(Database::getInstance()->getDb()->query<Faction>(query));
    Faction			*ret = NULL;

    if (result.size())
      ret = result.begin().load();

    if (t) {
      t->commit();
      delete t;
    }
    return (ret);
  }
};

#endif
