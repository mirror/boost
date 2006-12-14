# For PNG output (in a very small PNG)
# set terminal png small
# set output "netpipe.png"
# set size 0.5,0.5

# For Encapsulated PostScript output
set terminal postscript enhanced 20
set output "netpipe.eps"

# Common parts
set title "NetPIPE Bandwidth"
set xlabel "Message Size in Bytes"
set ylabel "Bandwidth in MB/s"
set data style lines
set logscale xy
set key right bottom
plot "NPmpi.out" title 'MPI', "NPboost_mpi.out" title "Boost.MPI", "NPmpi_dt.out" title 'MPI (Datatypes)', "NPboost_mpi_dt.out" title 'Boost.MPI (Datatypes)', "NPboost_mpi_ser.out" title 'Boost.MPI (Serialized)'
