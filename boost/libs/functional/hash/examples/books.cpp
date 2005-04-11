
//  Copyright Daniel James 2005. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash.hpp>
// If we had std::unordered_set.
//#include <unordered_set>
#include <cassert>

// This example illustrates how to use boost::hash with a custom hash function.
// For full details, see the tutorial.

namespace library
{
    struct book
    {
        int id;
        std::string author;
        std::string title;

        book(int i, std::string const& a, std::string const& t)
            : id(i), author(a), title(t) {}
    };

    bool operator==(book const& a, book const& b)
    {
        return a.id == b.id;
    }

    std::size_t hash_value(book const& b)
    {
        return boost::hash_value(b.id);
    }
}

int main()
{
    library::book knife(3458, "Zane Grey", "The Hash Knife Outfit");
    library::book dandelion(1354, "Paul J. Shanley", "Hash & Dandelion Greens");

    boost::hash<library::book> book_hasher;
    std::size_t knife_hash_value = book_hasher(knife);

    // If we had std::unordered_set:
    //
    //std::unordered_set<library::book, boost::hash<library::book> > books;
    //books.insert(knife);
    //books.insert(library::book(2443, "Lindgren, Torgny", "Hash"));
    //books.insert(library::book(1953, "Snyder, Bernadette M.",
    //    "Heavenly Hash: A Tasty Mix of a Mother's Meditations"));

    //assert(books.find(knife) != books.end());
    //assert(books.find(dandelion) == books.end());
}
