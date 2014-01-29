//
// Database.hpp for Database in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 29 13:39:52 2014 alexis mestag
// Last update Wed Jan 29 13:48:13 2014 alexis mestag
//

#ifndef			__DATABASE_HPP__
# define		__DATABASE_HPP__

# include		<odb/session.hxx>
# include		<odb/database.hxx>
# include		<odb/mysql/database.hxx>
# include		"Utility/Singleton.hpp"

# define DB_USER	"odbLinumon"
# define DB_PASSWORD	"odbLinumonPassword"
# define DB_DATABASE	"LinumonDatabase"

class			Database : public Singleton<Database>
{
  friend class		Singleton<Database>;

public:
  odb::mysql::database	*_db;
  odb::session		*_s;

private:
  Database() : Singleton(),
	       _db(new odb::mysql::database(DB_USER, DB_PASSWORD, DB_DATABASE)),
	       _s(new odb::session) {}
  virtual ~Database() {
    delete _db;
    delete _s;
  }
};

#endif
