#include<iostream>
#include<fstream>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "got.h"
#include"getch.h"
#include"swap.h"
#include "kbhit.h"

#define getoxy gotoxy
#define UP 1
#define DOWN 3
#define LEFT 2
#define RIGHT 4

class TheGame
{
public:

	int pointer_pos,initial_pos;
	time_t initial;
	int no,dir;

	struct snake_body{
		int x,y;
		struct snake_body* next;
		struct snake_body* prev;
	};

	struct trt{
		int x,y;
	};

	struct snake_body* start;
	struct trt* treat;

	TheGame(){
		pointer_pos=initial_pos=23;
		treat=(struct trt*)malloc(sizeof(struct trt));
	}

	void pointer(){
		gotoxy(81,pointer_pos);
		std::cout<<"->";
	}

	/*void preoptions(){ //FUNCTION THAT USES DIRECTION ARROWS. INCOMPLETE. FOR LATER
		gotoxy(-1,-1);
		std::cout<<"\t\t\t\tNew Game"<<endl<<"\t\t\t\tControls"<<endl<<"\t\t\t\tHighscores"<<endl<<"\t\t\t\tExit"<<endl;
		pointer(1);
		int x;
		if (getch() == '^[') { // if the first value is esc
    			getch(); // skip the [
    			switch(getch()) { // the real value
        			case '[A':
            // code for arrow up
            			break;
        			case '[B':
            				pointer(2);
            			break;
        			case '[C':
            // code for arrow right
            			break;
        			case '[D':
            // code for arrow left
            			break;
    			}
		}
	}*/

	void preoptions(){ //FUNCTION THAT USES W/A/S/D
		system("clear");
		gotoxy(-1,-1);
		for(int i=0;i<22;i++)
			std::cout<<endl;
		std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\b\b\b\b\bNew Game"<<endl<<"\t\t\t\t\t\t\t\t\t\t\t\b\b\b\b\bControls"<<endl<<"\t\t\t\t\t\t\t\t\t\t\t\b\b\b\b\bHighscores"<<endl<<"\t\t\t\t\t\t\t\t\t\t\t\b\b\b\b\bExit"<<endl<<endl<<endl<<"\t\t\t\t\t\t\t\t\t\b\b\b\b\bNote: Use W/A/S/D to control the arrow";
		pointer();
		char c;
		c=getch();
		if(c=='W'||c=='w'){
			if(pointer_pos!=initial_pos){
				pointer_pos--;
				preoptions();
			 }
			else{
				std::cout<<'\a';
				preoptions();
			}
		}
		else if(c=='S'||c=='s'){
			if(pointer_pos!=initial_pos+3){
				pointer_pos++;
				preoptions();
			}
			else{
				std::cout<<'\a';
				preoptions();
			}
		}
		else if(c=='\n'){
			if(pointer_pos==initial_pos){
				run_game();
			}
			else if(pointer_pos==initial_pos+1){
				controls();
			}
			else if(pointer_pos==initial_pos+2){
				highscores();
			}
			else if(pointer_pos==initial_pos+3){
				system("clear");
				exit(0);
			}
		}
		else{
			std::cout<<'\a';
			preoptions();
		}
	}

	void run_game(){
		initial=time(NULL);
		inital_parameter();
		gotoxy(0,2);
		game_display();
		//location_disp();
		//game_movement();
		//wait_time(1);
		usleep(1000000);
		game_movement();

		//location_disp();
		game_display();
		getoxy(0,100);
	}

	void inital_parameter(){
		dir=UP;
		struct snake_body* p;
		start=p=(struct snake_body*)malloc(sizeof(struct snake_body));
		p->x= rand()%80+10+40;
		p->y=rand()%10+10+14;
		start->prev=NULL;
		start->next=NULL;
		no=2;
		new_treat_pos();
		snake_bodypart(2);
		snake_bodypart(3);
	}

	void new_treat_pos(){
		treat->x=rand()%98+41;
		treat->y=rand()%28+15;
	}

	void game_display(){
		box();
		snake_head_up();
		//snake_bodypart_disp(no);
		//snake_bodypart_disp(no);
		disp_treat();
	}

	void snake_head_up(){
		gotoxy(start->x,start->y);
		std::cout<<"▲";
	}

	void snake_bodypart(int n){
		n=n-2;
		struct snake_body* p;
		struct snake_body* nav;
		p=(struct snake_body*)malloc(sizeof(struct snake_body));
		nav=start;
		for(int i=0;i<n;i++){
			nav=nav->next;
		}
		nav->next=p;
		p->x=nav->x;
		p->y=nav->y+1;
		p->prev=nav;
		p->next=NULL;
	}

	void snake_bodypart_disp(int n){
		n=n-1;
		struct snake_body* nav;
		nav=start;
		for(int i=0;i<n;i++){
			nav=nav->next;
		}
		gotoxy(nav->x,nav->y);
		std::cout<<"●";
		no++;
	}

	void disp_treat(){
		while(check_intersection(treat->x,treat->y)){
			new_treat_pos();
		}
		getoxy(treat->x,treat->y);
		std::cout<<"◌";
	}

	int check_intersection(int x,int y){
		struct snake_body* nav=start;
		while(1){
			if(nav->x==x||nav->y==y)
				return 1;
			else{
				if(nav->next==NULL)
					return 0;
				else
					nav=nav->next;
			}
		}
	}

	void game_movement (){
		struct snake_body* nav=start;
		int temp_x=nav->x,temp_y=nav->y;
		if(dir==UP)
			nav->y--;
		else if(dir==DOWN)
			nav->y++;
		else if(dir==LEFT)
			nav->x--;
		else if(dir==RIGHT)
			nav->x++;
		nav=nav->next;
		while(1){
			swap(&temp_x,&nav->x);
			swap(&temp_y,&nav->y);
			if(nav->next==NULL)
				break;
			else
				nav=nav->next;
		}
		for(time_t curr=time(NULL);curr==initial+1;curr=time(NULL));
	}

	void wait_time(int wait_t){
		time_t curr=time(NULL);
		time_t nav_t=time(NULL);
		while(1){
			if (nav_t-curr==wait_t) {
				break;
			}
			else{
				nav_t=time(NULL);
				game_display();
			}
		}
	}

	void controls(){
		system("clear");
		for(int i=0;i<21;i++)
			std::cout<<endl;
		std::cout<<"\t\t\t\t\t\t\t\t\tUse W/A/S/D to control Rohit, the snake"<<endl<<endl<<endl<<"\t\t\t\t\tThe aim is to make Rohit eat as many treats as possible without making him eat itself or the border";
		std::cout<<endl<<endl<<endl<<"\t\t\t\t\t\t\t\t\tPress anything to continue...";
		char c=getch();
		if(c){
			preoptions();
		}
	}

	void highscores(){//MAX name of 8 characters
		system("clear");
		gotoxy(80,18);
		std::cout<<"NAME\t\tSCORE";
		fstream hscores;
		hscores.open("ht_highscores.txt");
		int scores[5]={};
		char names[20][5]={};
		for(int i=0;i<5;i++){
			gotoxy(80,20+i);
			hscores>>names[i]>>scores[i];
			std::cout<<names[i]<<"\t\t\t"<<scores[i];
			if(hscores.eof()){
				for(;i<5;i++){
					gotoxy(80,20+i);
					std::cout<<"----"<<"\t\t"<<" ----";
				}
				break;
			}
	 	}
		std::cout<<endl<<endl<<endl<<endl<<"\t\t\t\t\t\t\t\t\t     Press anything to continue...";
		char c;
		if(getch())
		{
			preoptions();
		}
	}

	void location_disp(){
		struct snake_body* nav=start;
		while(1){
			std::cout<<nav->x<<'\t'<<nav->y<<endl;
			if(nav->next==NULL)
				break;
			else
				nav=nav->next;
		}
	}

	void box(){
		system("clear");
		gotoxy(40,14);
		int l=30;
		int b=100;
		for(int i=0;i<b;i++){
			std::cout<<"#";
		}
		std::cout<<endl;
		int i;
		for(i=0;i<l-2;i++){
			gotoxy(40,15+i);
			std::cout<<"#";
			for(int j=0;j<b-2;j++){
				std::cout<<" ";
			}
			std::cout<<"#"<<endl;
		}
		gotoxy(40,15+i);
		for(int j=0;j<b;j++){
			std::cout<<"#";
		}
	}
};

int main(){
	srand(time(NULL));
	TheGame newgame;
	newgame.run_game();
}
