//
// AuthorizedStatKeysRepository.hpp for AuthorizedStatKeysRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 12 20:59:22 2014 alexis mestag
// Last update Wed Mar 12 21:01:28 2014 alexis mestag
//

#ifndef				__AUTHORIZEDSTATKEYSREPOSITORY_HPP__
# define			__AUTHORIZEDSTATKEYSREPOSITORY_HPP__

# include			"Database/Repositories/Repository.hpp"
# include			"Stats/AuthorizedStatKeys-odb.hxx"

template<>
class				Repository<AuthorizedStatKeys> : public BaseRepository<AuthorizedStatKeys>
{
  friend class			Singleton<Repository<AuthorizedStatKeys> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  AuthorizedStatKeys				*getByName(std::string const &name,
							   bool const inTr = false) {
    Database::Transaction			*t = Database::getNewTransaction(inTr);
    Database::Query<AuthorizedStatKeys>		query(Database::Query<AuthorizedStatKeys>::name == name);
    Database::Result<AuthorizedStatKeys>	result(Database::getInstance()->getDb()->query<AuthorizedStatKeys>(query));
    AuthorizedStatKeys				*ret = NULL;

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
