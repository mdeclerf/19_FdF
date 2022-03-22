#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 1

# define KEY_ESC 53

# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124

# define KEY_ISO 34
# define KEY_PAR 35

# define KEY_H_PLUS 4
# define KEY_H_MIN 11

# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6

# define W_HEI	1080
# define W_WID	1920

/*
** b_p_p -> bit per pixel, ll -> line lenght, e ->endian
*/
typedef struct s_window {
	void	*mlx;
	void	*win;
	int		start_x;
	int		start_y;
	int		ampli;
	int		iso;
	int		parallel;
	int		height;
	int		length;
	int		len;
	int		height_div;
	int		rot_x;
	int		rot_y;
	int		rot_z;
	void	*img;
	char	*addr;
	int		b_p_p;
	int		ll;
	int		e;
	int		**array;
	char	**argv;

}				t_window;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
}			t_point;

typedef struct s_coord {
	t_point	start;
	t_point	end;
}			t_coord;

typedef struct s_color {
	int	R;
	int	G;
	int	B;
}			t_color;

typedef struct s_grad {
	t_color	A;
	t_color	B;
}			t_grad;

typedef struct s_bresen {
	t_point	delta;
	t_point	current;
	t_point	sign;
	int		err;
	int		e2;
}			t_bresen;

/*
** error_check.c
*/
int			check_args(int argc, char **argv);
int			check_map(char **argv, t_window window);

/*
** free_array.c
*/
void		free_array(t_window window, int **array);

/*
** ft_atoi.c
*/
int			ft_atoi(const char *str);

/*
** ft_split.c
*/
int			string_number(char const *s, char c);
int			str_len(char const *s, char c, int i);
char		**error_malloc(char **array, int string_count);
char		**copy(char const *s, char **array, char c, int string_number);
char		**ft_split(char const *s, char c);

/*
** get_next_line_utils.c
*/
int			ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_search(char *s);
char		*ft_free(char *string);
int			ft_check(char **line, int fd, char **saved);

/*
** get_next_line.c
*/
int			get_next_line(int fd, char **line);

/*
** parsing.c
*/
int			get_height(char **argv);
int			get_length(char **argv);
int			**allocate_array(t_window window);
char		**loop_fill_array(int fd, char **backup);
int			**fill_array(t_window window, int **array, char **argv);

/*
** keys.c
*/
int			close_x(void *param);
t_window	keys_init(t_window window, int **array);
int			keys_move_bis(int key, t_window *window);
int			keys_move(int key, t_window *window);

/*
** matrice_rotation.c
*/
t_point		rotation_x(t_point point, double angle);
t_point		rotation_y(t_point point, double angle);
t_point		rotation_z(t_point point, double angle);
t_point		iso(t_point point);
t_point		rotation_iso(t_point point, t_window window);

/*
** len_height.c
*/
int			len_def(t_window window);
int			len_def_bis(t_window window, int side);
int			height_div_categories(int max);
int			height_div(t_window window, int **array);

/*
** min_max.c
*/
int			get_max(t_window window, int **array);
int			get_min(t_window window, int **array);

/*
** gradient.c
*/
t_color		colorstruct_init(t_color co);
int			create_argb(char a, char r, char g, char b);
int			color_handling(t_point end, t_point start,
				t_bresen bresen, t_grad grad);
double		percent(int start, int end, int current);
int			get_default_color(t_window window, int z);
int			get_light(int start, int end, double percentage);
t_color		color_init(int current_z, t_window window, t_color storage);

/*
** pixel_segment.c
*/
void		my_mlx_pixel_put(t_window *window, int x, int y, int color);
t_bresen	segment_preparation(t_point startpoint, t_point endpoint);
void		segment(t_window *window, t_point startpoint, t_point endpoint,
				t_grad grad);
void		segment_mute(t_window *window, t_point startpoint,
				t_point endpoint, int color);

/*
** printing.c
*/
t_point		point_init(t_point point);
void		loop_1(t_window window, t_coord coord, int x, int y);
void		loop_2(t_window window, t_coord coord, int x, int y);
void		printing(t_window window);

/*
** printing_black.c
*/
void		loop_2_black(t_window window, t_coord coord, int x, int y);
void		loop_1_black(t_window window, t_coord coord, int x, int y);
void		printblack(t_window window);

/*
** menu.c
*/
void		display_menu(t_window window);

#endif
