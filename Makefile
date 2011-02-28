TARGETS=game

all: $(TARGETS)

game: *
	@echo '======== Game'
	g++ -Wall -o game main.cpp dummy.cpp -framework sfml-graphics -framework sfml-window -framework sfml-system -framework OpenGL -framework GLUT
	@echo '======== done'
	@echo

