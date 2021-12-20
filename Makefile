NAME = uls

INC = inc/uls.h

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

LIBMX = libmx/libmx.a

all: 
	@make -C libmx
	@mkdir obj
	@clang $(FLAGS) -c src/*.c
	@mv *.o obj/
	@clang $(FLAGS) obj/*.o $(LIBMX) -o $(NAME)

install: all
	@cp $(LIBMX) .

uninstall:
	@rm -rf ./libmx.a

clean: uninstall
	@rm -rf $(NAME)
	@rm -rf ./obj
	@make uninstall -C libmx

reinstall: clean install
