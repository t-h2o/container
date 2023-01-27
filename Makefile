#	Compilation setting

NAME	=	program

CC		=	g++
DB		=	lldb

CFLAGS	=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g
CFLAGS	+=	-Wfatal-errors

OFLAGS	=	-fsanitize=address
OFLAGS	+=	/usr/lib/libgtest.a


#	Sources

SRCD	=	srcs

SRCS	=	$(SRCD)/main.cpp
SRCS	+=	$(SRCD)/color.cpp
SRCS	+=	$(SRCD)/Awesome.cpp

SRCS	+=	$(SRCD)/test_vector.cpp
SRCS	+=	$(SRCD)/test_subject.cpp
SRCS	+=	$(SRCD)/test_pair.cpp
SRCS	+=	$(SRCD)/test_map.cpp


#	Headers

INCD	=	headers

INCS	=	$(INCD)/color.hpp
INCS	+=	$(INCD)/Awesome.hpp

INCS	+=	$(INCD)/Iterator.hpp
INCS	+=	$(INCD)/Map.hpp
INCS	+=	$(INCD)/Vector.hpp

INCS	+=	$(INCD)/test.hpp


#	Templates

TMPD	=	templates

TMPS	=	$(TMPD)/IteratorVector.cpp
TMPS	+=	$(TMPD)/Map.cpp
TMPS	+=	$(TMPD)/Pair.cpp
TMPS	+=	$(TMPD)/Vector.cpp


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
