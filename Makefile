###		DIRECTORY		###
HEADER		=	./inc/cub3D.h
BUILD_DIR	=	./build
SRC_DIR 	=	src/
PARS_DIR	=	parsing/
PRINT_DIR	=	printer/
DISP_DIR	=	display/
RAY_DIR		=	raycast/

###		SOURCE FILES		###
PARS_NAME	=	parser.c\
				parser_utils.c\
				texture.c\
				rgb.c\
				misc_utils.c\
				map_check.c
PRINT_NAME	=	error.c\
				dataprint.c
DISP_NAME	=	init.c\
				image_utils.c\
				drawers.c\
				hooks.c\
				maximap.c
RAY_NAME	=	utils.c\

PARS_SRC	=	$(addprefix ${PARS_DIR}, ${PARS_NAME})
PRINT_SRC	=	$(addprefix ${PRINT_DIR}, ${PRINT_NAME})
DISP_SRC	=	$(addprefix ${DISP_DIR}, ${DISP_NAME})
RAY_SRC		=	$(addprefix ${RAY_DIR}, ${RAY_NAME})

SRCS_NAME 	=	main.c ${PARS_SRC} ${PRINT_SRC} ${DISP_SRC} ${RAY_SRC}

SRCS		=	$(addprefix ${SRC_DIR}, ${SRCS_NAME})
OBJS		=	${SRCS:%.c=$(BUILD_DIR)/%.o}

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
RES_ALERT	:=	"\033[31mScreen res is lower than 1920x1080. You might not enjoy the game, please change hardware.\033[m"
RES_OK		:=	"\033[32mScreen display set to 1920x1080. Launch game with: \033[4\;36\;1m\.\/cub3D \<map\.cub\>\033[m"

###		OPTIONS		##
CFLAGS		=	-Wall -Wextra -Werror -g3
LDFLAGS		=	${LIBFT} ${MLX} ${XWIN}
REDIRVOID	=	>/dev/null 2>&1

###		RULES		###
$(BUILD_DIR)/%.o: %.c ${HEADER}
			@mkdir -p $(dir $@)
			@echo -e "\033[32m\c"
			${CC} ${CFLAGS} -c $< -o $@
			@echo -e "\033[0m\c"

all:		${NAME} screen_res_alert

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

${MLX}:
			@echo -ne "\033[33mmlx: compilation ...\033[0m"
			@make --no-print-directory -C ./libs/mlx >/dev/null 2>&1
			@echo -e "\r\033[33mmlx: compiled!            \033[0m"

clean:
			@make --no-print-directory clean -C ./libs/libft/ >/dev/null 2>&1
			@make --no-print-directory clean -C ./libs/mlx/ >/dev/null 2>&1
			@rm -rf ${BUILD_DIR}
			@echo -e "\033[32m${NAME} obj cleaned"

fclean:		clean
			@make --no-print-directory fclean -C ./libs/libft/
			@rm -rf ${NAME}
			@echo -e "\033[32m${NAME} fcleaned\033[m"

re:			fclean all

.PHONY:		all clean re screen_res_alert
