#include "../cub.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static int render_rect(t_img *img,  t_rect *rect)
{
	int	i;
	int j;
	
	i = rect->y;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
		{
			if (i == 0 || j == (rect->x + rect->width - 1) || i == (rect->y + rect->height - 1))
				my_mlx_pixel_put(img, j++, i, 000000); 
			my_mlx_pixel_put(img, j++, i, rect->color);
		}
		++i;
	}
	return (0);
}

int render_rect_player(t_img *img,  t_rect *rect)
{
	int	i;
	int j;
	
	i = rect->y;
    rect->height = TILE_SIZE / 4;
    rect->width = TILE_SIZE / 4;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
			my_mlx_pixel_put(img, j++, i, RED);
		++i;
	}
	return (0);
}


int render_line(t_img *img, double x, double y)
{
    int i;

    i = 0;
    while (i < TILE_SIZE)
    {
        my_mlx_pixel_put(img, x, y, RED);
        x++;
        y++;
        i++;
    }
    return (0);
}

int render_rotation_line(t_img *img, double x, double y, double angle)
{
    int i;

    i = 0;
    while (i < TILE_SIZE)
    {
        my_mlx_pixel_put(img, x, y, RED);
        x += cos(angle);
        y += sin(angle);
        i++;
    }
    return (0);
}

void render_player(t_img *img, t_parse *array)
{
	t_rect	rect;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 5;
	while (array->content[++k])
	{
		j = -1;
		while (array->content[k][++j])
		{
			rect.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			rect.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			if (array->content[k][j] == 'N')
				render_rect_player(img, &rect);
		}
		i++;
	}
}

void	render_map(t_img *img, t_parse *array)
{
	t_rect	rect;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 5;
	while (array->content[++k])
	{
		j = -1;
		while (array->content[k][++j])
		{
			rect.x = j * TILE_SIZE;
			rect.y = i * TILE_SIZE;
			rect.height = TILE_SIZE;
			rect.width = TILE_SIZE;
			if (array->content[k][j] == '1')
				rect.color = 14474440;
			else if (array->content[k][j] == '0')
				rect.color = 3289700;
			render_rect(img, &rect);
		}
		i++;
	}
}