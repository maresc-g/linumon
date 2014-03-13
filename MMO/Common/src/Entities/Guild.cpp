//
// Guild.cpp for  in /home/ansel_l/Documents/Pfa/linumon/MMO
// 
// Made by laurent ansel
// Login   <ansel_l@epitech.net>
// 
// Started on  Tue Feb 25 12:43:18 2014 laurent ansel
// Last update Thu Mar 13 17:29:10 2014 alexis mestag
//

#include			<algorithm>
#include			"Entities/Guild.hh"
#ifndef				CLIENT_COMPILATION
# include			"Database/Repositories/PlayerViewRepository.hpp"
# include			"Entities/Guild-odb.hxx"
#endif

Guild::Guild() :
  Persistent(), Nameable(),
  ContainerWrapper<container_type>()
{

}

Guild::Guild(std::string const &name) :
  Persistent(), Nameable(name),
  ContainerWrapper<container_type>()
{

}

Guild::Guild(Guild const &rhs) :
  Persistent(rhs), Nameable(rhs),
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

Guild::~Guild()
{

}

Guild				&Guild::operator=(Guild const &rhs)
{
  if (this != &rhs)
    {

    }
  return (*this);
}

#ifndef				CLIENT_COMPILATION
void				Guild::odbCallback(odb::callback_event e,
						   odb::database &db __attribute__((unused)))
{
  static std::map<odb::callback_event, void (Guild::*)()> const eventToMethod = {
    {odb::callback_event::pre_load,	NULL},
    {odb::callback_event::post_load,	&Guild::retrievePlayers}
  };
  auto			it = eventToMethod.find(e);

  if (it != eventToMethod.end() && it->second) {
    (this->*(it->second))();
  }
}

void				Guild::odbCallback(odb::callback_event e,
						   odb::database &db __attribute__((unused))) const
{
  std::map<odb::callback_event, void (Guild::*)() const> const eventToMethod = {
    {odb::callback_event::pre_persist,	NULL},
    {odb::callback_event::post_persist,	NULL},
    // {odb::callback_event::post_persist,	&Guild::retrievePlayers},
    {odb::callback_event::pre_update,	NULL},
    {odb::callback_event::post_update,	NULL},
    {odb::callback_event::pre_erase,	NULL},
    {odb::callback_event::post_erase,	NULL},
  };
  auto			it = eventToMethod.find(e);

  if (it != eventToMethod.end() && it->second) {
    (this->*(it->second))();
  }
}
#endif

void				Guild::deletePlayers()
{
  static std::function<bool(PlayerView *)>	playerDeleter = [](PlayerView *p) -> bool {
    delete p;
    return (true);
  };
  std::remove_if(this->begin(), this->end(), playerDeleter);
}

void				Guild::retrievePlayers()
{
  this->deletePlayers();
#ifndef				CLIENT_COMPILATION
  Repository<PlayerView>	&rpv = Database::getRepository<PlayerView>();
  std::list<PlayerView *>	*pvs = rpv.getByGuildName(this->getName(), true);

  if (pvs) {
    this->setContainer(*pvs);
    delete pvs;
  }
#endif
}

#ifndef				CLIENT_COMPILATION
void				Guild::addPlayer(Player &player)
{
  Repository<PlayerView>	&rpv = Database::getRepository<PlayerView>();
  std::list<PlayerView *>	*pv = rpv.getByUserId(player.getUser().getPersistentId());
  std::function<bool(PlayerView *)> playerSeeker = [&](PlayerView *p) -> bool {
    return (p->name == player.getName());
  };
  auto				it = std::find_if(pv->begin(), pv->end(), playerSeeker);

  if (pv && it != pv->end()) {
    this->getContainer().push_back(new PlayerView(**it));
  }
  player.setGuild(*this);
}

Guild				*Guild::createAndPersist(std::string const &name)
{
  Repository<Guild>		&rg = Database::getRepository<Guild>();
  Guild				*ret = new Guild(name);

  try {
    rg.persist(*ret);
  }
  catch (odb::object_already_persistent &e){
    delete ret;
    ret = NULL;
  }
  return (ret);
}

#endif

void				Guild::addPlayer(PlayerView *playerView)
{
  this->getContainer().push_back(playerView);
}

bool				Guild::serialization(Trame &trame) const
{
  bool				ret = true;

  trame["GUILD"] = this->getName();
  return (ret);
}

Guild				*Guild::deserialization(Trame const &trame)
{
  Guild			*guild = NULL;

  if (trame.isMember("GUILD"))
    guild = new Guild(trame["GUILD"].asString());
  return (guild);
}
