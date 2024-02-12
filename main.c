#include <so_long.h>

#define WIDTH 1280
#define HEIGHT 1024

#define	CHAR_SIZE 512

#define TILE_SIZE 384

#define BPP sizeof(int32_t)

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

mlx_image_t	*get_img(t_game *game, char *path, int i)
{
	char			*path_start;
	char			*nr;
	char			*full_path;
	mlx_texture_t	*texture;
	mlx_image_t		*new_frame;

	nr = ft_itoa(i);
	path_start = ft_strjoin(path, nr);
	if (!path_start)
		error();
	full_path = ft_strjoin(path_start, ".png");
	if (!full_path)
		error();
	texture = mlx_load_png(full_path);
	if (!texture)
		error();
	new_frame = mlx_texture_to_image(game->mlx, texture);
	if (!new_frame)
		error();
	free(path_start);
	free(full_path);
	free(nr);
	mlx_delete_texture(texture);
	return (new_frame);	
}

void	anim_to_window(mlx_t *mlx, t_list *frames)
{
	mlx_image_t	*frame;

	while (frames != NULL)
	{
		frame = (mlx_image_t *)frames->content;
		mlx_image_to_window(mlx, frame, 0, 0);
		frame->instances[0].enabled = false;
		frames = frames->next;
	}
}

t_anim	*load_animation(t_game *game, t_sprite sprite)
{
	t_anim			*anim;
	int				i;
	t_list			*new_frame;
	mlx_image_t		*new_img;

	anim = ft_calloc(1, sizeof(t_anim));
	if (!anim)
		error();
	anim->frame_speed = sprite.frame_speed;
	i = 0;
	while (i < sprite.frame_count)
	{	
		new_img = get_img(game, sprite.f_path, i);
		new_frame = ft_lstnew(new_img);
		if (!new_frame)
			error();
		if (!mlx_resize_image(new_img, sprite.size, sprite.size))
			error();
		ft_lstadd_back(&anim->frames, new_frame);
		i++;
	}
	anim_to_window(game->mlx, anim->frames);
	return (anim);
}

int update_animation(t_anim *a, double dt) {
  if (a) 
  {
    a->accum += dt * 1000;
    if (a->accum > a->frame_speed)
	{
		a->accum -= a->frame_speed;
		a->current_frame_num++;
		a->current_frame_num %= ft_lstsize(a->frames);
	  return (1);
    }
  }
  return (0);
}

void	character_idle_animation(void *my_game)
{
	static int				fps;
	mlx_image_t				*img;
	t_game					*game;

	game = (t_game *)my_game;
	fps = 1000 / game->mlx->delta_time;
 	printf("\e[1;1H\e[2Jfps [%d]\n", fps);
	img = (mlx_image_t *)ft_lstget(game->char_idle->frames, game->char_idle->current_frame_num)->content;
	img->instances[0].enabled = false;
	update_animation((t_anim *)game->char_idle, game->mlx->delta_time);
	img = (mlx_image_t *)ft_lstget(game->char_idle->frames, game->char_idle->current_frame_num)->content;
	img->instances[0].enabled = true;
}

t_game *init_game(mlx_t *mlx)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx;
	game->char_size = 256;
	return (game);
}

t_sprite	new_sprite(char *path, int f_cnt, int f_spd, uint32_t size)
{
	t_sprite	sprite;

	sprite.f_path = path;
	sprite.frame_count = f_cnt;
	sprite.frame_speed = f_spd;
	sprite.size = size;
	return (sprite);
}

void	get_animations(t_game *game)
{
	t_sprite	char_idle;

	char_idle = new_sprite("./assets/idle_", 6, 100, game->char_size);
	game->char_idle = load_animation(game, char_idle);
}

int32_t	main(void)
{
	mlx_t			*mlx;
	t_game			*game;
	mlx_image_t		*background;

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();
	game = init_game(mlx);	
	background = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!background)
		error();
	if (mlx_image_to_window(mlx, background, 0, 0) < 0)
		error();
	ft_memset(background->pixels, 0xFFFFFFFF, WIDTH * HEIGHT * BPP);
	get_animations(game);
	mlx_loop_hook(mlx, character_idle_animation, (void *)game);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}