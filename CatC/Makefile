BIN_DIR =	./
OBJ_DIR =	obj/
SRC_DIR =	./
RES_DIR =       ../res/

#use Catapult C ac_int librairie (available in OCAE/CIM (uncomment)
#INC_DIR =	/softslin/catapult2011a_200_12/Mgc_home/shared/include/

#use your own ac_int librairie (uncomment)
INC_DIR =       ../include/

#files
BIN =	${BIN_DIR}exec_cat
SRC =	${wildcard ${SRC_DIR}*.cpp}
OBJ =   ${SRC:${SRC_DIR}%.cpp=${OBJ_DIR}%.o}
RES =   ${wildcard ${RES_DIR}*_histo_CatC.pgm}

#flags
CFLAGS =	-g -W -Wall
IFLAGS =	-I${INC_DIR}

#Compiler
CC =		g++

#rules
all:		${BIN}

${BIN}:		${OBJ}
		${CC} $^ -o ${BIN}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp		
		${CC} ${IFLAGS} ${CFLAGS} -c $< -o $@

.PHONY:
	clean
	clean-all

clean: 
	rm -f $(OBJ)
	rm -f ${BIN}

clean-all: clean
	rm -f *.*~
	rm -f ${RES}
