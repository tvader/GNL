gcc -Wall -Werror -Wextra -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c && ./a.out > res
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=7 get_next_line.c get_next_line_utils.c main.c && ./a.out >> res
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c && ./a.out >> res
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=1000000 get_next_line.c get_next_line_utils.c main.c && ./a.out >> res
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c && ./a.out >> res
