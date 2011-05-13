CPP = g++
RM  = rm -f

BIN      = littleWorld
TAREGETS = $(shell find . -type f -name "*" | grep -E "\.(cpp)" | sed "s/\.cpp/\.o/g" | xargs) $(BIN)
OBJECTS  = $(shell find . -type f -name "*" | grep -E "\.(o)" | xargs)

LIBRARIES = -L/Library/Frameworks/boost.framework/opt/local/lib/ -lboost_signals
INCLUDES  = -I/Library/Frameworks/boost.framework/opt/local/include/
FRAMWORKS = -framework sfml-graphics -framework sfml-window -framework sfml-system -framework OpenGL -framework GLUT

FLAGS = $(INCLUDES)

all: $(TAREGETS)

clean:
	${RM} $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $(BIN) $(LIBRARIES) $(FRAMWORKS)

./object/dynamicObject/Player.o: object/dynamicObject/Player.cpp
	$(CPP) -c object/dynamicObject/Player.cpp -o object/dynamicObject/Player.o $(FLAGS)

./object/dynamicObject/Enemy.o: object/dynamicObject/Enemy.cpp
	$(CPP) -c object/dynamicObject/Enemy.cpp -o object/dynamicObject/Enemy.o $(FLAGS)

./object/DynamicObject.o: object/DynamicObject.cpp
	$(CPP) -c object/DynamicObject.cpp -o object/DynamicObject.o $(FLAGS)

./object/staticObject/Tile.o: object/staticObject/Tile.cpp
	$(CPP) -c object/staticObject/Tile.cpp -o object/staticObject/Tile.o $(FLAGS)

./object/StaticObject.o: object/StaticObject.cpp
	$(CPP) -c object/StaticObject.cpp -o object/StaticObject.o $(FLAGS)

./Object.o: Object.cpp
	$(CPP) -c Object.cpp -o Object.o $(FLAGS)

./util/Conf.o: util/Conf.cpp
	$(CPP) -c util/Conf.cpp -o util/Conf.o $(FLAGS)

./util/Vector2.o: util/Vector2.cpp
	$(CPP) -c util/Vector2.cpp -o util/Vector2.o $(FLAGS)

./util/IntersectionFunctions.o: util/IntersectionFunctions.cpp
	$(CPP) -c util/IntersectionFunctions.cpp -o util/IntersectionFunctions.o $(FLAGS)

./util/Console.o: util/Console.cpp
	$(CPP) -c util/Console.cpp -o util/Console.o $(FLAGS)

./util/Direction.o: util/Direction.cpp
	$(CPP) -c util/Direction.cpp -o util/Direction.o $(FLAGS)

./util/Pathfinder.o: util/Pathfinder.cpp
	$(CPP) -c util/Pathfinder.cpp -o util/Pathfinder.o $(FLAGS)

./util/Position.o: util/Position.cpp
	$(CPP) -c util/Position.cpp -o util/Position.o $(FLAGS)

./util/Segment.o: util/Segment.cpp
	$(CPP) -c util/Segment.cpp -o util/Segment.o $(FLAGS)

./util/Quad.o: util/Quad.cpp
	$(CPP) -c util/Quad.cpp -o util/Quad.o $(FLAGS)

./util/Point.o: util/Point.cpp
	$(CPP) -c util/Point.cpp -o util/Point.o $(FLAGS)

./World.o: World.cpp
	$(CPP) -c World.cpp -o World.o $(FLAGS)

./Camera.o: Camera.cpp
	$(CPP) -c Camera.cpp -o Camera.o $(FLAGS)

./Game.o: Game.cpp
	$(CPP) -c Game.cpp -o Game.o $(FLAGS)

./main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(FLAGS)

