#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'

void welcome();				   //55��ʼ����
void Finish();	               //291��������
int color(int c);
void menu();
void creatgraph();			   //69Χǽ��ӡ
void gotoxy(int x, int y);	   //111�����ת����ΪX 0,1,2..
void gotoprint(int x, int y);  //121��ת��ӡ
void gotodelete(int x, int y); //127��תɾ��
void creatfood();			   //133ʳ�����
int ClickControl();			   //157��ȡ�����ź�
int Judge();				   //270��Ϸ�����ж�
void MovingBody();			   //172�ߵ��ƶ�
void Eating();				   //223�߳Ե�������Ĳ������쳤��
void ChangeBody(int a, int b); //245�ߵ�����任,��һ������ǰһ��STRUCT,a,bΪhead֮ǰ����

/*ȫ�ֱ��� + Ԥ����*/
typedef struct Snakes
{
	int x;
	int y;
	struct Snakes *next;
} snake;

snake *head, *tail;

struct Food
{
	int x;
	int y;
} food;
char name[20];
int score = 0;
char click = 'w';
int speed;
int n;
char sel;

/************************************************************/
int main()
{
	welcome();
	//mciSendString("open C:\\snake\\2.mp3", NULL, 0, NULL);
    //mciSendString("play C:\\snake\\2.mp3", NULL, 0, NULL);
	lable:
    menu();
	creatgraph();
	creatfood();
	if (ClickControl() == 0)
	{
		if(sel=='y'||sel=='Y')
		{
		    system("cls");
			sel ='n';
			goto lable;
		}
        gotoxy(18, 22);
        color(10);
        printf("thanks for playing!\n");
        gotoxy(18, 28);
        system("pause");
		return 0;
	}

}

/**********************************************************/
void welcome()
{
	gotoxy(10, 1);
    color(2);
	printf(" /**************************************************************/");
    printf("                                                                                         \n");
	printf("                       __________       ___                                              \n");
	printf("                      /          \\     / \\ \\    |____      __\\__                     \n");
	printf("                     /  ________  \\   / ___ \\  _/ __     | |   /                       \n");
	printf("                     |  |      |__|     _/_   |_|  /    [|] |/                           \n");
	printf("                     |  |              | | |      /     _|_ \\__/                        \n");
	printf("                     \\  \\_______        / \\      |___/        ____                    \n");
	printf("                      \\         \\    ____ ____      ____   __ |  |  ___   ______       \n");
	printf("                       \\_______  \\   |  |/    \\    /    \\_/ / |  | /  /  /      \\   \n");
	printf("                               \\  \\  |    ___  \\  / ____   /  |  |/  /  /  ____  \\   \n");
	printf("                     __        |  |  |   /   \\  \\ | |  |  /   |     /  |  /____\\  |   \n");
	printf("                    \\  \\_______|  |  |  |    |  | | |__|  |   |     \\  |  ________/   \n");
	printf("                     \\            /  |  |    |  |  \\       \\  |  |\\  \\  \\  \\____  \n");
	printf("                      \\__________/   |__|    |__|   \\___/\\__\\ |__| \\__\\  \\______/ \n");
	gotoxy(10, 25);
	printf("/**************************************************************/");
	gotoxy(20, 18);
	printf("��ӭ����̰������Ϸ:)");
	gotoxy(20, 20);
	printf("����Ӣ�����뷨�в����������ƶ���ͬ�ڳԵ��Լ���wasd����p��ͣ");
    color(10);
	gotoxy(20, 22);
	printf("�������������:");
	scanf("%s", name);
	system("cls");
}

void menu()
{
    lable :
    gotoxy(10, 1);
    color(2);
	printf("/**************************************************************/");
    printf("                                                                                         \n");
	printf("                       __________       ___                                              \n");
	printf("                      /          \\     / \\ \\    |____      __\\__                     \n");
	printf("                     /  ________  \\   / ___ \\  _/ __     | |   /                       \n");
	printf("                     |  |      |__|     _/_   |_|  /    [|] |/                           \n");
	printf("                     |  |              | | |      /     _|_ \\__/                        \n");
	printf("                     \\  \\_______        / \\      |___/        ____                    \n");
	printf("                      \\         \\    ____ ____      ____   __ |  |  ___   ______       \n");
	printf("                       \\_______  \\   |  |/    \\    /    \\_/ / |  | /  /  /      \\   \n");
	printf("                               \\  \\  |    ___  \\  / ____   /  |  |/  /  /  ____  \\   \n");
	printf("                     __        |  |  |   /   \\  \\ | |  |  /   |     /  |  /____\\  |   \n");
	printf("                    \\  \\_______|  |  |  |    |  | | |__|  |   |     \\  |  ________/   \n");
	printf("                     \\            /  |  |    |  |  \\       \\  |  |\\  \\  \\  \\____  \n");
	printf("                      \\__________/   |__|    |__|   \\___/\\__\\ |__| \\__\\  \\______/ \n");
	gotoxy(10, 31);
	printf("/**************************************************************/");
    color(10);
    gotoxy(35, 20);
	printf("��-------------------------------��\n");
	int i; 
    for(i=21;i<26;i++)
    {
        gotoxy(35, i);
        printf("��                               ��\n");
    }
	gotoxy(35, 26);
	printf("��-------------------------------��\n");
	gotoxy(42, 22);
	color(13);
	printf("1.��ʼ��Ϸ");
    color(11);
	gotoxy(42, 24);
	printf("2.�˳���Ϸ");
	gotoxy(42,27);
	color(3);
	printf("��ѡ��[1 2]:[ ]\b\b");        //\bΪ�˸�ʹ�ù�괦��[]�м�
	color(14);
    scanf("%d", &n); 					//����ѡ��
    switch (n)
    {
    	case 1:					//ѡ��ʼ��Ϸ
    		system("cls");
        	break;
    	case 2:
        	color(6);
            gotoxy(42, 29);
            printf("�߿�����!�t(��?����)�r\n");
			color(1);
            system("pause");
            exit(0);
        	break;
		default:				//�����1~3֮���ѡ��
			color(12);
			gotoxy(42,29);
			printf("������1~2֮�����!");
			getch();			//���������
			system("cls");		//����
            goto lable ;
    }
}

/**********************************************************/
void creatgraph()
{
	int i;
	srand((int)time(NULL));
	color(rand()%12+1);
	for (i = 0; i < 58; i += 2) //��ӡ���±߿�
	{
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++)
	{
		gotoprint(0, i);
		gotoprint(56, i);
	}
	gotoxy(63, 10);
	printf("��� %s ,��ӭ����", name);
	gotoxy(63, 15);
	printf("�㵱ǰ�ķ����� %d    =���أ�= ������������", score);
	head = (snake *)malloc(sizeof(snake));
	head->x = 16;
	head->y = 15;
	tail = (snake *)malloc(sizeof(snake));
	snake *p = (snake *)malloc(sizeof(snake));
	snake *q = (snake *)malloc(sizeof(snake));
	p->x = 16;
	p->y = 16;
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = tail;
	tail->next = NULL;
	tail->x = 4;
	tail->y = 2;
}
/**********************************************************/
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
/**********************************************************/
void gotoprint(int x, int y)
{
	gotoxy(x, y);
	printf("��");
}
/**********************************************************/
void gotodelete(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}
/**********************************************************/
void creatfood()
{
	srand((int)time(NULL));
    lable:
	food.y = rand() % (25 - 1 + 1) + 1;
	food.x = rand() % (54 - 2 + 1) + 2;
	if (food.x % 2 != 0)
	{
		food.x = food.x + 1;
	}
	snake *judge = head;
	while (1) //�����ų������ظ�
	{
		if (judge->next == NULL)
			break;
		if (food.x == judge->x && food.y == judge->y)
		{
			goto lable;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("��");
}
/**********************************************************/
int ClickControl()
{
	while (1)
	{
		if (Judge() == 0 )
			return 0;
		if (_kbhit())
		{
			click = _getch();
		}
		MovingBody();
		Eating();
	}
	return 1;
}
/**********************************************************/
void MovingBody()
{
	int count = 0;
	int a = head->x, b = head->y;
	snake *p = head;
	//ͨ������պ��ӡʵ�ֶ���Ч��
	while (1)
	{
		if (p->next == NULL)
			break;
		gotodelete(p->x, p->y);
		count++;
		p = p->next;
	}
	switch (click)
	{
	case up:
		head->y -= 1;
		ChangeBody(a, b);
		break;
	case down:
		head->y += 1;
		ChangeBody(a, b);
		break;
	case left:
		head->x -= 2;
		ChangeBody(a, b);
		break;
	case right:
		head->x += 2;
		ChangeBody(a, b);
		break;
	case stop:
		_getch();
		break;
	}
	p = head;
	while (1)
	{
		if (p->next == NULL)
			break;
		gotoprint(p->x, p->y);
		p = p->next;
	}
	p = head;
	gotoxy(0, 28);
	if (count <= 10)
		speed = 150;
	else if (count > 10 && count <= 20)
		speed = 100;
	else if (count > 20 && count <= 40)
		speed = 50;
	else
		speed = 25;
	Sleep(speed);
}
/**********************************************************/
void Eating()
{
	if (head->x == food.x && head->y == food.y)
	{
		creatfood();
		snake *_new = (snake *)malloc(sizeof(snake));
		snake *p;
		p = head;
		while (1)
		{
			if (p->next->next == NULL)
				break;
			p = p->next;
		}
		p->next = _new;
		_new->next = tail;
		score += 10;
		gotoxy(77, 15);

		if(score<=290)
			printf("%d", score);
	}
}
/**********************************************************/
void ChangeBody(int a, int b)
{
	snake *p = head->next;
	int mid1, mid2, _mid1, _mid2;
	mid1 = p->x;
	mid2 = p->y;
	while (1)
	{
		if (p->next->next == NULL)
			break;
		_mid1 = p->next->x;
		_mid2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = _mid1;
		mid2 = _mid2;
		p = p->next;
	}
	p = head->next;
	//if (p->next!= NULL)
	{
		p->x = a;
		p->y = b;
	}
}
/**********************************************************/
int Judge()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
	{
		Finish();
		return 0;
	}
	snake *p = head->next;
	while (1)
	{
		if (p->next == NULL)
			break;
		if (head->x == p->x && head->y == p->y)
		{
			click='w';
			Finish();
			return 0;
		}
		p = p->next;
	}
	return 1;
}
/**********************************************************/
void Finish()
{
	system("cls");
	gotoxy(10, 1);
	printf("/**************************************************************/");
			gotoxy(18, 2);
		    printf("\n                                                               \n");
            printf("            ****          ****    ******************    ******************  \n");
            printf("            ****          ****    ******************    ******************  \n");
            printf("            ****          ****           ****                  ****  \n");
            printf("            ****          ****           ****                  **** \n");
            printf("            ******************           ****                  ****      \n");
            printf("            ******************           ****                  ****   \n");
            printf("            ****          ****           ****                  ****   \n");
            printf("            ****          ****           ****                  ****   \n");
            printf("            ****          ****    ******************           ****   \n");
            printf("            ****          ****    ******************           ****   \n"); 
	gotoxy(10, 25);
	printf("/**************************************************************/");
	gotoxy(18, 14);
	color(2);
	printf("����   ��̭      o(*������*)o");
	gotoxy(20, 16);
	color(3);
	printf("������շ����� %d    hiahiahia", score);
	gotoxy(18, 18);
	color(4);
	printf("������Ŷ��     ����Ŭ��O(��_��)O\n");
	gotoxy(18, 20);
	color(8);
	printf("����ϸ񣬹��򵽼�\n");
	gotoxy(18, 22);
	color(9);
	printf("���ޣ���Y/N��");
	getchar();
	sel=getchar();
}

int color(int c)
{
	//SetConsoleTextAttribute��API���ÿ���̨����������ɫ�ͱ���ɫ�ĺ���
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}

