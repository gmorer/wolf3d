#include "wolf3d.h"

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
			count.x++;
		}
		count.y++;
	}
	return (1);
}
