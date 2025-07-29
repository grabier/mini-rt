#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>



#define MAX_W 1600
#define MAX_H 1200
#define MAX_D 100.0
#define PI 3.14159

typedef struct s_vec {
	double x, y, z;
} t_vec;

typedef struct s_ray {
	t_vec or;
	t_vec dir;
} t_ray;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;


typedef struct s_cam {
	t_vec origin;
	t_vec forward;
	t_vec up;
	t_vec right;
	t_vec hor;
	t_vec ver;
	t_vec ll;
} t_cam;

typedef struct s_parse {
	t_cam		*cam;
	mlx_t		*data;
	mlx_image_t	*img;
} t_parse;

typedef struct collision {
	double depth;
} t_collision;


double rocket(t_vec p);


// -------- Vector utils --------

t_vec add(t_vec a, t_vec b) { return (t_vec){a.x + b.x, a.y + b.y, a.z + b.z}; }
t_vec sub(t_vec a, t_vec b) { return (t_vec){a.x - b.x, a.y - b.y, a.z - b.z}; }
t_vec scale(double k, t_vec v) { return (t_vec){k * v.x, k * v.y, k * v.z}; }
double dot(t_vec a, t_vec b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
t_vec cross(t_vec a, t_vec b) {
	return (t_vec){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x};
}
double vlen(t_vec v) { return sqrt(dot(v, v)); }
t_vec norm(t_vec v) {
	double len = vlen(v);
	if (len == 0) return v;
	return scale(1.0 / len, v);
}


t_collision map(t_vec p)
{
	t_collision c;
	c.depth = rocket(p);
	return (c);
}
double calcSoftshadow(t_vec ro, t_vec rd, double mint, double tmax)
{
    double res = 1.0;
    double t = mint;
    for (int i = 0; i < 24; i++)
    {
        t_collision col = map(add(ro, scale(t, rd)));
        double h = col.depth;
        double s = fmax(0.0, fmin(1.0, 8.0 * h / t));
        res = fmin(res, s);
        t += fmax(0.01, fmin(0.2, h));
        if (res < 0.004 || t > tmax)
            break;
    }
    res = fmax(0.0, fmin(1.0, res));
    return res * res * (3.0 - 2.0 * res);
}


t_vec calcNormal(t_vec pos)
{
    t_vec n = {0.0, 0.0, 0.0};
    for (int i = 0; i < 4; i++)
    {
        int xi = ((i + 3) >> 1) & 1;
        int yi = (i >> 1) & 1;
        int zi = i & 1;
        t_vec e = scale(0.5773, (t_vec){2.0 * xi - 1.0, 2.0 * yi - 1.0, 2.0 * zi - 1.0});
        t_collision col = map(add(pos, scale(0.0005, e)));
        n = add(n, scale(col.depth, e));
    }
    return norm(n);
}


double calcAO(t_vec pos, t_vec nor)
{
    double occ = 0.0;
    double sca = 1.0;
    for (int i = 0; i < 5; i++)
    {
        double h = 0.01 + 0.12 * (double)i / 4.0;
        t_collision col = map(add(pos, scale(h, nor)));
        double d = col.depth;
        occ += (h - d) * sca;
        sca *= 0.95;
        if (occ > 0.35)
            break;
    }
    double ao = 1.0 - 3.0 * occ;
    if (ao < 0.0) ao = 0.0;
    if (ao > 1.0) ao = 1.0;
    return ao * (0.5 + 0.5 * nor.y);
}


// -------- SDF (signed distance function) --------

double sphere(t_vec p) {
	return vlen(p) - 3.0; // esfera centrada en (0,0,0) radio 3
}

double rocket(t_vec p) {
	double x = p.x, y = p.y, z = p.z;

	double f = pow(x, 2.0) * pow(y, 2.0)
		+ 0.5 * pow(x, 2.0) * pow(z, 2.0)
		- 1.0 * pow(x, 2.0)
		+ pow(x, 4.0)
		+ pow(y, 2.0) * pow(z, 2.0)
		- 1.0 * pow(y, 3.0)
		+ 0.5 * pow(y, 4.0)
		- 1.0 * pow(z, 2.0)
		+ pow(z, 4.0)
		+ 1.0 / 3.0;

	t_vec grad;
	grad.x = 2.0 * x * pow(y, 2.0)
		+ x * pow(z, 2.0)
		- 2.0 * x
		+ 4.0 * pow(x, 3.0);

	grad.y = 2.0 * pow(x, 2.0) * y
		+ 2.0 * y * pow(z, 2.0)
		- 3.0 * pow(y, 2.0)
		+ 2.0 * pow(y, 3.0);

	grad.z = pow(x, 2.0) * z
		+ 2.0 * pow(y, 2.0) * z
		- 2.0 * z
		+ 4.0 * pow(z, 3.0);

	return f / vlen(grad);
}


// -------- Raycasting (raymarching) --------

t_collision raycast(t_ray ray) {
	t_collision res;
	res.depth = -1;

	double t = 0.0;
	for (int i = 0; i < 128 && t < MAX_D; i++) {
		t_vec p = add(ray.or, scale(t, ray.dir));
		double h = fmax(rocket(p), sphere(p));
		if (fabs(h) < 0.001) {
			res.depth = t;
			break;
		}
		t += h;
	}
	return res;
}

// -------- Cálculo del rayo --------

t_ray ft_calc_ray(int i, int j, t_parse *pr) {
	double u = (i + 0.5) / MAX_W;
	double v = (j + 0.5) / MAX_H;

	t_vec pixel = add(add(pr->cam->ll, scale(u, pr->cam->hor)), scale(v, pr->cam->ver));
	t_vec dir = sub(pixel, pr->cam->origin);

	t_ray ray = {pr->cam->origin, norm(dir)};
	return ray;
}

// -------- Render de píxel --------

t_vec estimate_normal(t_vec pos) {
	const double eps = 0.0005;

	double dx = rocket((t_vec){pos.x + eps, pos.y, pos.z}) - rocket((t_vec){pos.x - eps, pos.y, pos.z});
	double dy = rocket((t_vec){pos.x, pos.y + eps, pos.z}) - rocket((t_vec){pos.x, pos.y - eps, pos.z});
	double dz = rocket((t_vec){pos.x, pos.y, pos.z + eps}) - rocket((t_vec){pos.x, pos.y, pos.z - eps});

	return norm((t_vec){dx, dy, dz});
}



/* uint32_t renderr(t_parse *pr, int width, int height) {
	t_ray ray = ft_calc_ray(width, height, pr);
	t_collision col = raycast(ray);

	if (col.depth != -1)
		return 0x00FF00FF; // verde
	return 0xFF0000FF; // rojo (fondo)
} */

uint32_t renderr(t_parse *pr, int width, int height) {
	t_ray ray = ft_calc_ray(width, height, pr);
	t_collision col = raycast(ray);

	if (col.depth != -1) {
		t_vec p = add(ray.or, scale(col.depth, ray.dir));
		t_vec n = estimate_normal(p);
		// Normal mapeada a color (de [-1,1] a [0,255])
		t_color color = {
			(unsigned char)((n.x * 0.5 + 0.5) * 130),
			(unsigned char)((n.y * 0.5 + 0.5) * 255),
			(unsigned char)((n.z * 0.5 + 0.5) * 255)
		};
		return (0xFF << 24 | color.r << 16 | color.g << 8 | color.b);
	}
	return 0xFF000000; // negro fondo
}



// -------- Bucle de render --------

void ft_render_loop(t_parse *pr) {
	for (int j = 0; j < MAX_H; j++) {
		for (int i = 0; i < MAX_W; i++) {
			uint32_t color = renderr(pr, i, j);
			mlx_put_pixel(pr->img, i, j, color);
		}
	}
	mlx_image_to_window(pr->data, pr->img, 0, 0);
	mlx_loop(pr->data);
}

// -------- Inicialización de cámara --------

void init_camera(t_cam *cam) {
	cam->origin = (t_vec){0, 0, -10};
	cam->forward = norm((t_vec){0, 0, 1});

	t_vec world_up = {0, 1, 0};
	cam->right = norm(cross(world_up, cam->forward));
	cam->up = cross(cam->forward, cam->right);

	double fov = 90.0;
	double viewport_height = 2.0 * tan((fov * PI / 180.0) / 2.0);
	double viewport_width = viewport_height * ((double)MAX_W / (double)MAX_H);

	cam->hor = scale(viewport_width, cam->right);
	cam->ver = scale(viewport_height, cam->up);

	t_vec half_hor = scale(0.5, cam->hor);
	t_vec half_ver = scale(0.5, cam->ver);
	cam->ll = sub(sub(add(cam->origin, cam->forward), half_hor), half_ver);
}

// -------- Parsing fake (simula parseo) --------

t_parse *ft_parsingg(int argc, char **argv) {
	(void)argc;
	(void)argv;

	t_parse *pr = malloc(sizeof(t_parse));
	pr->cam = malloc(sizeof(t_cam));
	init_camera(pr->cam);

	pr->data = mlx_init(MAX_W, MAX_H, "Raymarch Sphere", false);
	if (!pr->data)
		return NULL;

	pr->img = mlx_new_image(pr->data, MAX_W, MAX_H);
	if (!pr->img)
		return NULL;

	return pr;
}

// -------- MAIN --------

int main(int argc, char **argv) {
	t_parse *program = ft_parsingg(argc, argv);
	if (!program)
		return 1;

	ft_render_loop(program);
	return 0;
}