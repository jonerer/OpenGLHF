
all : demoz 

demoz : scenes/black.c scenes/entry.c scenes/water.c
	gcc -Wall -o demoz -lGL -lglut -ljpeg scenes/entry.c scenes/black.c scenes/water.c helpers.c readppm.c readjpeg.c zpr.c loadobj.c shaderutils.c
clean :
	rm demoz
