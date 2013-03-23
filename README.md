htop with vi-like movement and temperature meter patches.
--------------------------------------------------------
You might have some problems with the Makefile.
If you have problems check the file: CRT.h and add TEMPERATURE to the array
of colors.
There might be other problem with the Makefile.
Also, for the temp I'm just scraping data from /proc/ but on some other 
distro the files might vary.
