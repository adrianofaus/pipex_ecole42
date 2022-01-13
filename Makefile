NAME			:=	pipex

CC				:=	clang

RM				:=	rm -rf

CFLAGS			:=	-Wall -Wextra -Werror -g3

PATH_SRC		:=	./src/

PATH_UTILS		:=	./utils/
PATH_UTILS_BON	:= ./utils_bonus/

SRCS			:=	$(PATH_SRC)ft_memcpy.c $(PATH_SRC)ft_split.c $(PATH_SRC)ft_strchr.c\
					$(PATH_SRC)ft_strdup.c $(PATH_SRC)ft_strjoin.c $(PATH_SRC)ft_strlen.c\
					$(PATH_SRC)ft_strncmp.c $(PATH_SRC)ft_substr.c $(PATH_SRC)ft_putstr_fd.c\
					$(PATH_SRC)ft_calloc.c $(PATH_SRC)ft_bzero.c $(PATH_UTILS)commands.c\
					$(PATH_UTILS)errors.c $(PATH_UTILS)free_matrix.c $(PATH_UTILS)here_doc.c\
					$(PATH_UTILS)parse_cmd.c pipex.c

BON_SRC			:=	$(PATH_SRC)ft_memcpy.c $(PATH_SRC)ft_split.c $(PATH_SRC)ft_strchr.c\
					$(PATH_SRC)ft_strdup.c $(PATH_SRC)ft_strjoin.c $(PATH_SRC)ft_strlen.c\
					$(PATH_SRC)ft_strncmp.c $(PATH_SRC)ft_substr.c $(PATH_SRC)ft_putstr_fd.c\
					$(PATH_SRC)ft_calloc.c $(PATH_SRC)ft_bzero.c $(PATH_UTILS_BON)commands_bonus.c\
					$(PATH_UTILS_BON)errors_bonus.c $(PATH_UTILS_BON)free_matrix_bonus.c $(PATH_UTILS_BON)here_doc_bonus.c\
					$(PATH_UTILS_BON)parse_cmd_bonus.c pipex_bonus.c

OBJS			:=	${SRCS:.c=.o}
BON_OBJ			:=	${BON_SRC:.c=.o}

all:				${NAME}

${NAME}:			${OBJS}
						${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean:
					${RM} ${OBJS} ${BON_OBJ}

fclean:				clean
					${RM} ${NAME}

bonus:				${BON_OBJ}
						${CC} ${CFLAGS} ${BON_SRC} -o ${NAME}

re:					fclean all

rebonus:			fclean bonus

.PHONY:				all clean fclean re bonus rebonus