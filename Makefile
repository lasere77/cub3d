CC=cc
NAME = cub3D
SRCS_DIR = srcs/
SOURCES =	cub3d.c		\

SOURCES	:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

DEPS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.d)

CFLAGS = -MP -MMD -Wall -Werror -Wextra -g
INCLUDE = -I includes/ -I libft/includes/ -I MacroLibX/includes/

LIBS = libft/libft.a MacroLibX/libmlx.so

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -j --no-print-directory -C libft/
	$(MAKE) -j --no-print-directory -C MacroLibX/
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDE) -lSDL2 -lm $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

gdb: $(NAME)
	gdb -tui $(NAME)

clean: 
	$(MAKE) clean --no-print-directory -C libft/
	$(MAKE) clean --no-print-directory -C MacroLibX/
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean --no-print-directory -C libft/
	$(MAKE) fclean --no-print-directory -C MacroLibX/
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re gdb

-include $(DEPS)