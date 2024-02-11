#include <so_long.h>

#define WIDTH 1280
#define HEIGHT 1024

#define	CHAR_SIZE 256

#define TILE_SIZE 384

#define BPP sizeof(int32_t)

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

t_character	*load_character(mlx_t *mlx)
{
	t_character		*joey;
	mlx_texture_t	*texture;
	int				i;
	char			*path_start;
	char			*path;
	char			*nr;

	joey = malloc(sizeof(t_character));
	joey->idle = malloc(sizeof(mlx_image_t *) * 6);
	joey->idle_frame = malloc(sizeof(int) * 6);
	joey->accum = 0;
	joey->frame_speed = 100;
	i = 0;
	while (i < 6)
	{	
		nr = ft_itoa(i);
		path_start = ft_strjoin("./assets/idle_", nr);
		path = ft_strjoin(path_start, ".png");
		texture = mlx_load_png(path);
		joey->idle[i] = mlx_texture_to_image(mlx, texture);
		joey->idle_frame[i] = mlx_image_to_window(mlx, joey->idle[i], 0, 0);
		joey->idle[i]->instances[joey->idle_frame[i]].enabled = false;
		mlx_resize_image(joey->idle[i], CHAR_SIZE, CHAR_SIZE);
		free(path);
		free(path_start);
		mlx_delete_texture(texture);
		i++;
	}
	joey->mlx = mlx;
	return (joey);
}

int update_animation(t_character * a) {
  if (a) 
  {
    a->accum += a->mlx->delta_time * 1000;
    if (a->accum > a->frame_speed)
	{
      a->accum -= a->frame_speed;
	  return (1);
    }
  }
  return (0);
}

void	character_idle_animation(void *character)
{
	static int		i = 0;
	t_character *joey;
	static int		fps;

	joey = character;
	fps = 1000 * joey->mlx->delta_time;
 	printf("\e[1;1H\e[2Jfps [%d]\n", fps);
	
	if (update_animation(joey))
	{
		joey->idle[i]->instances[joey->idle_frame[i]].enabled = false;
		i++;
		if (i == 6)
			i = 0;
		joey->idle[i]->instances[joey->idle_frame[i]].enabled = true;
	}

}

int32_t	main(void)
{
	mlx_t			*mlx;
	t_character		*joey;
	mlx_image_t		*background;
	// Start mlx
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	//add white backgroud
	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!background)
		error();
	mlx_image_to_window(mlx, background, 0, 0);
	ft_memset(background->pixels, 0xFFFFFFFF, WIDTH * HEIGHT * BPP);

	joey = load_character(mlx);
	mlx_loop_hook(mlx, character_idle_animation, joey);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}