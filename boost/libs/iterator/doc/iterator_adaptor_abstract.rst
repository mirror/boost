The ``iterator_adaptor`` is a base class template derived from an
instantiation of ``iterator_facade``. The core interface functions
expected by ``iterator_facade`` are implemented in terms of the
``iterator_adaptor``\ 's ``Base`` template parameter. A class derived
from ``iterator_adaptor`` typically redefines some of the core
interface functions to adapt the behavior of the ``Base`` type.
Whether the derived class models any of the standard iterator concepts
depends on the operations supported by the ``Base`` type and which
core interface functions of ``iterator_facade`` are redefined in the
``Derived`` class.
