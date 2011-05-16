
all : demoz 

demoz : scenes/space.c scenes/black.c scenes/entry.c scenes/water.c scenes/tunnel.c scenes/screen.c	
	gcc -g -Wall -o demoz -lGL -lglut -lGLU -ljpeg scenes/entry.c scenes/black.c scenes/water.c scenes/tunnel.c scenes/screen.c helpers.c readppm.c readjpeg.c zpr.c loadobj.c shaderutils.c scenes/space.c
clean :
	rm demoz

