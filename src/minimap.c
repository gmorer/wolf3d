#include "wolf3d.h"

static int	print_player(t_env *env, t_int_coord count)
{
	t_color color;
	if ((count.y * env->size.y / 200 + 1 ) == (int)env->pos.x)
		if ((count.x * env->size.x / 200 + 1 ) == (int)env->pos.y)
		{
			color = BLUE;
			color.a = 150;
			draw_pixel(env, env->minimap, count, &(BLUE));
		}
	return (1);
}

int	ft_minimap(t_env *env)
{
	t_int_coord count;
	t_color		color;

	count.x = 0;
	count.y = 0;
	while (count.y	< 200)
	{
		count.x = 0;
		while (count.x < 200)
		{
			if (env->map[count.y * env->size.y / 200 + 1][count.x * env->size.x / 200 + 1] == 1)
			{
				color = WHITE;
				color.a = 150;
				draw_pixel(env, env->minimap, count, &(color));
			}
			else
			{
				color = BLACK;
				color.a = 150;
				draw_pixel(env, env->minimap, count, &(color));
			}
			print_player(env, count);
			count.x++;
		}
		count.y++;
	}
	return (1);
}
