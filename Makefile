###		DIRECTORY		###
HEADER		=	./inc/cub3D.h
BUILD_D		=	./build
SRC_D 		=	src/
PARS_D		=	${SRC_D}parsing/
PRINT_D		=	${SRC_D}printer/
DISP_D		=	${SRC_D}display/
RAY_D		=	${SRC_D}raycast/
vpath %.c src ${PARS_D} ${PRINT_D} ${DISP_D} ${RAY_D}

###		SOURCE FILES		###
PARS_FILES	=	parser.c\
				parser_utils.c\
				texture.c\
				rgb.c\
				misc_utils.c\
				map_check.c
PRINT_FILES	=	error.c\
				dataprint.c
DISP_FILES	=	init.c\
				image_utils.c\
				draw_rect.c\
				draw_line.c\
				movements.c\
				hooks.c\
				displayer.c\
				maximap.c\
				minimap.c\
				outro.c \
				alpha.c \
				weapon.c
RAY_FILES	=	raycaster.c\
				dda.c
MAIN_FILES	=	main.c endfree.c

SRCS 		=	${MAIN_FILES} ${PARS_FILES} ${PRINT_FILES} ${DISP_FILES} ${RAY_FILES}
OBJS		=	${SRCS:%.c=$(BUILD_D)/%.o}

###		DEFINITIONS		###
NAME		=	cub3D
LIBFT		=	./libs/libft/libft.a
MLX			=	./libs/mlx/libmlx.a
XWIN		=	-lXext -lX11
SHELL		=	/bin/bash
CC			=	cc

###		SCREEN RES		###
DIM			:=	$(shell xdpyinfo | grep dim | grep -o "[0-9]*x[0-9]* pixels")
WIDTH		:=	$(shell echo ${DIM} | cut -d'x' -f1 | grep -o "[0-9]*")
HEIGHT		:=	$(shell echo ${DIM} | cut -d'x' -f2 | grep -o "[0-9]*")
RES_ALERT	:=	"\033[31mScreen res is lower than 1920x1080. You might not enjoy the game, please set pixel resolution to 1920x1080.\033[m"
RES_OK		:=	"\033[32mScreen display set to 1920x1080. Launch game with: \033[4\;36\;1m\.\/cub3D \<map\.cub\>\033[m"

###		COUNTERS DEF		###
OS				=	$(shell uname -s)
INTROMACINTEL	=	60
INTROUBUNTU		=	750
INTRO			=	$(shell [[ ${OS} = "Darwin" ]] && echo ${INTROMACINTEL} || echo ${INTROUBUNTU} )
COUNTER_DEFINE	=	"-D INTRO_COUNTER=${INTRO}"

###		OPTIONS		###
CFLAGS		=	-Wall -Wextra -Werror -g3
LDFLAGS		=	-lm ${LIBFT} ${MLX} ${XWIN}
REDIRVOID	=	>/dev/null 2>&1

###		COMMANDS DISP	###
WASD		=	"[WASD]\\t\\t: move around\\n"
SHIFT		=	"[Lshift]\\t: sprint\\n"
ARROWS		=	"[Left/Right]\\t: turn\\n"
QUIT		=	"[Q]\\t\\t: quit game, red cross leftclick also works"
OUTRO		=	"[ESC]\\t\\t: pause game\\n"
MAP			=	"[M]\\t\\t: on/off full map view, leftclick to teleport\\n"

###		RULES		###
$(BUILD_D)/%.o: %.c ${HEADER}
			@mkdir -p $(dir $@)
			@echo -e "\033[32m\c"
			${CC} ${CFLAGS} ${COUNTER_DEFINE} -c $< -o $@
			@echo -e "\033[0m\c"

all:		${NAME} screen_res_alert print_cmds

${NAME}:	${LIBFT} ${MLX} ${OBJS} ${HEADER}
			@echo -e "\033[32m\c"
			${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo -e "Link complete for exec --> \033[4;36;1m${NAME}\033[0m"

${LIBFT}:
			@echo -ne "\033[33mlibft: compilation ...\033[0m"
			@make --no-print-directory -C ./libs/libft/
			@echo -e "\r\033[33mlibft: compiled!           \033[0m"

screen_res_alert:
		@echo -e $(shell [[ ${WIDTH} -ge 1920 && ${HEIGHT} -ge 1080 ]] && echo -e ${RES_OK} || echo -e ${RES_ALERT} ) > /dev/stderr

print_cmds:
		@echo -e "\033[36;1mCOMMANDS :\033[0m"
		@echo -e "\033[36m${WASD}${SHIFT}${ARROWS}${MAP}${OUTRO}${QUIT}\033[0m"


${MLX}:
			@echo -ne "\033[33mmlx: compilation ...\033[0m"
			@make --no-print-directory -C ./libs/mlx >/dev/null 2>&1
			@echo -e "\r\033[33mmlx: compiled!            \033[0m"

clean:
			@make --no-print-directory clean -C ./libs/libft/ >/dev/null 2>&1
			@make --no-print-directory clean -C ./libs/mlx/ >/dev/null 2>&1
			@rm -rf ${BUILD_D}
			@echo -e "\033[32m${NAME} obj cleaned"

fclean:		clean
			@make --no-print-directory fclean -C ./libs/libft/
			@rm -rf ${NAME}
			@echo -e "\033[32m${NAME} fcleaned\033[m"

re:			fclean all

.PHONY:		all clean re screen_res_alert
