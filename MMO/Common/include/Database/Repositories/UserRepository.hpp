//
// UserRepository.hpp for UserRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  1 15:25:50 2014 alexis mestag
// Last update Mon Mar 10 20:29:21 2014 alexis mestag
//

#ifndef				__USERREPOSITORY_HPP__
# define			__USERREPOSITORY_HPP__

# include			<algorithm>
# include			<functional>
# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Entities/User-odb.hxx"

template<>
class				Repository<User> : public BaseRepository<User>
{
  friend class			Singleton<Repository<User> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  User				*getByPseudo(std::string const &pseudo, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<User>	query(Database::Query<User>::pseudo == pseudo);
    Database::Result<User>	result(Database::getInstance()->getDb()->query<User>(query));
    User			*ret = NULL;

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
