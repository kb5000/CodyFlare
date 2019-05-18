#include "animes.h"
#include "spline_interpolation.h"
void Linkline(double x1, double x2, double y1, double y2, Vector* buffer);

Pos draw_enemy1_2(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	double cs = cos(t), ss = sin(t), c4s = cos(4 * t), s4s = sin(4 * t);
	return new_pos(-4 * cs * s4s - ss * c4s + cs, -4 * ss * s4s + cs * c4s - ss);
}

Pos draw_enemy2_2(DrawFuncHolder* dfh)
{
	double t = dfh->tNow;
	double cs = cos(t), ss = sin(t), c3s = cos(3 * t), s3s = sin(3 * t), s5s = sin(5 * t), c5s = cos(5 * t);
	return new_pos(3 * s5s*c3s*cs + 5 * s3s*c5s*cs - s3s * s5s*ss,
					3 * s5s*c3s*ss + 5 * s3s*c5s*ss + cs * s3s*s5s);
}

void draw_bonus_enemy(Pos* pos) {
	//double H = GetWindowHeight(), W = GetWindowWidth();
	//double a = W / 4;//a,b为中心点坐标
	//double b = H / 2;

	hnew(DrawFuncHolder, dfh);
	*dfh = create_function_holder(draw_enemy1_2, *pos, new_pos(0.16, 0.16), 0.16, 0, 2 * PI, 0.1, -PI / 4, color_by_name("Black"), 1, 0);
	draw_function(dfh);
	free(dfh);
	//*t += 0;
}

void draw_infernal_enemy(Pos *pos)
{
	hnew(DrawFuncHolder, dfh);
	*dfh = create_function_holder(draw_enemy2_2, *pos, new_pos(0.16, 0.16), 0.3, 0, 2 * PI, 0.005, 0 , color_by_name("Black"), 1, 0);
	draw_function(dfh);
	free(dfh);
}

//desparated
//这个东西应该是可以转动的...但是做不得
void enemy1_drawer()
{
	//Vector lines = gen_empty_vector(RectObj);
	double x[6], y[6];
	double H = GetWindowHeight(), W = GetWindowWidth();
	double a = W / 4;//a,b为中心点坐标
	double b = H / 2;
	double e = H / 150.0;
	x[0] = a;y[0] = b;
	x[1] = x[0] + e;y[1] = y[0] + 4 * e;
	x[2] = x[0];y[2] = y[0] + 5 * e;
	x[3] = x[0] - e;y[3] = y[0] + 4 * e;
	Vector v;
	Pos temp;
	Spline* sp;
	int i = 0;
	for (;i < 6;i++)
	{
		v = gen_empty_vector(Pos);
		calls(v, push, (temp = new_pos(x[0], y[0]), &temp));
		calls(v, push, (temp = new_pos(x[1], y[1]), &temp));
		calls(v, push, (temp = new_pos(x[2], y[2]), &temp));
		calls(v, push, (temp = new_pos(x[3], y[3]), &temp));

		sp = create_spline(&v, NULL, 1);
		add_func_to_timer(draw_spline, sp, 1, 1, -1);
		int j = 0;
		for (;j < 4;j++)
		{
			double tx = (x[j] - a) * cos(PI / 3) - (y[j] - b) * sin(PI / 3) + a;
			double ty = (y[j] - b) * cos(PI / 3) + (x[j] - a) * sin(PI / 3) + b;
			x[j] = tx;
			y[j] = ty;
		}
	}

}

void draw_basic_enemy(Pos* position)
{
	double x[20], y[20];
	//double H = GetWindowHeight(), W = GetWindowWidth();
	//double a = W * 0.8;//a,b为中心点坐标
	//double b = H / 2;
	//double e = H / 60.0;
	double a = position->x, b = position->y, e = 0.07;
	x[0] = a;y[0] = b;
	x[1] = a;y[1] = b + e;
	x[2] = a - 0.5*e;y[2] = b;
	x[3] = x[2];y[3] = b+1.5*e;
	x[4] = a - 1.5*e;y[4] = b + 1.5*e;
	x[5] = (x[2] + x[4]) / 2.0;y[5] = (y[2] + y[4]) / 2.0;
	x[6] = a - 1.5*e;y[6] = b;
	x[7] = a - e;y[7] = b - 0.5*e;
	x[8] = (x[0] + x[7]) / 2.0;y[8] = (y[0] + y[7]) / 2.0;
	x[9] = a - 3 * e;y[9] = b + 0.75*e;
	x[10] = a - 3.75*e;y[10] = b;
	x[11] = a - 2 * e;y[11] = b - 1.5*e;
	x[12] = (x[11] + x[7]) / 2.0;y[12] = (y[11] + y[7]) / 2.0;
	x[13] = x[12] + 0.25*e;y[13] = b - 4 * e;
	x[14] = a;y[14] = b - 2.5 * e;
	x[15] = (x[14] + x[7]) / 2.0;y[15] = (y[14] + y[7]) / 2.0;

	//Vector v;Pos temp;Spline* sp;

	hnew(Vector, buf);
	*buf = gen_empty_vector(RectPos);
	for (int i = 0; i < 2; i++)
	{
		double tx[20], ty[20];
		int j = 0;
		if (i == 0)
			for (;j <= 15;j++)
				tx[j] = x[j], ty[j] = y[j];
		else
			for (j = 0;j <= 15;j++)
				tx[j] = 2 * a - x[j], ty[j] = y[j];

		Linkline(tx[1], tx[2], ty[1], ty[2], buf);
		Linkline(tx[2], tx[3], ty[2], ty[3], buf);
		Linkline(tx[3], tx[5], ty[3], ty[5], buf);
		Linkline(tx[2], tx[4], ty[2], ty[4], buf);
		Linkline(tx[4], tx[6], ty[4], ty[6], buf);
		Linkline(tx[8], tx[9], ty[8], ty[9], buf);
		Linkline(tx[9], tx[12], ty[9], ty[12], buf);
		Linkline(tx[10], tx[7], ty[10], ty[7], buf);
		Linkline(tx[10], tx[11], ty[10], ty[11], buf);
		Linkline(tx[11], tx[0], ty[11], ty[0], buf);
		Linkline(tx[12], tx[13], ty[12], ty[13], buf);
		Linkline(tx[13], tx[15], ty[13], ty[15], buf);
		Linkline(tx[14], tx[7], ty[14], ty[7], buf);


	}
	//add_func_to_timer(draw_plain_lines, buf, 1, 192389, -1);
	draw_plain_lines(buf);
	pcalls(buf, destroy);
	free(buf);
}

void draw_player_plane(Pos* position)
{
	double a = position->x, b = position->y;
	double x[15],y[15];
	//double a, b;
	//a = GetWindowWidth()/2;
	//b = GetWindowHeight()/2;

	double e = 0.05;
	x[0] = a, y[0] = b;
	x[1] = a;y[1] = b + 6 * e;
	x[2] = a + e;y[2] = b + 3 * e;
	x[3] = a + 2 * e;y[3] = b + 2 * e;
	x[4] = a + 2.5 * e;y[4] = b + 4.5 * e;
	x[5] = a + 2.5 * e;y[5] = b + 1.5 * e;
	x[6] = a + 4 * e;y[6] = b;
	x[7] = a + 2.7 * e;y[7] = b - 1.3 * e;
	x[8] = a + 2 * e;y[8] = b - e;
	x[9] = a + 2.2 * e;y[9] = b - 2 * e;
	x[10] = a;y[10] = b - e;
	int i = 2;
	Vector v;
	Pos temp;
	Spline* sp;
	int j = 0;
	for (;j < 2;j++)
	{
		for (i = 2;i <= 10;i++)
		{
			v = gen_empty_vector(Pos);
			calls(v, push, (temp = new_pos(x[i - 1], y[i - 1] - e*j*0.5), &temp));
			calls(v, push, (temp = new_pos(x[i], y[i] - e*j*0.5), &temp));

			sp = create_spline(&v, NULL, 1);
			//add_func_to_timer(draw_spline, sp, 1, 1, -1);
			draw_spline(sp);
			destroy_spline(sp);
			free(sp);
		}
		for (i = 2;i <= 10;i++)
		{
			v = gen_empty_vector(Pos);
			calls(v, push, (temp = new_pos(2 * a - x[i - 1], y[i - 1] - e * j*0.5), &temp));
			calls(v, push, (temp = new_pos(2 * a - x[i], y[i] - e * j*0.5), &temp));

			sp = create_spline(&v, NULL, 1);
			//add_func_to_timer(draw_spline, sp, 1, 1, -1);
			draw_spline(sp);
			destroy_spline(sp);
			free(sp);
		}
	}
	
}


void Linkline(double x1, double x2, double y1, double y2, Vector* buffer)
{
	RectPos rp = {{x1, y1}, {x2, y2}};
	pcalls(buffer, push, &rp);
	//MovePen(x1, y1);
	//DrawLine(x2, y2);
	//Vector v;
	//Pos temp;
	//Spline* sp;
	//v = gen_empty_vector(Pos);
	//calls(v, push, (temp = new_pos(x1, y1), &temp));
	//calls(v, push, (temp = new_pos(x2, y2), &temp));

	//sp = create_spline(&v, NULL, 1);
	//add_func_to_timer(draw_spline, sp, 1, 1, -1);
}


