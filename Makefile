ALL_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp|h)" | xargs)
CPP_FILES := $(shell find . -type f -name "*" | grep -E "\.(cpp)" | xargs)

BOOST_INCLUDE_DIR := /Library/Frameworks/boost.framework/opt/local/include/
BOOST_LIB_DIR     := /Library/Frameworks/boost.framework/opt/local/lib/

all: littleWorld

littleWorld: $(ALL_FILES)
	@echo '======== LittleWorld'
	g++ -Wall -o littleWorld $(CPP_FILES) \
	-I $(BOOST_INCLUDE_DIR) \
	-L$(BOOST_LIB_DIR) \
	-lboost_signals -framework sfml-graphics -framework sfml-window -framework sfml-system -framework OpenGL -framework GLUT
	@echo '======== done'
	@echo

