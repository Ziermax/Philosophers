#<--------------------------------|VARIABLES|--------------------------------->#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

#<----------------------------------|FILES|----------------------------------->#

SRC_F = main.c init_data.c philo.c print_action.c oracle.c set_philo.c get_info.c
SRC_D = ./sources/

OBJ_F = ${SRC_F:.c=.o}
OBJ_D = ./objects/

DEP_F = ${SRC_F:.c=.d}
DEP_D = ./dependencies/

SRC = ${addprefix ${SRC_D}, ${SRC_F}}
OBJ = ${addprefix ${OBJ_D}, ${OBJ_F}}
DEP = ${addprefix ${DEP_D}, ${DEP_F}}

#<---------------------------------|COLORS|----------------------------------->#

DF = \033[0;39m#		Default

# Regular Colors
RED = \033[0;31m#		Red

# Bold
BYELLOW = \033[1;33m#	Yellow
BBLUE = \033[1;34m#		Blue
BCYAN = \033[1;36m#		Cyan

# Bold High Intensity
BIRED = \033[1;91m#		Red
BIGREEN = \033[1;92m#	Green

#<---------------------------------|RULES|------------------------------------>#

all: ${NAME}

${NAME}: ${OBJ_D} ${DEP_D} ${OBJ}
#	@${CC} ${CFLAGS} -fsanitize=thread -lpthread ${OBJ} -o ${NAME}
	@${CC} ${CFLAGS} -lpthread ${OBJ} -o ${NAME}
	@echo "${RED}Compiling progam:${DF}"
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS}${DF} ${BIGREEN}${OBJ_F}${DF} \
	${BCYAN}-o${DF} ${RED}${NAME}${DF}"

${OBJ_D}%.o: ${SRC_D}%.c Makefile
	@${CC} ${CFLAGS} -MMD -c $< -o $@
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS} -MMD${DF} ${BCYAN}-c${DF} \
	${BIRED}$<${DF} ${BCYAN}-o${DF} ${BIGREEN}$@${DF}"
	@mv ${@:.o=.d} ${DEP_D}
	@echo "${BCYAN}mv${DF} ${BYELLOW}${@:.o=.d}${DF} ${BCYAN}${DEP_D}${DF}"

${OBJ_D}:
	@mkdir ${OBJ_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${OBJ_D}${DF}"

${DEP_D}:
	@mkdir ${DEP_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${DEP_D}${DF}"

#<---------------------------------|PHONY|------------------------------------>#

clean:
	@rm -rf ${OBJ_D} ${DEP_D}
	@echo "${RED}rm -rf${DF} ${BIGREEN}OBJECTS: ${OBJ_F}${DF}"
	@echo "${RED}rm -rf${DF} ${BYELLOW}DEPENDENCIES: ${DEP_F}${DF}"

fclean: clean
	@rm -rf ${NAME}
	@echo "${RED}rm -rf${DF} ${RED}PROGRAM: ${NAME}${DF}"

re : fclean all

-include ${DEP}

.PHONY: all clean fclean re
#<---------------------------------------------------------------------------->#
