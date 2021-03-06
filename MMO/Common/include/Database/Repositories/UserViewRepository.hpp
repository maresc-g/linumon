//
// UserViewRepository.hpp for UserViewRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 10:02:02 2014 alexis mestag
// Last update Mon Mar 10 20:29:23 2014 alexis mestag
//

#ifndef				__USERVIEWREPOSITORY_HPP__
# define			__USERVIEWREPOSITORY_HPP__

# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Entities/Views/UserView-odb.hxx"

template<>
class				Repository<UserView> : public Singleton<Repository<UserView> >
{
  friend class			Singleton<Repository<UserView> >;

private:
  Repository() : Singleton() {}
  virtual ~Repository() {}

public:
  UserView			*getByPseudo(std::string const &pseudo, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);
    Database::Query<UserView>	query(Database::Query<UserView>::pseudo == pseudo);
    Database::Result<UserView>	result(Database::getInstance()->getDb()->query<UserView>(query));
    UserView			*ret = NULL;

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
