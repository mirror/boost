#include <memory>
#include <string>

#include <boost/move/move.hpp>
#include <boost/container/map.hpp>
#include <boost/container/scoped_allocator.hpp>

template <typename Ty>
class SimpleAllocator
{
public:
	typedef Ty value_type;
	typedef typename std::allocator<Ty>::pointer pointer;
	typedef typename std::allocator<Ty>::size_type size_type;

	SimpleAllocator(int value)
		: _value(value)
	{}

	template <typename T>
	SimpleAllocator(const SimpleAllocator<T> &other)
		: _value(other._value)
	{}

	pointer allocate(size_type n)
	{
		return _allocator.allocate(n);
	}
	void deallocate(pointer p, size_type n)
	{
		_allocator.deallocate(p, n);
	}
private:
	int _value;
	std::allocator<Ty> _allocator;

	template <typename T> friend class SimpleAllocator;
};

template <typename Ty>
class ScopedAllocator : public boost::container::scoped_allocator_adaptor<SimpleAllocator<Ty> >
{
private:
	typedef boost::container::scoped_allocator_adaptor<SimpleAllocator<Ty> > Base;

public:
	ScopedAllocator(int value)
		: Base(SimpleAllocator<Ty>(value))
	{}
};

class Resource
{
private: // Not copyable
	Resource(const Resource &);
	Resource &operator=(const Resource &);
public:
	typedef SimpleAllocator<int> allocator_type;

	Resource(BOOST_RV_REF(Resource)other)
		: _value(other._value), _allocator(boost::move(other._allocator))
	{
		other._value = -1;
	}

	Resource(BOOST_RV_REF(Resource)other, const allocator_type &allocator)
		: _value(other._value), _allocator(allocator)
	{
		other._value = -1;
	}

	Resource(int value, const allocator_type &allocator)
		: _value(value), _allocator(allocator)
	{}
private:
	int _value;
	allocator_type _allocator;
};

typedef std::pair<const std::string, Resource> MapNode;

typedef boost::container::scoped_allocator_adaptor<SimpleAllocator<MapNode> > MapAllocator;

typedef boost::container::map<std::string, Resource, std::less<std::string>, MapAllocator> Map;

int main()
{
	Map map1(std::less<std::string>(), SimpleAllocator<MapNode>(5));

	map1.emplace("foo", 42);
	map1.emplace("bar", 11);

	//Map map2 = map1;
	return 0;
}
