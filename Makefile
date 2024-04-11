#<------------------------------------||-------------------------------------->#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

#<------------------------------------||-------------------------------------->#

PRG_D =# ./philo/

#SRC_F = main.c parser.c philosophers.c dinner.c
#SRC_F = main.c parser.c init_table.c info.c dinner.c philo_actions.c
SRC_F = main.c initialization.c info.c
SRC_D = ./sources3/

OBJ_F = ${SRC_F:.c=.o}
OBJ_D = ./objects/

DEP_F = ${SRC_F:.c=.d}
DEP_D = ./dependencies/

SRC = ${addprefix ${SRC_D}, ${SRC_F}}
OBJ = ${addprefix ${OBJ_D}, ${OBJ_F}}
DEP = ${addprefix ${DEP_D}, ${DEP_F}}

#<------------------------------------||-------------------------------------->#

#COLOR

DF = \033[0;39m#		Default

# Regular Colors
BLACK = \033[0;30m#		Black
RED = \033[0;31m#		Red
GREEN = \033[0;32m#		Green
YELLOW = \033[0;33m#		Yellow
BLUE = \033[0;34m#		Blue
PURPLE = \033[0;35m#		Purple
CYAN = \033[0;36m#		Cyan
WHITE = \033[0;37m#		White

# Bold
BBLACK = \033[1;30m#		Black
BRED = \033[1;31m#		Red
BGREEN = \033[1;32m#		Green
BYELLOW = \033[1;33m#		Yellow
BBLUE = \033[1;34m#		Blue
BPURPLE = \033[1;35m#		Purple
BCYAN = \033[1;36m#		Cyan
BWHITE = \033[1;37m#		White

# Underline
UBLACK = \033[4;30m#		Black
URED = \033[4;31m#		Red
UGREEN = \033[4;32m#		Green
UYELLOW = \033[4;33m#		Yellow
UBLUE = \033[4;34m#		Blue
UPURPLE = \033[4;35m#		Purple
UCYAN = \033[4;36m#		Cyan
UWHITE = \033[4;37m#		White

# Background
ON_BLACK = \033[40m#		Black
ON_RED = \033[41m#		Red
ON_GREEN = \033[42m#		Green
ON_YELLOW = \033[43m#		Yellow
ON_BLUE = \033[44m#		Blue
ON_PURPLE = \033[45m#		Purple
ON_CYAN = \033[46m#		Cyan
ON_WHITE = \033[47m#		White

# High Intensity
IBLACK = \033[0;90m#		Black
IRED = \033[0;91m#		Red
IGREEN = \033[0;92m#		Green
IYELLOW = \033[0;93m#		Yellow
IBLUE = \033[0;94m#		Blue
IPURPLE = \033[0;95m#		Purple
ICYAN = \033[0;96m#		Cyan
IWHITE = \033[0;97m#		White

# Bold High Intensity
BIBLACK = \033[1;90m#		Black
BIRED = \033[1;91m#		Red
BIGREEN = \033[1;92m#		Green
BIYELLOW = \033[1;93m#		Yellow
BIBLUE = \033[1;94m#		Blue
BIPURPLE = \033[1;95m#		Purple
BICYAN = \033[1;96m#		Cyan
BIWHITE = \033[1;97m#		White

# High Intensity backgrounds
ON_IBLACK = \033[0;100m#	Black
ON_IRED = \033[0;101m#		Red
ON_IGREEN = \033[0;102m#	Green
ON_IYELLOW = \033[0;103m#	Yellow
ON_IBLUE = \033[0;104m#		Blue
ON_IPURPLE = \033[0;105m#	Purple
ON_ICYAN = \033[0;106m#		Cyan
ON_IWHITE = \033[0;107m#	White


#<------------------------------------||-------------------------------------->#

all: ${NAME}

color:
	@echo "${BLACK}Black${DF}"
	@echo "${RED}Red${DF}"
	@echo "${GREEN}Green${DF}"
	@echo "${YELLOW}Yellow${DF}"
	@echo "${BLUE}Blue${DF}"
	@echo "${PURPLE}Purple${DF}"
	@echo "${CYAN}Cyan${DF}"
	@echo "${WHITE}White${DF}"
	@echo
	@echo "${BBLACK}BBlack${DF}"
	@echo "${BRED}BRed${DF}"
	@echo "${BGREEN}BGreen${DF}"
	@echo "${BYELLOW}BYellow${DF}"
	@echo "${BBLUE}BBlue${DF}"
	@echo "${BPURPLE}BPurple${DF}"
	@echo "${BCYAN}BCyan${DF}"
	@echo "${BWHITE}BWhite${DF}"
	@echo
	@echo "${IBLACK}IBlack${DF}"
	@echo "${IRED}IRed${DF}"
	@echo "${IGREEN}IGreen${DF}"
	@echo "${IYELLOW}IYellow${DF}"
	@echo "${IBLUE}IBlue${DF}"
	@echo "${IPURPLE}IPurple${DF}"
	@echo "${ICYAN}ICyan${DF}"
	@echo "${IWHITE}IWhite${DF}"
	@echo
	@echo "${BIBLACK}BIBlack${DF}"
	@echo "${BIRED}BIRed${DF}"
	@echo "${BIGREEN}BIGreen${DF}"
	@echo "${BIYELLOW}BIYellow${DF}"
	@echo "${BIBLUE}BIBlue${DF}"
	@echo "${BIPURPLE}BIPurple${DF}"
	@echo "${BICYAN}BICyan${DF}"
	@echo "${BIWHITE}BIWhite${DF}"
	@echo
	@echo "${UBLACK}UBlack${DF}"
	@echo "${URED}URed${DF}"
	@echo "${UGREEN}UGreen${DF}"
	@echo "${UYELLOW}UYellow${DF}"
	@echo "${UBLUE}UBlue${DF}"
	@echo "${UPURPLE}UPurple${DF}"
	@echo "${UCYAN}UCyan${DF}"
	@echo "${UWHITE}UWhite${DF}"
	@echo
	@echo "${ON_BLACK}ONBlack${DF}"
	@echo "${ON_RED}ONRed${DF}"
	@echo "${ON_GREEN}ONGreen${DF}"
	@echo "${ON_YELLOW}ONYellow${DF}"
	@echo "${ON_BLUE}ONBlue${DF}"
	@echo "${ON_PURPLE}ONPurple${DF}"
	@echo "${ON_CYAN}ONCyan${DF}"
	@echo "${ON_WHITE}ONWhite${DF}"
	@echo
	@echo "${ON_IBLACK}ONIBlack${DF}"
	@echo "${ON_IRED}ONIRed${DF}"
	@echo "${ON_IGREEN}ONIGreen${DF}"
	@echo "${ON_IYELLOW}ONIYellow${DF}"
	@echo "${ON_IBLUE}ONIBlue${DF}"
	@echo "${ON_IPURPLE}ONIPurple${DF}"
	@echo "${ON_ICYAN}ONICyan${DF}"
	@echo "${ON_IWHITE}ONIWhite${DF}"

${NAME}: ${PRG_D} ${OBJ_D} ${DEP_D} ${OBJ}
	@${CC} ${CFLAGS} -lpthread ${OBJ} -o ${PRG_D}${NAME}
	@echo "${RED}Compiling progam:${DF}"
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS}${DF} ${BIGREEN}${OBJ_F}${DF} ${BCYAN}-o${DF} ${RED}${PRG_D}${NAME}${DF}"

${OBJ_D}%.o: ${SRC_D}%.c Makefile
	@${CC} ${CFLAGS} -MMD -c $< -o $@
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS} -MMD${DF} ${BCYAN}-c${DF} ${BIRED}$<${DF} ${BCYAN}-o${DF} ${BIGREEN}$@${DF}"
	@mv ${@:.o=.d} ${DEP_D}
	@echo "${BCYAN}mv${DF} ${BYELLOW}${@:.o=.d}${DF} ${BCYAN}${DEP_D}${DF}"

${OBJ_D}:
	@mkdir ${OBJ_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${OBJ_D}${DF}"

${DEP_D}:
	@mkdir ${DEP_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${DEP_D}${DF}"

#${PRG_D}:
#	mkdir ${PRG_D}
#	@echo "${BCYAN}mkdir${DF} ${BCYAN}${PRG_D}${DF}"

#<------------------------------------||-------------------------------------->#

clean:
	@rm -rf ${OBJ_D} ${DEP_D}
	@echo "${RED}rm -rf${DF} ${BIGREEN}OBJECTS: ${OBJ_F}${DF}"
	@echo "${RED}rm -rf${DF} ${BYELLOW}DEPENDENCIES: ${DEP_F}${DF}"

fclean: clean
	@rm -rf ${PRG_D}
	@echo "${RED}rm -rf${DF} ${RED}PROGRAM: ${NAME}${DF}"

re : fclean all

-include ${DEP}

.PHONY: all clean fclean re
#<------------------------------------||-------------------------------------->#
