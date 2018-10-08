#target: dependencies
#	rule to build
#

# Work cited: https://askubuntu.com/questions/433943/how-to-clean-executable-using-make-clean
# 	      https://www.cs.bu.edu/teaching/cpp/writing-makefiles/

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -g
CXXFLAGS += -Wall 
#CXXFLAGS += -O3
#CXXFLAGS += -pedantic-errors
#LDFLAGS = -lboost_date_time

OBJS =ant.o critter.o doodleBug.o game.o gameMenu.o menuValidation.o predPreyMain.o 
SRCS =ant.cpp critter.cpp doodleBug.cpp game.cpp gameMenu.cpp menuValidation.cpp predPreyMain.cpp
HEADERS =ant.hpp critter.hpp doodleBug.hpp game.hpp gameMenu.hpp menuValidation.hpp

predPreyMain: ${OBJS} 	
	${CXX} ${CXXFLAGS} -o predPreyMain predPreyMain.o ant.o critter.o doodleBug.o game.o menuValidation.o gameMenu.o 

predPreyMain.o: predPreyMain.cpp ${HEADERS}
	 ${CXX} ${CXXFLAGS} -c predPreyMain.cpp

ant.o:ant.hpp
critter.o:critter.hpp
doodleBug.o:doodleBug.hpp
game.o:game.hpp
gameMenu.o:gameMenu.hpp
menuValidation.o:menuValidation.hpp

clean: ${OBJS}
	-rm *.o ${OBJS} predPreyMain
