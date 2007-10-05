.. Metafunctions/Concepts//Lambda Expression |30

Lambda Expression
=================

Description
-----------

A |Lambda Expression| is a compile-time invocable entity in either of the following two
forms:

* |Metafunction Class|
* |Placeholder Expression|

Most of the MPL components accept either of those, and the concept
gives us a consice way to describe these requirements.


Expression requirements
-----------------------

See corresponding |Metafunction Class| and |Placeholder Expression| specifications.


Models
------

* |always|
* |unpack_args|
* ``plus<_, int_<2> >``
* ``if_< less<_1, int_<7> >, plus<_1,_2>, _1 >``


See also
--------

|Metafunctions|, |Placeholders|, |apply|, |lambda|
