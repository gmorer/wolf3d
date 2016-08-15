#include "wolf3d.h"

static int	print_player(t_env *env, t_int_coord count)
{
	if ((count.y * env->size.y / 200 + 1 ) == (int)env->pos.x)
		//if ((count.y * env->size.y / 200 + 1 ) - env->pos.y > 0)
			if ((count.x * env->size.x / 200 + 1 ) == (int)env->pos.y)
				//if ((count.x * env->size.x / 200 + 1 ) - env->pos.x > 0)
					draw_pixel(env, env->minimap, count, &(BLUE));
	return (1);
}

int	ft_minimap(t_env *env)
{
	t_int_coord count;

	count.x = 0;
	count.y = 0;
	while (count.y	< 200)
	{
		count.x = 0;
		while (count.x < 200)
		{
			if (env->map[count.y * env->size.y / 200 + 1][count.x * env->size.x / 200 + 1] == 1)
				draw_pixel(env, env->minimap, count, &(WHITE));
			else
				draw_pixel(env, env->minimap, count, &(BLACK));
			print_player(env, count);
			count.x++;
		}
		count.y++;
	}
	return (1);
}
