//
// CartridgeClip.cpp for CartridgeClip in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Mar 26 01:36:47 2014 alexis mestag
// Last update Wed Mar 26 02:47:01 2014 alexis mestag
//

#include				<algorithm>
#include				<functional>
#include				"Entities/CartridgeClip.hh"

CartridgeClip::CartridgeClip() :
  ContainerWrapper<container_type>(),
  _sum(new summary_type)
{

}

CartridgeClip::~CartridgeClip()
{
  this->emptyClip();
  delete _sum;
}

CartridgeClip::CartridgeClip(CartridgeClip const &rhs) :
  ContainerWrapper<container_type>()
{
  *this = rhs;
}

CartridgeClip				&CartridgeClip::operator=(CartridgeClip const &rhs)
{
  if (this != &rhs) {
    this->setClip(rhs.getClip());
    this->setClipFromSummary(rhs.getClipSummary());
  }
  return (*this);
}

void					CartridgeClip::emptyClip()
{
  static std::function<bool(Cartridge *)>	clipEmptier = [](Cartridge *c) -> bool {
    delete c;
    return (true);
  };

  this->getContainer().remove_if(clipEmptier);
  _sum->clear();
}

// CartridgeClip::summary_type const	&CartridgeClip::getSum() const
// {
//   return (*_sum);
// }

// void					CartridgeClip::setSum(summary_type const &sum)
// {
//   *_sum = sum;
// }

void					CartridgeClip::addCartridge(Cartridge const &cartridge)
{
  this->getContainer().push_back(new Cartridge(cartridge));
  (*_sum)[cartridge.getEfficiency()]++;
}

Cartridge				*CartridgeClip::getNextCartridge()
{
  static std::function<bool(Cartridge *, Cartridge *)>	maxCartridgeSeeker = [](Cartridge *c1,
										Cartridge *c2) {
    return (*c1 < *c2);
  };
  auto					it = std::max_element(this->begin(),
							      this->end(),
							      maxCartridgeSeeker);
  Cartridge				*ret = it != this->end() ? *it : NULL;

  if (ret) {
    this->getContainer().erase(it);
    (*_sum)[ret->getEfficiency()]--;
  }
  return (ret);
}

CartridgeClip::container_type const	&CartridgeClip::getClip() const
{
  return (this->getContainer());
}

void					CartridgeClip::setClip(container_type const &c)
{
  this->emptyClip();
  std::for_each(c.begin(), c.end(), [&](Cartridge *cartridge) -> void {
      this->addCartridge(*cartridge);
      (*this->_sum)[cartridge->getEfficiency()]++;
    });
}

CartridgeClip::summary_type const	&CartridgeClip::getClipSummary() const
{
  return (*_sum);
}

void					CartridgeClip::setClipFromSummary(summary_type const &sum)
{
  Cartridge				toAdd;

  this->emptyClip();
  std::for_each(sum.begin(), sum.end(), [&](std::pair<summary_type::key_type,
					    summary_type::mapped_type> const &pair) {
		  toAdd.setEfficiency(pair.first);
		  for (auto i = summary_type::mapped_type() ; i < pair.second ; ++i) {
		    this->addCartridge(toAdd);
		  }
		});
}
