#include <boost/iterator/transform_iterator.hpp>

template< class Map >
struct select_first
{
    typedef typename Map::key_type& result_type;
    
    result_type operator()( const typename Map::value_type& r ) const
    {
        return r.first;
    }
};

template< class Map >
struct select_second
{
    typedef typename Map::mapped_type& result_type;
    
    result_type operator()( const typename Map::value_type& r ) const
    {
        return r.second;
    }
};

template< class Map >
struct map_key_iterator : 
    public boost::transform_iterator< select_first<Map>, 
                                      typename Map::const_iterator >
{
private:
    typedef boost::transform_iterator< select_first<Map>, 
                                       typename Map::const_iterator >
        base;
    
    typedef typename Map::const_iterator iterator;
public:
    map_key_iterator() : base()
    { }

    map_key_iterator( iterator x ) : base(x)
    { }

    map_key_iterator& operator=( iterator r )
    {
        base::operator=(r);
        return *this;
    }
};


template< class Map >
struct map_value_iterator : 
    public boost::transform_iterator< select_second<Map>, 
                                      typename Map::iterator >
{
private:
    typedef boost::transform_iterator< select_second<Map>, 
                                       typename Map::iterator >
        base;
    typedef typename Map::iterator iterator;
    
public:
    map_value_iterator() : base()
    { }

    map_value_iterator( iterator x ) : base(x)
    { }    

    map_value_iterator& operator=( iterator r )
    {
        base::operator=(r);
        return *this;
    }

};


template< class Map >
struct map_const_value_iterator : 
    public boost::transform_iterator< select_second<Map>, 
                                      typename Map::const_iterator >
{
private:
    typedef boost::transform_iterator< select_second<Map>, 
                                       typename Map::const_iterator >
        base;
    typedef typename Map::const_iterator iterator;
public:
    map_const_value_iterator() : base()
    { }

    map_const_value_iterator( iterator x ) : base(x)
    { }

    map_const_value_iterator& operator=( iterator r )
    {
        base::operator=(r);
        return *this;
    }
};

#include <map>

int main()
{
    typedef std::map<int,int> map;

    map m;
    map_key_iterator<map> key_begin = m.begin();
    map_value_iterator<map> value_begin = m.begin();
    map_const_value_iterator<map> value_end = m.end();
        
    key_begin++;
    value_begin++;
    value_end--;
}


