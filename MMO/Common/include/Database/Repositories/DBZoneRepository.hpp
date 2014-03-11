//
// DBZoneRepository.hpp for DBZoneRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 10 15:24:18 2014 alexis mestag
// Last update Mon Mar 10 20:28:58 2014 alexis mestag
//

#ifndef				__DBZONEREPOSITORY_HPP__
# define			__DBZONEREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Entities/DBZone-odb.hxx"

template<>
class				Repository<DBZone> : public BaseRepository<DBZone>
{
  friend class			Singleton<Repository<DBZone> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  DBZone			*getByName(std::string const &name, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<DBZone>	query(Database::Query<DBZone>::name == name);
    Database::Result<DBZone>	result(Database::getInstance()->getDb()->query<DBZone>(query));
    DBZone			*ret = NULL;

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
