#define DARWIN_FORCE_BUILTIN
#define DARWIN_DISABLE_LOG
#include "./darwin/headers/darwin.hpp"
#include <string>
#include <random>
#include <ctime>
#include <deque>
#include <utility>
int main()
{
	darwin::runtime.load("./darwin.module");
	auto pic=darwin::runtime.get_drawable();
	darwin::sync_clock clock(60);
	std::deque<std::pair<int,int>> she(3);
	int sws=0;
	int x2,y2;
	std::string str0="You lose";
	std::string str1="Please press \"Ctrl+C\" to exit";
	std::default_random_engine e(time(nullptr));
	darwin::pixel sheshen(' ',true,false,darwin::colors::blue,darwin::colors::white);
	darwin::pixel shiwu('@',true,false,darwin::colors::blue,darwin::colors::white);
	darwin::pixel die(' ',true,false,darwin::colors::blue,darwin::colors::red);
	for(int i=0; i<3; ++i) {
		she[i].first=i;
		she[i].second=0;
	}
	char fx='d';
	while(true) {
		clock.reset();
		darwin::runtime.fit_drawable();
		//shiwu shengcheng
		if(sws==0) {
			std::uniform_int_distribution<int> u1(0,0.5*pic->get_width()-1);
			std::uniform_int_distribution<int> u2(0,0.5*pic->get_height()-1);
			x2=u1(e);
			y2=u2(e);
			int count1=0;
			for(int i=0; i<she.size(); ++i) {
				if(!((she[i].first==x2)&&(she[i].second==y2)))
					++count1;
				if(count1==she.size())
					++sws;
			}
			continue;
		}
		//panding yidong
		if(darwin::runtime.is_kb_hit()) {
			switch(darwin::runtime.get_kb_hit()) {
			case'a':
					if(fx!='d'&&(fx=='w'||fx=='s'))
						fx='a';
				break;
			case'd':
					if(fx!='a'&&(fx=='w'||fx=='s'))
						fx='d';
				break;
			case'w':
				if(fx!='s'&&(fx=='a'||fx=='d'))
					fx='w';
				break;
			case's':
				if(fx!='w'&&(fx=='a'||fx=='d'))
					fx='s';
				break;
			}
		}
		pic->clear();
		//pan ding fang xiang,xing dong
		if(fx=='d') {
			if(!((she[she.size()-1].first+1==x2)&&she[she.size()-1].second==y2)) {
				she.pop_front();
			} else {
				sws=0;
			}
			int a(she[she.size()-1].first+1),b(she[she.size()-1].second);
			std::pair<int,int> ls(a,b);
			if(a>0.5*(pic->get_width()-2)) {
				fx='h';
			}
			for(int i=0; i<she.size(); ++i) {
				if(she[i].first==a&&she[i].second==b) {
					fx='h';
				}
			}
			she.push_back(ls);
		}
		if(fx=='a') {
			if(!((she[she.size()-1].first-1==x2)&&she[she.size()-1].second==y2)) {
				she.pop_front();
			} else {
				sws=0;
			}
			int a(she[she.size()-1].first-1),b(she[she.size()-1].second);
			std::pair<int,int> ls(a,b);
			if(a<0) {
				fx='h';
			}
			for(int i=0; i<she.size(); ++i) {
				if(she[i].first==a&&she[i].second==b) {
					fx='h';
				}
			}
			she.push_back(ls);
		}
		if(fx=='s') {
			if(!((she[she.size()-1].first==x2)&&she[she.size()-1].second+1==y2)) {
				she.pop_front();
			} else {
				sws=0;
			}
			int a(she[she.size()-1].first),b(she[she.size()-1].second+1);
			std::pair<int,int> ls(a,b);
			if(b>=(pic->get_height())) {
				fx='h';
			}
			for(int i=0; i<she.size(); ++i) {
				if(she[i].first==a&&she[i].second==b) {
					fx='h';
				}
			}
			she.push_back(ls);
		}
		if(fx=='w') {
			if(!((she[she.size()-1].first==x2)&&she[she.size()-1].second-1==y2)) {
				she.pop_front();
			} else {
				sws=0;
			}
			int a(she[she.size()-1].first),b(she[she.size()-1].second-1);
			std::pair<int,int> ls(a,b);
			if(b<0) {
				fx='h';
			}
			for(int i=0; i<she.size(); ++i) {
				if(she[i].first==a&&she[i].second==b) {
					fx='h';
				}
			}
			she.push_back(ls);
		}
		//huashe he shiwu
		for(int i=0; i<she.size(); ++i) {
			pic->draw_pixel(she[i].first*2,she[i].second,sheshen);
			pic->draw_pixel(she[i].first*2+1,she[i].second,sheshen);
		}
		pic->draw_pixel(2*x2,y2,shiwu);
		pic->draw_pixel(2*x2+1,y2,shiwu);
		if(fx=='h') {
			pic->fill(die);
			pic->draw_string(0.5*(pic->get_width()-str0.size()),0.5*pic->get_height(),str0,darwin::pixel(' ',true,false,darwin::colors::blue,darwin::colors::white));
			pic->draw_string(0.5*(pic->get_width()-str1.size()),pic->get_height()-1,str1,darwin::pixel(' ',true,false,darwin::colors::blue,darwin::colors::white));
		}
		darwin::runtime.update_drawable();
		clock.sync();
	}
	return 0;
}