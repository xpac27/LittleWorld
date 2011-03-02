ALL_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp|h)" | xargs)
CPP_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp)" | xargs)

BOOST_INCLUDE_DIR := /opt/local/var/macports/software/boost/1.45.0_1/opt/local/include/
BOOST_LIB_DIR     := /opt/local/var/macports/software/boost/1.45.0_1/opt/local/lib/

all: game

game: $(ALL_FILES)
	@echo '======== Game'
	g++ -Wall -o game $(CPP_FILES) \
	-I $(BOOST_INCLUDE_DIR) \
	-L$(BOOST_LIB_DIR) \
	-lboost_signals -framework sfml-graphics -framework sfml-window -framework sfml-system -framework OpenGL -framework GLUT
	@echo '======== done'
	@echo

