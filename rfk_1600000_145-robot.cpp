#include <conio.h>
#include <dos.h>
#include <iomanip.h>
#include <iostream.h>
#include <process.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
#define ROBOT 0
#define KITTEN 1
#define MESSAGES 145
//#define NUM_BOGUS 10
int NUM_BOGUS;

void instructions();
void draw_robot();
void draw_kitten();
void do_stuff();
struct object
{
	int x;
	int y;
	int color;
	char character;
};

object robot;
object kitten;
static char* messages[] =
{
	"\"I pity the fool who mistakes me for kitten!\", sez Mr. T.",
	"That's just an old tin can.",
	"It's an altar to the horse god.",
	"A box of dancing mechanical pencils. They dance! They sing!",
	"It's an old Duke Ellington record.",
	"A box of fumigation pellets.",
	"A digital clock. It's stuck at 2:17 PM.",
	"That's just a charred human corpse.",
	"I don't know what that is, but it's not kitten.",
	"An empty shopping bag. Paper or plastic?",
	"Could it be... a big ugly bowling trophy?",
	"A coat hanger hovers in thin air. Odd.",
	"Not kitten, just a packet of Kool-Aid(tm).",
	"A freshly-baked pumpkin pie.",
	"A lone, forgotten comma, sits here, sobbing.",
	"ONE HUNDRED THOUSAND CARPET FIBERS!!!!!",
	"It's Richard Nixon's nose!",
	"It's Lucy Ricardo. \"Aaaah, Ricky!\", she says.",
	"You stumble upon Bill Gates' stand-up act.",
	"Just an autographed copy of the Kama Sutra.",
	"It's the Will Rogers Highway. Who was Will Rogers, anyway?",
	"It's another robot, more advanced in design than you but strangely immobile.",
	"Leonard Richardson is here, asking people to lick him.",
	"It's a stupid mask, fashioned after a beagle.",
	"Your State Farm Insurance(tm) representative!",
	"It's the local draft board.",
	"Seven 1/4\" screws and a piece of plastic.",
	"An 80286 machine.",
	"One of those stupid \"Homes of the Stars\" maps.",
	"A signpost saying \"TO KITTEN\". It points in no particular direction.",
	"A hammock stretched between a tree and a volleyball pole.",
	"A Texas Instruments of Destruction calculator.",
	"It's a dark, amphorous blob of matter.",
	"Just a pincushion.",
	"It's a mighty zombie talking about some love and prosperity.",
	"\"Dear robot, you have been personally selected to recieve this Visa card...\"",
	"It's just an object.",
	"A mere collection of pixels.",
	"A badly dented high-hat cymbal lies on its side here.",
	"A marijuana brownie.",
	"A plush Chewbacca.",
	"Daily hunger conditioner from Australasia",
	"Just some stuff.",
	"Why are you touching this when you should be finding kitten?",
	"A glorious fan of peacock feathers.",
	"It's some compromising photos of Babar the Elephant.",
	"A copy of the Weekly World News. Watch out for the chambered nautilus!",
	"It's the proverbial wet blanket.",
	"A \"Get Out of Jail Free\" card.",
	"An incredibly expensive \"Mad About You\" collector plate.",
	"Paul Moyer's necktie.",
	"A haircut and a real job. Now you know where to get one!",
	"An automated robot-hater. It frowns disapprovingly at you.",
	"An automated robot-liker. It smiles at you.",
	"It's a black hole. Don't fall in!",
	"Just a big brick wall.",
	"You found kitten! No, just kidding.",
	"Heart of Darkness brand pistachio nuts.",
	"A smoking branding iron shaped like a 24-pin connector.",
	"It's a Java applet.",
	"An abandoned used-car lot.",
	"A shameless plug for Crummy - The Site: http://crummy.home.ml.org",
	"A shameless plug for Nerth Pork:",
	"A can of Spam Lite.",
	"This is another fine mess you've gotten us into, Stanley.",
	"It's scenery for \"Waiting for Godot\".",
	"A grain elevator towers high above you.",
	"A Mentos wrapper.",
	"It's the constellation Pisces.",
	"It's a fly on the wall. Hi, fly!",
	"This kind of looks like kitten, but it's not.",
	"It's a banana! Oh, joy!",
	"A helicopter has crashed here.",
	"Carlos Tarango stands here, doing his best impression of Pat Smear.",
	"A patch of mushrooms grows here.",
	"A patch of grape jelly grows here.",
	"A spindle, and a grindle, and a bucka-wacka-woom!",
	"A geyser sprays water high into the air.",
	"A toenail? What good is a toenail?",
	"You've found the fish! Not that it does you much good in this game.",
	"A Buttertonsils bar.",
	"One of the few remaining discoes.",
	"Ah, the uniform of a Revolutionary-eta minuteman.",
	"A punch bowl, filled with punch and lemon slices.",
	"It's nothing but a G-thang, baby.",
	"IT'S ALIVE! AH HA HA HA HA!",
	"This was no boating accident!",
	"Wait! This isn't the poker chip! You've been tricked! DAMN YOU, MENDEZ!",
	"A livery stable! Get your livery!",
	"It's a perpetual immobility machine (they're easier to build).",
	"\"On this spot in 1962, Henry Winkler was sick.\"",
	"There's nothing here; it's just an optical illusion.",
	"The World's Biggest Motzah Ball!",
	"A tribe of cannibals lives here. They eat Malt-O-Meal for breakfast, you know.",
	"This appears to be a large stack of trashy romance novels.",
	"Look out! Exclamation points!",
	"A herd of wild coffee mugs slumbers here.",
	"It's a limbo bar! How low can you go?",
	"It's the horizon. Now THAT'S weird.",
	"A vase full of artificial flowers is stuck to the floor here.",
	"A large snake bars your way.",
	"A pair of saloon-style doors swing slowly back and forth here.",
	"It's an ordinary bust of Beethoven... but why is it painted green?",
	"It's TV's lovable wisecracking Crow! \"Bite me!\", he says.",
	"Hey, look, it's war. What is it good for? Absolutely nothing. Say it again.",
	"It's the amazing self-referential thing that's not kitten.",
	"A flamboyant feather boa. Now you can dress up like Carol Channing!",
	"\"Sure hope we get some rain soon,\" says Farmer Joe.",
	"\"How in heck can I wash my neck if it ain't gonna rain no more?\" asks Farmer Al.",
	"\"Topsoil's all gone, ma,\" weeps Lil' Greg.",
	"This is a large brown bear. Oddly enough, it's currently peeing in the woods.",
	"A team of arctic explorers is camped here.",
	"This object here appears to be Louis Farrakhan's bow tie.",
	"This is the world-famous Chain of Jockstraps.",
	"A trash compactor, compacting away.",
	"This toaster strudel is riddled with bullet holes!",
	"It's a hologram of a crashed helicopter.",
	"This is a television. On screen you see a robot strangely similar to yourself.",
	"This balogna has a first name, it's R-A-N-C-I-D.",
	"A salmon hatchery? Look again. It's merely a single salmon.",
	"It's a rim shot. Ba-da-boom!",
	"It's creepy and it's kooky, mysterious and spooky. It's also somewhat ooky.",
	"This is an anagram.",
	"This object is like an analogy.",
	"It's a symbol. You see in it a model for all symbols everywhere.",
	"The object pushes back at you.",
	"A traffic signal. It appears to have been recently terrorized.",
	"\"There is no kitten!\" cackles the old crone. You are shocked by her blasphemy.",
	"This is a Lagrange point. Don't come too close now.",
	"The dirty old tramp bemoans the loss of his harmonica.",
	"Look, it's Fanny the Irishman!",
	"What in blazes is this?",
	"It's the instruction manual for a previous version of this game.",
	"A brain cell. Oddly enough, it seems to be functioning.",
	"Tea and/or crumpets.",
	"This jukebox has nothing but Cliff Richards albums in it.",
	"It's a Quaker Oatmeal tube, converted into a drum.",
	"This is a remote control. Being a robot, you keep a wide berth.",
	"It's a roll of industrial-strength copper wire.",
	"Oh boy! Grub! Er, grubs.",
	"A puddle of mud, where the mudskippers play.",
	"Plenty of nothing.",
	"Look at that, it's the Crudmobile.",
	"Just Walter Mattheau and Jack Lemmon.",
	"Two crepes, two crepes in a box."
};

int used_messages[MESSAGES];
char screen[81][25];

int main(int argc, char *argv[])
{
	//Do general start-of-program stuff.
	srand(time(NULL));
	cout.setf(ios::left);
	_setcursortype(0);

	if (argc == 1) { cout << "Yello!"; NUM_BOGUS = 10; } else { NUM_BOGUS = int(argv[0]); }

	object *bogus = new object[NUM_BOGUS];
	int *bogus_messages = new int[NUM_BOGUS];

	//
	//Now we have the filling in of the various arrays.
	//

	//Create an array to represent the screen so that we can make sure all
	//the objects go on different squares.
	for (int counter = 0; counter <= 80; counter++)
	{
		for (int counter2 = 0; counter2 <= 24; counter2++)
		{
			screen[counter][counter2] = EMPTY;
		}
	}
	//Create an array to ensure we don't get duplicate messages.
	for (counter = 0; counter < MESSAGES; counter++)
	{
		used_messages[counter] = 0;
	}

	//
	//Now we initialize the various game objects.
	//
	//Assign a position to the player.
	robot.x = rand() % 80+1;
	robot.y = rand() % 21+4;
	robot.character = '#';
	robot.color = DARKGRAY;
	screen[robot.x][robot.y] = ROBOT;

	//Assign the kitten a unique position.
	do
	{
		kitten.x = rand() % 80+1;
		kitten.y = rand() % 21+4;
	} while (screen[kitten.x][kitten.y] != EMPTY);

	//Assign the kitten a character and a color.
	do
	{
		kitten.character = rand() % 254 + 1;
	} while (kitten.character == '#' || kitten.character == ' ' || kitten.character == char(7));
	kitten.color = rand() % 15 + 1;
	screen[kitten.x][kitten.y] = KITTEN;

	//Now, initialize non-kitten objects.
	for (counter = 0; counter < NUM_BOGUS; counter++)
	{
		//Assign a unique position.
		do
		{
			bogus[counter].x = rand() % 80+1;
			bogus[counter].y = rand() % 21+4;
		} while (screen[bogus[counter].x][bogus[counter].y] != EMPTY);
		screen[bogus[counter].x][bogus[counter].y] = counter+2;

		//Assign a character.
		do
		{
			bogus[counter].character = rand() % 254 + 1;
		} while (bogus[counter].character == '#' || bogus[counter].character == ' ' || bogus[counter].character == char(7));
		bogus[counter].color = rand() % 15 + 1;

		//Assign a unique message.
		int index = 0;
		do
		{
			index = rand() % MESSAGES;
		} while (used_messages[index] != 0);
		bogus_messages[counter] = index;
		used_messages[index] = 1;
	}

	//Print instructions.
	clrscr();
	instructions();
	clrscr();

	//Put stuff on the screen.
	textcolor(WHITE);
	gotoxy(1,1);
	cout << "robotfindskitten v1600000.3";
	gotoxy(1,3);
	cout << "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
	gotoxy(kitten.x,kitten.y);
	draw_kitten();
	for (counter = 0; counter < NUM_BOGUS; counter++)
	{
		gotoxy(bogus[counter].x,bogus[counter].y);
		textcolor(bogus[counter].color);
		putch(bogus[counter].character);
	}

	gotoxy(robot.x,robot.y);
	draw_robot();
	int old_x = robot.x;
	int old_y = robot.y;
	do_stuff();
}
void process_input(char input);

void do_stuff()
{
	//
	//Now the fun begins.
	//
	char input;
	input = getch();
	while (int(input) != 27)
	{
		process_input(input);
		//Redraw robot, where avaliable
		if (!(old_x == robot.x && old_y == robot.y))
		{
			gotoxy(old_x,old_y);
			putch(' ');
			gotoxy(robot.x,robot.y);
			draw_robot();
			screen[old_x][old_y] = EMPTY;
			screen[robot.x][robot.y] = ROBOT;
		old_x = robot.x;
			old_y = robot.y;
		}
		input = getch();
	}
	gotoxy(1,3);
}

//Given the keyboard input, interprets it.
void process_input(char input)
{
	int check_x = robot.x;
	int check_y = robot.y;
	switch (int(input))
	{
		case 72: //up
			check_y--;
			break;
		case 80: //down
			check_y++;
			break;
		case 75: //left
			check_x--;
			break;
		case 77: //right
			check_x++;
			break;
		case 0:
			break;
		default: //invalid command
			gotoxy(1,2);
			textcolor(WHITE);
			cout << setw(80) << "Invalid command: Use direction keys or Esc.";
			return;
	}

	//Check for going off the edge of the screen.
	if (check_y < 4 || check_y > 24 || check_x < 1 || check_x > 80)
	{
		return;
	}

	//Check for collision
	if (screen[check_x][check_y] != EMPTY)
	{
		switch (screen[check_x][check_y])
		{
			case ROBOT:
				//We didn't move.
				break;
			case KITTEN: //Found it!
				gotoxy(1,2);
				cout << setw(80) << "";

				//The grand cinema scene.
				for (int counter = 0; counter <=3; counter++)
				{
					gotoxy(55+counter-1,2);
					putch(' ');
					gotoxy(62-counter+1,2);
					putch(' ');
					gotoxy(55+counter,2);
					if (int(input) == 72 || int(input) == 75)
						draw_kitten();
					else
						draw_robot();
					gotoxy(62-counter,2);
					if (int(input) == 72 || int(input) == 75)
						draw_robot();
					else
						draw_kitten();
					delay (600);
				}
				//They're in love!
				gotoxy(58,1);
				textcolor(LIGHTRED);
				putch(char(3));
				putch(char(3));
				gotoxy(1,2);
				delay (1200);
				textcolor(WHITE);
				cout << "You found kitten! Way to go, robot!\n";
				//Put "Play again?" code here.
				exit(0);
				break;
			default:
				gotoxy(1,2);
				cout << setw(80) << messages[bogus_messages[screen[check_x][check_y]-2]];
				break;
		}
		gotoxy(1,2);
		return;
	}
	//Otherwise, move the robot.
	robot.x = check_x;
	robot.y = check_y;
}

void instructions()
{
	textcolor(WHITE);
	gotoxy(1,1);
	cout <<"robotfindskitten v1600000.3\n"
		 <<"By the illustrious Leonard Richardson (C) 1997\n"
		 <<"Written especially for the Nerth Pork robotfindskitten contest\n\n"
		 <<"   In this game, you are robot (";
	draw_robot();
	textcolor(WHITE);
	cout <<"). Your job is to find kitten. This task\n"
		 <<"is complicated by the existance of various things which are not kitten.\n"
		 <<"Robot must touch items to determine if they are kitten or not. The game\n"
		 <<"ends when robotfindskitten. Alternatively, you may end the game by hitting\n"
		 <<"the Esc key. See the documentation for more information.\n\n"
		 <<"   Press any key to start.\n";
	char dummy = getch();

}

void draw_robot() //Draws robot at current position
{
	textcolor(robot.color);
	putch(robot.character);
}

void draw_kitten() //Draws kitten at current position
{
	textcolor(kitten.color);
	putch(kitten.character);
}