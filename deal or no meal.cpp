#include<lvp\gui_top.h>
#include<lvp\string.h>
#include<lvp\vector.h>
#include<lvp\matrix.h>
#include<lvp\random.h>
#include<time.h>
#include<sstream>
#include<string>

void wait(double sec)
{
	double wt = clock() + (sec * 1000);
	while (clock() < wt)
	{
	}
}

String stringify(int num)
{
	std::stringstream comp; //creates a new string stream
	std::string temp;	//creates a cstring to s
	String rv = "";
	comp << num;
	temp = comp.str();
	for (int i = 0; i < temp.size(); i++)
	{
		rv += temp[i];
	}
	return rv;
}

String formatcash(int mon)
{
	String rmon = stringify(mon);
	String rv = "";
	for (int i = rmon.length() - 1; i >= 0; i--)
	{
		rv += rmon[i];
	}
	return rv;
}

class Suitcase 
{
	private:
		int boxnum, monval, xt, yt;
		String model;
		bool open;
	public:
		Suitcase();
		Suitcase(int box, int monval, int xpos, int ypos, String model);
		bool isHit(int x, int y);
		void paint();
		void openbox();
		int boxacc();
		bool opacc();
};

Suitcase::Suitcase()
:boxnum(0), monval(0), xt(0), yt(0), model(""), open(false)
{
}

Suitcase::Suitcase(int boxnum_, int monval_, int xt_, int yt_, String model_)
:boxnum(boxnum_), monval(monval_), xt(xt_), yt(yt_), model(model_), open(false)
{
}

bool Suitcase::isHit(int x, int y)
{
	if (x >= xt && x <= xt + 150 && y >= yt && y <= yt + 100)
	{
		return true;
	}
	if (x >= xt + 50 && y >= yt - 30 && x <= xt + 60 && y <= yt)
	{
		return true;
	}
	if (x >= xt + 50 && y >= yt - 30 && x <= xt + 100 && y <= yt - 20)
	{
		return true;
	}
	if (x <= xt + 100 && y >= yt - 30 && x >= xt + 90 && y <= yt)
	{
		return true;
	}
	return false;
}

void Suitcase::paint()
{
	SetFillColor(RGB(96, 96, 96));
	FilledRectangle(xt, yt, xt + 150, yt + 100); //body
	SetFillColor(RGB(102, 51, 0));
	FilledRectangle(xt + 50, yt - 30, xt + 60, yt); //handle left
	FilledRectangle(xt + 50, yt - 30, xt + 100, yt - 20); //handle top
	FilledRectangle(xt + 100, yt - 30, xt + 90, yt); //handle right
	gotoxy(xt + 75, yt + 50);
	SetTextSize(2);
	DrawCenteredText(boxnum); //box number
}

void Suitcase::openbox()
{
	paint();
	for (int i = 0; i < 100; i++)
	{
		SetFillColor(RGB(96, 96, 96));
		FilledRectangle(xt, yt, xt + 150, yt + 100);
		SetFillColor(RGB(102, 51, 0));
		FilledRectangle(xt + 50, yt - 30, xt + 60, yt);
		FilledRectangle(xt + 50, yt - 30, xt + 100, yt - 20);
		FilledRectangle(xt + 100, yt - 30, xt + 90, yt);
		SetFillColor(RGB(0, 0, 0));
		FilledRectangle(xt, yt, xt + 150, yt + i);
		if (i >= 50)
		{
			gotoxy(xt + 75, yt + 50);
			SetTextSize(2);
			DrawCenteredText(/*formatcash*/(monval));
		}
		else
		{
			gotoxy(xt + 75, yt + 50);
			SetTextSize(2);
			DrawCenteredText(boxnum);
		}
		wait(0.01);
	}
	open = true;
}

int Suitcase::boxacc()
{
	return boxnum;
}

bool Suitcase::opacc()
{
	return open;
}	

class Panel
{
	private:
		int value, xp, yp;
		bool lit;
	public:
		Panel();
		Panel(int value, int xp, int yp);
		void unlight();
		void draw();
		int valacc();
};

Panel::Panel()
:value(0), xp(0), yp(0), lit(false)
{
}

Panel::Panel(int value_, int xp_, int yp_)
:value(value_), xp(xp_), yp(yp_), lit(true)
{
}

void Panel::unlight()
{
	lit = false;
}

void Panel::draw()
{
	if (lit)
	{
		SetColor(RGB(0, 0, 0));
		SetFillColor(YELLOW);
		FilledRectangle(xp, yp, xp + 100, yp + 20);
		gotoxy((xp + 100) / 2, yp + 15);
		SetTextSize(2);
		DrawCenteredText(/*formatcash*/(value));
	}
	else
	{
		SetColor(RGB(0, 0, 0));
		Rectangle(xp, yp, xp + 100, yp + 20);
		gotoxy((xp + 100) / 2, yp + 15);
		SetTextSize(2);
		DrawCenteredText(/*formatcash*/(value));
	}
}

int Panel::valacc()
{
	return value;
}

class gameplay
{
	private:
		vector <Suitcase> cases;
		vector <Panel> panels;
		int x, y;
	public:
		gameplay();
		gameplay(int x, int y);
		void play();
		void back();
};

gameplay::gameplay()
:cases(0), panels(0), x(0), y(0)
{	
}

gameplay::gameplay(int x_, int y_)
:panels(26), x(x_), y(y_)
{
	vector <String> models(26);
	vector <double> monvals(26);
	vector <int> relvals(26);
	vector <Suitcase> tempcase(26);
	randomize();
	models[0] = "Ann McCabe";
	models[1] = "Lisa McCabe";
	models[2] = "Maya McCabe";
	models[3] = "Legs McCabe";
	models[4] = "Alanna McCabe";
	models[5] = "Colleen McCabe";
	models[6] = "Caoimhe McCabe";
	models[7] = "Eva McCabe";
	models[8] = "Ciaran McCabe";
	models[9] = "Brianna McCabe";
	models[10] = "Bridget McCabe";
	models[11] = "Caitlin McCabe";
	models[12] = "Naimh McCabe";
	models[13] = "Cara McCabe";
	models[14] = "Fianna McCabe";
	models[15] = "Maggie McCabe";
	models[16] = "Darcy McCabe";
	models[17] = "Deirdre McCabe";
	models[18] = "Eitna McCabe";
	models[19] = "Enda McCabe";
	models[20] = "Claire McCabe";
	models[21] = "Fiona McCabe";
	models[22] = "Gael McCabe";
	models[23] = "Iona McCabe";
	models[24] = "Mona McCabe";
	models[25] = "Nessie McCabe";
	monvals[0] = .01;
	monvals[1] = 1;
	monvals[2] = 5;
	monvals[3] = 10;
	monvals[4] = 25;
	monvals[5] = 50;
	monvals[6] = 75;
	monvals[7] = 100;
	monvals[8] = 200;
	monvals[9] = 300;
	monvals[10] = 400;
	monvals[11] = 500;
	monvals[12] = 750;
	monvals[13] = 1000;
	monvals[14] = 5000;
	monvals[15] = 10000;
	monvals[16] = 25000;
	monvals[17] = 50000;
	monvals[18] = 75000;
	monvals[19] = 100000;
	monvals[20] = 200000;
	monvals[21] = 300000;
	monvals[22] = 400000;
	monvals[23] = 500000;
	monvals[24] = 750000;
	monvals[25] = 1000000;

	int panelX = 50;
	int panelY = 60;

	for (int i = 0; i < panels.length(); i++)
	{
		panels[i] = Panel(monvals[i], panelX, panelY);
		panelY+=27;
	}
	int r;

	for(int i = 0; i < 26; i++)
	{
		do
		{
			r = random(26);
			if (monvals[r] != -1)
			{
				relvals[i] = monvals[r];
				monvals[r] = -1;
			}
		}
		while(monvals[r] != -1);
	}
	
	int x__ = 400;
	int y__ = 60;
	for (int u = 0; u < tempcase.length(); u++)
	{
		tempcase[u] = Suitcase(u + 1, relvals[u], x__, y__, models[u]);
		x__+=200;
		if (x__>1250)
		{
			x__=400;
			y__+=130;
		}
	}
	cases = tempcase;
}

void gameplay::back()
{
	SetFillColor(YELLOW);
	FilledRectangle(0,0,GetMaxX(),GetMaxY());
	SetFillColor(ORANGE);
	FilledRectangle(0,0,300,GetMaxY());//LEFT PANEL
	SetFillColor(WHITE);
	FilledRectangle(600,GetMaxY()-200,GetMaxX()-100,GetMaxY());//BOTTOM PANEL
}

void gameplay::play()
{
	back();
	for (int i = 0; i < cases.length(); i++)
	{
		if (!cases[i].opacc())
		{
			cases[i].paint();
		}
		panels[i].draw();
	}
	for (int k = 0; k < cases.length(); k++)
	{
		if (cases[k].isHit(x,y))
		{
			MessageBox("","meme");
			panels[k].unlight();
			cases[k].openbox();
			panels[k].draw();
		}
	}
}

class GuiClass
{
	public:
		GuiClass();
		void GuiMouseClick(int x, int y); // Action if mouse click
		void GuiPaint(); // Repaint the entire window
		String Title(); 
	private:
		gameplay game;
		int x, y;
};

GuiClass::GuiClass()
:game(x ,y)
{
}

String GuiClass::Title()
{
	return "Deal or No Deal";
}

void GuiClass::GuiMouseClick(int x_, int y_)
{
	x = x_, y = y_;
}

void GuiClass::GuiPaint()
{
	game.play();
}

#include <lvp\gui_bot.h>