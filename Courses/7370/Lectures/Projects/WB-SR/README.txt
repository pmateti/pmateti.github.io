
This dir contains WhiteBoard, a demo example of SR.  It does roughly the
equivalent of the RPC version in /usr/local/lib/Languages/730/C-Whiteboard

Because of the way some of our machines are set up, it is necessary
that you cp the executable into your own directory, and
then run it; e.g. 

wb xmcnm b1 gamma b1 kirk b2 data b2 uhura

#             ^b1 and b2 are names of boards
#      ^ the name of the X11 machine you are logged in


If you wish to rebuild everything, add the SR executables to your
path, as in

set path = ($path /usr/local/lib/Languages/SR/links)

and then do

make clean; make


