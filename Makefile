ALL_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp|h)" | xargs)
CPP_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp)" | xargs)

all: game

game: $(ALL_FILES)
	@echo '======== Game'
	g++ -Wall -o game $(CPP_FILES) -framework sfml-graphics -framework sfml-window -framework sfml-system -framework OpenGL -framework GLUT
	@echo '======== done'
	@echo

