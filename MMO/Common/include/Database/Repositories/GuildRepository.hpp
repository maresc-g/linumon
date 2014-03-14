//
// GuildRepository.hpp for GuildRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Mar 14 13:44:58 2014 alexis mestag
// Last update Fri Mar 14 13:45:51 2014 alexis mestag
//

#ifndef				__FACTIONREPOSITORY_HPP__
# define			__FACTIONREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Guild-odb.hxx"

template<>
class				Repository<Guild> : public BaseRepository<Guild>
{
  friend class			Singleton<Repository<Guild> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  Guild			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<Guild>	query(Database::Query<Guild>::name == name);
    Database::Result<Guild>	result(Database::getInstance()->getDb()->query<Guild>(query));
    Guild			*ret = NULL;

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
