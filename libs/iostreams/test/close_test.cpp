/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * Verifies that the close() member functions of filters and devices
 * are called with the correct arguments in the correct order when 
 * they are combined using chains or adapters.
 *
 * File:        libs/iostreams/test/close_test.cpp
 * Date:        Sun Dec 09 16:12:23 MST 2007
 * Copyright:   2007 CodeRage
 * Author:      Jonathan Turkanis
 */

#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/combine.hpp>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/filter/symmetric.hpp>
#include <boost/iostreams/invert.hpp>
#include <boost/iostreams/restrict.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>  
#include "detail/closable.hpp"
#include "detail/operation_sequence.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;
namespace io = boost::iostreams;

void input_chain_test()
{
    // Test input filter and device
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(closable_filter<input>(seq.new_operation(2)));
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test bidirectional filter and device
    {
        operation_sequence  seq;
        chain<input>        ch;

        
        // Test chain::pop()
        ch.push(
            closable_filter<bidirectional>(
                seq.new_operation(2),
                seq.new_operation(3)
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test seekable filter and device
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(closable_filter<seekable>(seq.new_operation(1)));
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test dual-user filter
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(
            closable_filter<dual_use>(
                seq.new_operation(2), 
                seq.new_operation(3)
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct source
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(closable_filter<input>(seq.new_operation(2)));
        ch.push(closable_device<direct_input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<direct_input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct bidirectional device
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(closable_filter<input>(seq.new_operation(2)));
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(3)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(3)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct seekable device
    {
        operation_sequence  seq;
        chain<input>        ch;

        // Test chain::pop()
        ch.push(closable_filter<input>(seq.new_operation(1)));
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void output_chain_test()
{
    // Test output filter and device
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<output>(seq.new_operation(1)));
        ch.push(closable_device<output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test bidirectional filter and device
    {
        operation_sequence  seq;
        chain<output>       ch;

        
        // Test chain::pop()
        ch.push(
            closable_filter<bidirectional>(
                seq.new_operation(2),
                seq.new_operation(3)
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test seekable filter and device
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<seekable>(seq.new_operation(1)));
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test dual-user filter
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(
            closable_filter<dual_use>(
                seq.new_operation(1), 
                seq.new_operation(2)
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct sink
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<output>(seq.new_operation(1)));
        ch.push(closable_device<direct_output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<direct_output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct bidirectional device
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<output>(seq.new_operation(2)));
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(3)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(3)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct seekable device
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<output>(seq.new_operation(1)));
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void bidirectional_chain_test()
{
    // Test bidirectional filter and device
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        
        // Test chain::pop()
        ch.push(
            closable_filter<bidirectional>(
                seq.new_operation(2),
                seq.new_operation(3)
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct bidirectional device
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;

        // Test chain::pop()
        ch.push(
            closable_filter<bidirectional>(
                seq.new_operation(2),
                seq.new_operation(3)
            )
        );
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(
            closable_device<direct_bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void seekable_chain_test()
{
    // Test seekable filter and device
    {
        operation_sequence  seq;
        chain<seekable>     ch;

        // Test chain::pop()
        ch.push(closable_filter<seekable>(seq.new_operation(1)));
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test direct seekable device
    {
        operation_sequence  seq;
        chain<output>       ch;

        // Test chain::pop()
        ch.push(closable_filter<output>(seq.new_operation(1)));
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.pop());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);

        // Test filter reuse and chain::reset()
        seq.reset();
        ch.push(closable_device<direct_seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void stream_test()
{
    // Test source
    {
        operation_sequence                seq;
        stream< closable_device<input> >  str;
        str.open(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(str.close());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test sink
    {
        operation_sequence                 seq;
        stream< closable_device<output> >  str;
        str.open(closable_device<output>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(str.close());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test bidirectional device
    {
        operation_sequence                        seq;
        stream< closable_device<bidirectional> >  str;
        str.open(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(2)
            )
        );
        BOOST_CHECK_NO_THROW(str.close());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test seekable device
    {
        operation_sequence                   seq;
        stream< closable_device<seekable> >  str;
        str.open(closable_device<seekable>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(str.close());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void combine_test()
{
    // Combine a source and a sink
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_device<input>(seq.new_operation(1)),
                closable_device<output>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine two bidirectional devices
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_device<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_device<bidirectional>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                )
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine two seekable devices
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_device<seekable>(seq.new_operation(1)),
                closable_device<seekable>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine an input filter and an output filter
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_filter<input>(seq.new_operation(2)),
                closable_filter<output>(seq.new_operation(3))
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine two bidirectional filters
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_filter<bidirectional>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_filter<bidirectional>(
                    seq.new_operation(4),
                    seq.new_operation(5)
                )
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(6)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine two seekable filters
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_filter<seekable>(seq.new_operation(2)),
                closable_filter<seekable>(seq.new_operation(3))
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(4)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Combine two dual-use filters
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::combine(
                closable_filter<dual_use>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_filter<dual_use>(
                    seq.new_operation(4),
                    seq.new_operation(5)
                )
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(6)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void composite_device_test()
{
    // Compose an input filter with a source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<input>(seq.new_operation(2)),
                closable_device<input>(seq.new_operation(1))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a bidirectional filter with a source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_device<input>(seq.new_operation(1))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a seekable filter with a source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(2)),
                closable_device<input>(seq.new_operation(1))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a dual-use filter with a source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_device<input>(seq.new_operation(1))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose an output filter with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<output>(seq.new_operation(1)),
                closable_device<output>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a bidirectional filter with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_device<output>(seq.new_operation(3))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a seekable filter with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(1)),
                closable_device<output>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a dual-use filter with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_device<output>(seq.new_operation(3))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a bidirectional filter with a bidirectional device
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_device<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(4)
                )
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a seekable filter with a seekable device
    {
        operation_sequence  seq;
        chain<seekable>     ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(1)),
                closable_device<seekable>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void composite_filter_test()
{
    // Compose two input filters
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<input>(seq.new_operation(3)),
                closable_filter<input>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a bidirectional filter with an input filter
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                ),
                closable_filter<input>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_MESSAGE(seq.is_success(), seq.message());
    }

    // Compose a seekable filter with an input filter
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(3)),
                closable_filter<input>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a dual-use filter with an input filter
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                ),
                closable_filter<input>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose two output filters
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<output>(seq.new_operation(1)),
                closable_filter<output>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a bidirectional filter with an output filter
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_filter<output>(seq.new_operation(3))
            )
        );
        ch.push(closable_device<output>(seq.new_operation(4)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a seekable filter with an output filter
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(1)),
                closable_filter<output>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose a dual-use filter with an output filter
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_filter<output>(seq.new_operation(3))
            )
        );
        ch.push(closable_device<output>(seq.new_operation(4)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose two bidirectional filters
    {
        operation_sequence    seq;
        chain<bidirectional>  ch;
        ch.push(
            io::compose(
                closable_filter<bidirectional>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                ),
                closable_filter<bidirectional>(
                    seq.new_operation(2),
                    seq.new_operation(5)
                )
            )
        );
        ch.push(
            closable_device<bidirectional>(
                seq.new_operation(1),
                seq.new_operation(6)
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose two seekable filters
    {
        operation_sequence  seq;
        chain<seekable>     ch;
        ch.push(
            io::compose(
                closable_filter<seekable>(seq.new_operation(1)),
                closable_filter<seekable>(seq.new_operation(2))
            )
        );
        ch.push(closable_device<seekable>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose two dual-use filters for input
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                ),
                closable_filter<dual_use>(
                    seq.new_operation(2),
                    seq.new_operation(5)
                )
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Compose two dual-use filters for output
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::compose(
                closable_filter<dual_use>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                closable_filter<dual_use>(
                    seq.new_operation(1),
                    seq.new_operation(4)
                )
            )
        );
        ch.push(closable_device<output>(seq.new_operation(5)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void invert_test()
{
    // Invert an output filter
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(io::invert(closable_filter<output>(seq.new_operation(2))));
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Invert an input filter
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(io::invert(closable_filter<input>(seq.new_operation(1))));
        ch.push(closable_device<output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void restrict_test()
{
    // Restrict a source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(io::restrict(closable_device<input>(seq.new_operation(1)), 0));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a seekable device
    {
        operation_sequence  seq;
        chain<seekable>     ch;
        ch.push(
            io::restrict(closable_device<seekable>(seq.new_operation(1)), 0)
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a direct source
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::restrict(closable_device<direct_input>(seq.new_operation(1)), 0)
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a direct seekable device
    {
        operation_sequence  seq;
        chain<seekable>     ch;
        ch.push(
            io::restrict(
                closable_device<direct_seekable>(seq.new_operation(1)), 
                0
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict an input filter
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(io::restrict(closable_filter<input>(seq.new_operation(2)), 0));
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a seekable filter
    {
        operation_sequence  seq;
        chain<seekable>     ch;
        ch.push(
            io::restrict(closable_filter<seekable>(seq.new_operation(1)), 0)
        );
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a dual_use filter for input
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::restrict(
                closable_filter<dual_use>(
                    seq.new_operation(2),
                    seq.new_operation(3)
                ),
                0
            )
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Restrict a dual_use filter for output
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::restrict(
                closable_filter<dual_use>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                0
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void symmetric_filter_test()
{
    // Test input
    {
        operation_sequence  seq;
        chain<input>        ch;
        ch.push(
            io::symmetric_filter<closable_symmetric_filter>
                (0, seq.new_operation(2))
        );
        ch.push(closable_device<input>(seq.new_operation(1)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Test output
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::symmetric_filter<closable_symmetric_filter>
                (0, seq.new_operation(1))
        );
        ch.push(closable_device<output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void tee_test()
{
    // Note: The implementation of tee_device closes the first
    // sink before the second

    // Tee two sinks (Borland <= 5.8.2 needs a little help compiling this case,
    // but it executes the closing algorithm correctly)
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                closable_device<output>(seq.new_operation(1)),
                closable_device<
                    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
                        borland_output
                    #else
                        output
                    #endif
                >(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee two bidirectional devices
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                closable_device<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                ),
                closable_device<bidirectional>(
                    seq.new_operation(3),
                    seq.new_operation(4)
                )
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee two seekable devices
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                closable_device<seekable>(seq.new_operation(1)),
                closable_device<seekable>(seq.new_operation(2))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(io::tee(closable_device<output>(seq.new_operation(1))));
        ch.push(closable_device<output>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a bidirectional device
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                closable_device<bidirectional>(
                    seq.new_operation(1),
                    seq.new_operation(2)
                )
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a seekable device
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(io::tee(closable_device<seekable>(seq.new_operation(1))));
        ch.push(closable_device<seekable>(seq.new_operation(2)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

void tee_composite_test()
{
    // This test is probably redundant, but it verifies that
    // ticket #1002 is fixed

    // Tee a composite sink with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<output>(seq.new_operation(1)),
                    closable_device<output>(seq.new_operation(2))
                ),
                closable_device<output>(seq.new_operation(3))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a composite bidirectional device with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<bidirectional>(
                        seq.new_operation(2),
                        seq.new_operation(3)
                    ),
                    closable_device<bidirectional>(
                        seq.new_operation(1),
                        seq.new_operation(4)
                    )
                ),
                closable_device<output>(seq.new_operation(5))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a composite composite seekable device with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<seekable>(seq.new_operation(1)),
                    closable_device<seekable>(seq.new_operation(2))
                ),
                closable_device<output>(seq.new_operation(3))
            )
        );
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }


    // Tee a composite sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<output>(seq.new_operation(1)),
                    closable_device<output>(seq.new_operation(2))
                )
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a composite bidirectional device with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<bidirectional>(
                        seq.new_operation(2),
                        seq.new_operation(3)
                    ),
                    closable_device<bidirectional>(
                        seq.new_operation(1),
                        seq.new_operation(4)
                    )
                )
            )
        );
        ch.push(closable_device<output>(seq.new_operation(5)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }

    // Tee a composite composite seekable device with a sink
    {
        operation_sequence  seq;
        chain<output>       ch;
        ch.push(
            io::tee(
                io::compose(
                    closable_filter<seekable>(seq.new_operation(1)),
                    closable_device<seekable>(seq.new_operation(2))
                )
            )
        );
        ch.push(closable_device<output>(seq.new_operation(3)));
        BOOST_CHECK_NO_THROW(ch.reset());
        BOOST_CHECK_OPERATION_SEQUENCE(seq);
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("execute test");
    test->add(BOOST_TEST_CASE(&input_chain_test));
    test->add(BOOST_TEST_CASE(&output_chain_test));
    test->add(BOOST_TEST_CASE(&bidirectional_chain_test));
    test->add(BOOST_TEST_CASE(&seekable_chain_test));
    test->add(BOOST_TEST_CASE(&stream_test));
    test->add(BOOST_TEST_CASE(&combine_test));
    test->add(BOOST_TEST_CASE(&composite_device_test));
    test->add(BOOST_TEST_CASE(&composite_filter_test));
    test->add(BOOST_TEST_CASE(&invert_test));
    test->add(BOOST_TEST_CASE(&restrict_test));
    test->add(BOOST_TEST_CASE(&symmetric_filter_test));
    test->add(BOOST_TEST_CASE(&tee_test));
    test->add(BOOST_TEST_CASE(&tee_composite_test));
    return test;
}
