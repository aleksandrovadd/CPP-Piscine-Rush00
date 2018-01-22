CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -O3
CXXXFLAGS = -Wall -Wextra -Werror -O3 -lncurses
NAME = ft_retro

SRC = main.cpp Player.cpp Enemy.cpp Bullet.cpp GameObject.cpp GameCycle.cpp Background.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXXFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
