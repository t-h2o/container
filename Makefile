#	Compilation setting

NAME	=	program

CC		=	g++
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-Wfatal-errors
CFLAGS	+=	-std=c++98

OFLAGS	=	-fsanitize=address


#	Sources

SRCD	=	srcs

SRCS	+=	$(SRCD)/Awesome.cpp
SRCS	+=	$(SRCD)/color.cpp
SRCS	+=	$(SRCD)/main.cpp
SRCS	+=	$(SRCD)/test_algorithm.cpp
SRCS	+=	$(SRCD)/test_chain_list.cpp
SRCS	+=	$(SRCD)/test_map.cpp
SRCS	+=	$(SRCD)/test_pair.cpp
SRCS	+=	$(SRCD)/test_random_access_iterator.cpp
SRCS	+=	$(SRCD)/test_rev_random_access_iterator.cpp
SRCS	+=	$(SRCD)/test_stack.cpp
SRCS	+=	$(SRCD)/test_vector.cpp
SRCS	+=	$(SRCD)/to_string.cpp


#	Headers

INCD	=	headers

INCS	+=	$(INCD)/Awesome.hpp
INCS	+=	$(INCD)/algorithm.hpp
INCS	+=	$(INCD)/chain_list.hpp
INCS	+=	$(INCD)/color.hpp
INCS	+=	$(INCD)/Iterator.hpp
INCS	+=	$(INCD)/map.hpp
INCS	+=	$(INCD)/pair.hpp
INCS	+=	$(INCD)/random_access_iterator.hpp
INCS	+=	$(INCD)/rev_bidirectional.hpp
INCS	+=	$(INCD)/rev_random_access_iterator.hpp
INCS	+=	$(INCD)/Tdd.hpp
INCS	+=	$(INCD)/test.hpp
INCS	+=	$(INCD)/to_string.hpp
INCS	+=	$(INCD)/vector.hpp


#	Templates

TMPD	=	templates

TMPS	+=	$(TMPD)/chain_list.cpp
TMPS	+=	$(TMPD)/Color.cpp
TMPS	+=	$(TMPD)/map.cpp
TMPS	+=	$(TMPD)/Node.cpp
TMPS	+=	$(TMPD)/pair.cpp
TMPS	+=	$(TMPD)/random_access_iterator.cpp
TMPS	+=	$(TMPD)/RBTchecker.cpp
TMPS	+=	$(TMPD)/rev_bidirectional.cpp
TMPS	+=	$(TMPD)/rev_random_access_iterator.cpp
TMPS	+=	$(TMPD)/Tdd.cpp
TMPS	+=	$(TMPD)/vector.cpp


#	Objets

OBJD	=	objs
OBJS	=	$(addprefix $(OBJD)/, $(notdir $(SRCS:.cpp=.o)))

RM		=	rm -rf

vpath %.cpp $(SRCD):$(SRCD)/class


all : $(NAME)

$(NAME):	$(OBJS)
	@printf "$(YELLOW)Creating executable..$(DEFAULT)\n"
	@$(CC) $(OBJS) $(OFLAGS) -o $(NAME)
	@printf "$(GREEN)---> $(NAME) is ready$(DEFAULT)\n"

$(OBJD)/%.o : %.cpp | $(OBJD)
	@printf "$(YELLOW)Compiling $(DEFAULT)$<\n"
	@$(CC) $(CFLAGS) -I$(INCD) -o $@ -c $<

$(OBJD) :
	@mkdir -p $(OBJD)

clean:
	@$(RM) $(OBJD)
	@printf "$(RED)Removed $(CYAN)$(OBJD)$(DEFAULT)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(CYAN)$(NAME)$(DEFAULT)\n"

re:	fclean all


db: all
	$(DB) $(NAME)

format:
	@cat $(SRCS) $(INCS) $(TMPS) > /tmp/before
	@clang-format -i $(SRCS) $(INCS) $(TMPS)
	@cat $(SRCS) $(INCS) $(TMPS) > /tmp/after
	@diff -u --color=auto /tmp/before /tmp/after || true


diagram:
	asciidoctor -r asciidoctor-diagram assets/README.adoc -o assets/index.html

doc: diagram
	asciidoctor README.adoc -o index.html


.PHONY: all clean fclean libclean fullclean

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
