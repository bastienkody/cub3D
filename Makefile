###		DIRECTORY		###
HEADER		=	./inc/cub3D.h
BUILD_DIR	=	./build
SRC_DIR 	=	./src/
PARS_DIR	=	parsing/
PRINT_DIR	=	printer/

###		SOURCE FILES		###
PARS_NAME	=	parser.c
PRINT_NAME	=	error.c

PARS_SRC	=	$(addprefix ${PARS_DIR}, ${PARS_NAME})
PRINT_SRC	=	$(addprefix ${PRINT_DIR}, ${PRINT_NAME})

SRCS_NAME 	=	main.c ${PARS_SRC} ${PRINT_SRC}

SRCS		=	$(addprefix ${SRC_DIR}, ${SRCS_NAME})
OBJS		=	${SRCS:%.c=$(BUILD_DIR)/%.o}

###		DEFINITIONS		###
NAME		=	cub3Dd
LIBFT		=	./libs/libft/libft.a
MLX			=	./libs/mlx/libmlx_Linux.a
CC			=	cc

###		OPTIONS		##
CFLAGS		=	-Wall -Wextra -Werror -g3
LDFLAGS		=	${LIBFT} ${MLX}
REDIRVOID	=	>/dev/null 2>&1

###		RULES		###
$(BUILD_DIR)/%.o: %.c
			@mkdir -p $(dir $@)
			@echo "\033[32m\c"
			${CC} ${CFLAGS} -c $< -o $@
			@echo "\033[0m\c"

all:		${NAME}

${NAME}:	${LIBFT} ${MLX} ${OBJS} ${HEADER} 
			@echo "\033[32m\c"
			${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "Link complete for exec --> \033[4;36;1m${NAME}\033[0m"

${LIBFT}:
			@echo -n "\033[33mlibft compilation ...\033[0m"
			@make --no-print-directory -C ./libs/libft/ >/dev/null 2>&1
			@echo "\033[33mlibft compiled\033[0m"

${MLX}:
			@echo -n "\033[33mmlx compilation ...\033[0m"
			@make --no-print-directory -C ./libs/mlx >/dev/null 2>&1
			@echo "\033[33mmlx compiled\033[0m"

clean:
			@make --no-print-directory clean -C ./libs/libft/ >/dev/null 2>&1
			@make --no-print-directory clean -C ./libs/mlx/ >/dev/null 2>&1
			@rm -rf ${BUILD_DIR}
			@echo "\033[32m${NAME} obj cleaned"

fclean:		clean
			@make --no-print-directory fclean -C ./libs/libft/
			@rm -rf ${NAME}
			@echo "\033[32m${NAME} fcleaned\033[m"

re:			fclean all

.PHONY:		all clean re
