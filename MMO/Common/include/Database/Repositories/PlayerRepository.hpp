//
// PlayerRepository.hpp for PlayerRepository in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  3 17:41:44 2014 alexis mestag
// Last update Mon Mar 10 20:36:44 2014 alexis mestag
//

#ifndef				__PLAYERREPOSITORY_HPP__
# define			__PLAYERREPOSITORY_HPP__

# include			"Database/Database.hpp"
# include			"Database/Repositories/Repository.hpp"
# include			"Database/Repositories/MobRepository.hpp"
# include			"Entities/Player-odb.hxx"

template<>
class				Repository<Player> : public BaseRepository<Player>
{
  friend class			Singleton<Repository<Player> >;

private:
  Repository() : BaseRepository() {}
  virtual ~Repository() {}

public:
  virtual void			smartUpdate(Player &p, bool const inTr = false) {
    Database::Transaction	*t = Database::getNewTransaction(inTr);

    /*
    ** Updating Talents
    */
    std::cout << "Updating talents for " << p.getName() << std::endl;
    Repository<Talent>		*rt = &Database::getRepository<Talent>();
    for (auto it = p.getTalents().begin() ; it != p.getTalents().end() ; ++it) {
      std::cout << "\t Talent is persistent : " << std::boolalpha << (*it)->isPersistent() << std::noboolalpha << std::endl;
      rt->smartUpdate(**it, !inTr ? !inTr : inTr);
    }

    BaseRepository<Player>::smartUpdate(p, !inTr ? !inTr : inTr);

    /*
    ** Updating Stats
    */
    Repository<Stat>		*rStat = &Database::getRepository<Stat>();
    for (auto it = p.getStats().begin() ; it != p.getStats().end() ; ++it) {
      rStat->smartUpdate(**it, !inTr ? !inTr : inTr);
    }

    /*
    ** Updating Equipments
    */
    // Repository<Stuff>		*rStuff = &Database::getRepository<Stuff>();
    // for (auto it = p.getEquipment().begin() ; it != p.getEquipment().end() ; ++it) {
    //   rStuff->smartUpdate(**it, !inTr ? !inTr : inTr);
    // }

    /*
    ** Updating Mobs
    */
    Repository<Mob>		*rm = &Database::getRepository<Mob>();
    for (auto it = p.getDigitaliser().begin() ; it != p.getDigitaliser().end() ; ++it) {
      rm->smartUpdate(**it, !inTr ? !inTr : inTr);
    }

    /*
    ** Updating Jobs
    */
    Repository<Job>		*rj = &Database::getRepository<Job>();
    for (auto it = p.getJobs().begin() ; it != p.getJobs().end() ; ++it) {
      rj->smartUpdate(**it, !inTr ? !inTr : inTr);
    }

    if (t) {
      t->commit();
      delete t;
    }
  }
};

#endif
