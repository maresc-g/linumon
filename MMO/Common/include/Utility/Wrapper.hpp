//
// Wrapper.hpp for Wrapper in /home/mestag_a/Documents/Projets/Tek3/PFA/linumon/MMO
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Feb 28 13:17:26 2014 alexis mestag
// Last update Fri Mar 21 16:09:23 2014 alexis mestag
//

#ifndef				__WRAPPER_HPP__
# define			__WRAPPER_HPP__

# include			<chrono>
# include			<random>

template<typename T>
class				Wrapper
{
public:
  typedef T			wrapped_type;

public:
  virtual ~Wrapper() {}
};

template<typename T>
class				ContainerWrapper : public Wrapper<T>
{
private:
  T				*_container;

public:
  typedef typename Wrapper<T>::wrapped_type			container_type;
  typedef typename container_type::iterator			iterator;
  typedef typename container_type::const_iterator		const_iterator;
  typedef typename container_type::reverse_iterator		reverse_iterator;
  typedef typename container_type::const_reverse_iterator	const_reverse_iterator;
  typedef typename container_type::size_type			size_type;

private:
  ContainerWrapper(ContainerWrapper const &rhs);
  ContainerWrapper		&operator=(ContainerWrapper const &rhs);

public:
  T const			&getContainer() const {
    return (*_container);
  }
  T				&getContainer() {
    return (*_container);
  }
  void				setContainer(T const &c) {
    *_container = c;
  }

  const_iterator		randomElement() const
  {
    static unsigned int				seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine		rGen(seed);
    std::uniform_int_distribution<size_type>	distribution(0, this->size() - 1);
    size_type					k = distribution(rGen);
    const_iterator				it = this->begin();

    std::advance(it, k);
    return (it);
  }
public:
  ContainerWrapper() : _container(new T) {}
  virtual ~ContainerWrapper() {
    delete _container;
  }

  iterator			begin() _GLIBCXX_NOEXCEPT { return (_container->begin()); }
  const_iterator		begin() const _GLIBCXX_NOEXCEPT { return (_container->begin()); }
  iterator			end() _GLIBCXX_NOEXCEPT { return (_container->end()); }
  const_iterator		end() const _GLIBCXX_NOEXCEPT { return (_container->end()); }
  reverse_iterator		rbegin() _GLIBCXX_NOEXCEPT { return (_container->rbegin()); }
  const_reverse_iterator	rbegin() const _GLIBCXX_NOEXCEPT { return (_container->rbegin()); }
  reverse_iterator		rend() _GLIBCXX_NOEXCEPT { return (_container->rend()); }
  const_reverse_iterator	rend() const _GLIBCXX_NOEXCEPT { return (_container->rend()); }

#if	__cplusplus >= 201103L
  const_iterator		cbegin() const noexcept { return (_container->cbegin()); }
  const_iterator		cend() const noexcept { return (_container->cend()); }
  const_reverse_iterator	crbegin() const noexcept { return (_container->crbegin()); }
  const_reverse_iterator	crend() const noexcept { return (_container->crend()); }
#endif

  size_type			size() const _GLIBCXX_NOEXCEPT { return (_container->size()); }
};

#endif
