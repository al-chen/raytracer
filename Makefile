CC = g++
# ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
# 	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
# 	LDFLAGS = -framework GLUT -framework OpenGL \
#     	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
#     	-lGL -lGLU -lm -lstdc++
# else
# 	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
# 	LDFLAGS = -lglut -lGLU -lGL
# endif

RM = /bin/rm -f 
all: testImage

classes.h.gch: classes.h
	$(CC) classes.h

Color.o: Color.cpp classes.h
	$(CC) -c Color.cpp

DirectionalLight.o: DirectionalLight.cpp classes.h
	$(CC) -c DirectionalLight.cpp

Film.o: Film.cpp classes.h
	$(CC) -c Film.cpp

Light.o: Light.cpp classes.h
	$(CC) -c Light.cpp

Matrix.o: Matrix.cpp classes.h
	$(CC) -c Matrix.cpp

ObjParser.o: ObjParser.cpp classes.h
	$(CC) -c ObjParser.cpp

Point.o: Point.cpp classes.h
	$(CC) -c Point.cpp

PointLight.o: PointLight.cpp classes.h
	$(CC) -c PointLight.cpp

Ray.o: Ray.cpp classes.h
	$(CC) -c Ray.cpp

Raytracer.o: Raytracer.cpp classes.h
	$(CC) -c Raytracer.cpp

Scene.o: Scene.cpp classes.h
	$(CC) -c Scene.cpp

Shape.o: Shape.cpp classes.h
	$(CC) -c Shape.cpp

Sphere.o: Sphere.cpp classes.h
	$(CC) -c Sphere.cpp

Triangle.o: Triangle.cpp classes.h
	$(CC) -c Triangle.cpp

Vector.o: Vector.cpp classes.h
	$(CC) -c Vector.cpp

main.o: main.cpp classes.h
	$(CC) -c main.cpp

testImage: Color.o DirectionalLight.o Film.o Light.o ObjParser.o Matrix.o Point.o PointLight.o Ray.o Raytracer.o Scene.o Shape.o Sphere.o Triangle.o Vector.o main.o
	$(CC) -o testImage Color.o DirectionalLight.o Film.o Light.o ObjParser.o Matrix.o Point.o PointLight.o Ray.o Raytracer.o Scene.o Shape.o Sphere.o Triangle.o Vector.o main.o

clean: 
	$(RM) *.o testImage
 


