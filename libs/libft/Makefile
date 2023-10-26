###			DIRECTORIES			###
BUILD_DIR			=	./.build
STD_DIR				=	./std/
GNL_DIR				=	./gnl/
PRINTF_DIR			=	./ft_fprintf/
ATOI_DIR			=	./atoi/
ARRAY_DIR			=	./array/
CHARRAY_DIR			=	./array/charray/
INT_ARRAY_DIR		=	./array/int_array/
STRJOIN_DIR			=	./strjoin/

###			SOURCFILES			###
HEADER				=	libft.h

STD_FILES			=	ft_atoi.c\
						ft_isalnum.c \
						ft_isprint.c \
						ft_memcpy.c \
						ft_putendl_fd.c \
						ft_strchr.c \
						ft_strlcpy.c \
						ft_strrchr.c \
						ft_toupper.c \
						ft_isalpha.c \
						ft_itoa.c \
						ft_memmove.c \
						ft_putnbr_fd.c \
						ft_strdup.c \
						ft_strlen.c \
						ft_strtrim.c \
						ft_bzero.c \
						ft_isascii.c \
						ft_memchr.c \
						ft_memset.c \
						ft_putstr_fd.c \
						ft_strjoin.c \
						ft_strncmp.c \
						ft_strcmp.c \
						ft_substr.c \
						ft_calloc.c \
						ft_isdigit.c \
						ft_memcmp.c \
						ft_putchar_fd.c \
						ft_split.c \
						ft_strlcat.c \
						ft_strnstr.c \
						ft_tolower.c \
						ft_strmapi.c \
						ft_striteri.c \
						ft_lstnew.c \
						ft_lstadd_front.c \
						ft_lstsize.c \
						ft_lstlast.c \
						ft_lstadd_back.c \
						ft_lstdelone.c \
						ft_lstclear.c \
						ft_lstiter.c \
						ft_lstmap.c\
						ft_realloc.c

GNL_FILES			=	get_next_line.c \
						get_next_line_utils.c

PRINTF_FILES		=	ft_fprintf.c \
						ft_fprintf_printer.c \
						ft_fprintf_hexa.c \
						ft_fprintf_utils.c

ATOI_FILES			=	ft_atoc_novf.c\
						ft_atouc_novf.c\
						ft_atoi_novf.c\
						ft_atoll_novf.c

ARRAY_FILES			=

CHARRAY_FILES		=	free_charray.c\
						ft_bzero_charray.c\
						dup_charray.c

INT_ARRAY_FILES		=	free_int_array.c

STRJOIN_FILES		=	strjoin.c\
						strjoin3.c\
						strjoin_char.c\
						superjoin.c


###			SOURCEFILES FULLNAMES			###
STD_SRCS			=	$(addprefix ${STD_DIR}, ${STD_FILES})
GNL_SRCS			=	$(addprefix ${GNL_DIR}, ${GNL_FILES})
PRINTF_SRCS			=	$(addprefix ${PRINTF_DIR}, ${PRINTF_FILES})
ATOI_SRCS			=	$(addprefix ${ATOI_DIR}, ${ATOI_FILES})
ARRAY_SRCS			=	$(addprefix ${ARRAY_DIR}, ${ARRAY_FILES})
CHARRAY_SRCS		=	$(addprefix ${CHARRAY_DIR}, ${CHARRAY_FILES})
INT_ARRAY_SRCS		=	$(addprefix ${INT_ARRAY_DIR}, ${INT_ARRAY_FILES})
STRJOIN_SRCS		=	$(addprefix ${STRJOIN_DIR}, ${STRJOIN_FILES})

SRCS				=	${STD_SRCS} ${GNL_SRCS} ${PRINTF_SRCS} ${ATOI_SRCS} ${ARRAY_SRCS}\
							${CHARRAY_SRCS} ${INT_ARRAY_SRCS} ${STRJOIN_SRCS}
OBJS				=	${SRCS:%.c=$(BUILD_DIR)/%.o}


###			VARIABLES			###
NAME 				=	libft.a
CC 					=	cc
CFLAGS 				=	-Wall -Wextra -Werror


###			RULES			###
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "\033[32m\c"
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "\033[0m\c"

all		:	${NAME}

${NAME}	:	${HEADER} ${OBJS}
		@ar rcs ${NAME} ${OBJS}

clean	:
		@rm -rf ${BUILD_DIR}
		@echo "\033[33mlibft obj cleaned\033[0m"

fclean	:	clean
		@rm -rf ${NAME}
		@echo "\033[33mlibft.a fcleaned\033[0m"

re		:	fclean all

.PHONY	:		all clean fclean re
