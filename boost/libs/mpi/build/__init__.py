import sys
if sys.platform == 'linux2':
    import dl
    flags = sys.getdlopenflags()
    sys.setdlopenflags(dl.RTLD_NOW|dl.RTLD_GLOBAL)
    import mpi
    sys.setdlopenflags(flags)
else:
import mpi

