//
// Database.hpp for Database in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 13:39:52 2014 alexis mestag
// Last update Fri Feb 21 00:10:06 2014 alexis mestag
//

#ifndef			__DATABASE_HPP__
# define		__DATABASE_HPP__

# include		<odb/session.hxx>
# include		<odb/database.hxx>
# include		<odb/mysql/database.hxx>
# include		<odb/mysql/exceptions.hxx>
# include		"Database/Session.hpp"
# include		"Utility/Singleton.hpp"

# define DB_USER	"odbLinumonUser"
# define DB_PASSWORD	"odbLinumonPassword"
# define DB_DATABASE	"Linumon"

template<typename T>
class			Repository;

class			Database : public Singleton<Database>
{
  friend class		Singleton<Database>;

public:
  template<typename T>
  using Query = odb::query<T>;
  template<typename T>
  using Result = odb::result<T>;
  using Transaction = odb::transaction;
  template<typename T>
  using ObjectTraits = odb::object_traits<T>;
  typedef odb::mysql::database	DBType;

private:
  DBType		*_db;

private:
  Database() : Singleton(),
	       _db(new DBType(DB_USER, DB_PASSWORD, DB_DATABASE)) {}
  virtual ~Database() {
    Session::deleteInstance();
    delete _db;
  }

public:
  DBType		*getDb() {
    return (_db);
  }

  template<typename T>
  static Repository<T>	&getRepository() {
    return (*Repository<T>::getInstance());
  }
};

# include		"Database/Repositories/Repository.hpp"

#endif
