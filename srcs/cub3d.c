#include "libft.h"
#include "ft_printf.h"
#include "mlx.h"

#define FPS_GOAL 60

int	main(void)
{
	mlx_set_fps_goal(NULL, FPS_GOAL);
	ft_printf("%d", ft_atoi("10"));
	return (0);
}
