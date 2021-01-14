SRC = $(realpath src/mesh_from_file.c) \
       $(realpath src/mesh2d.c) \
	   $(realpath src/operations.c) \
	   $(realpath src/Rtree-search.c) \
	   $(realpath lib/rtree/rtree.c) \
	   $(realpath lib/triangle/triangle.c) \
	   $(realpath src/TestTemps.c) 

OBJ = $(SRC:.c=.o)

CFLAGS = -g -O2 -w -Wall
LDFLAGS = -lm

TARGET = rts_demo

all: $(TARGET)


rts_demo: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	${RM} ${OBJ}   
 