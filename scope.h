#ifndef SCOPE_H
# define SCOPE_H
# include "./libft/libft.h"

typedef	struct	s_scene
{
	t_obj		*obj;
	char		*mtl;
}				t_scene;

typedef struct	s_obj
{
	t_poly		*all_face;
	t_val		*v_value;
	t_val		*vn_value;
	t_val		*vt_value;
}				t_obj

typedef struct	s_vtemp
{
	double		x;
	double		y;
	double		z;
}				t_vtemp;


typedef struct	s_val
{
	t_vtemp		*value;
}				t_val

typedef struct	s_poly
{
	t_vertex	*face;
}				t_poly;

typedef struct	s_vertex
{
	int			v_index;
	int			vn_index;
	int			vt_index;
}				t_vertex;

//main.c
void			ft_usage(void);

//read.c
char			*ft_strfuse(char *str1, char *str2);
char			*read_file(char *file);

#endif
