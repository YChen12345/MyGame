#pragma once
#include <iostream>
#include <fstream>
class gamedata {
public:
	int scenceid;
	int state;
	int score;
	float totaltime;
	float createThreshold;
	float cam_pos_x;
	float cam_pos_y;
	float player_pos_x;
	float player_pos_y;
	float player_atkgap;
	float player_atktimer;
	int player_blood;
	int player_skill_level;
	float player_skillgap;
	float player_skilltimer;
	int emynum;
	int emykid[200] = { 0 };
	int emyblood[200] = { 0 };
	float emypos_x[200] = { 0 };
	float emypos_y[200] = { 0 };
	int propnum;
	float propkid[100] = { 0 };
	float proppos_x[100] = { 0 };
	float proppos_y[100] = { 0 };
	int emy_bullet_num;
	int eb_hurt[200] = { 0 };
	float eb_timer[200] = { 0 };
	float eb_pos_x[200] = { 0 };
	float eb_pos_y[200] = { 0 };
	float eb_dir_x[200] = { 0 };
	float eb_dir_y[200] = { 0 };
	int player_bullet_num;
	int pb_kid[200] = { 0 };
	int pb_hurt[200] = { 0 };
	float pb_timer[200] = { 0 };
	float pb_pos_x[200] = { 0 };
	float pb_pos_y[200] = { 0 };
	float pb_dir_x[200] = { 0 };
	float pb_dir_y[200] = { 0 };

	
public:
	gamedata() {
		scenceid = 0;
		state = 0;
		score = 0;
		totaltime = 0;
		createThreshold = 3.0f;
		cam_pos_x = 0;
		cam_pos_y = 0;
		player_pos_x=0;
		player_pos_y=0;
		player_atkgap=1;
		player_atktimer=0;
		player_blood=20;
		player_skill_level=1;
		player_skillgap=6;
		player_skilltimer=1;
		emynum=0;
		propnum = 0;
		emy_bullet_num = 0;
		player_bullet_num = 0;
	}
	void load() {
		std::ifstream datafile("Resources/archive.txt");
		datafile >> scenceid;
		datafile >> state ;
		datafile >> score ;
		datafile >> totaltime ;
		datafile >> createThreshold ;
		datafile >> cam_pos_x;
		datafile >> cam_pos_y;
		datafile >> player_pos_x;
		datafile >> player_pos_y ;
		datafile >> player_atkgap ;
		datafile >> player_atktimer ;
		datafile >> player_blood ;
		datafile >> player_skill_level;
		datafile >> player_skillgap ;
		datafile >> player_skilltimer;
		datafile >> emynum ;
		datafile >> propnum;
		datafile >> emy_bullet_num;
		datafile >> player_bullet_num;
		for (int i = 0; i < emynum; i++) {
			datafile >> emykid[i];
			datafile >> emyblood[i];
			datafile >> emypos_x[i];
			datafile >> emypos_y[i];
		}
		for (int i = 0; i < propnum; i++) {
			datafile >> propkid[i];
			datafile >> proppos_x[i];
			datafile >> proppos_y[i];
		}
		for (int i = 0; i < emy_bullet_num; i++) {
			datafile >> eb_hurt[i];
			datafile >> eb_timer[i];
			datafile >> eb_pos_x[i];
			datafile >> eb_pos_y[i];
			datafile >> eb_dir_x[i];
			datafile >> eb_dir_y[i];
		}
		for (int i = 0; i < player_bullet_num; i++) {
			datafile >> pb_kid[i];
			datafile >> eb_hurt[i];
			datafile >> eb_timer[i];
			datafile >> eb_pos_x[i];
			datafile >> eb_pos_y[i];
			datafile >> eb_dir_x[i];
			datafile >> eb_dir_y[i];
		}
	}
	void save() {
		std::ofstream datafile("Resources/archive.txt");
		if (!datafile.is_open()) {
			std::cerr << "can not open this file\n";
			return;
		}
		datafile << scenceid << ' ';
		datafile << state << ' ';
		datafile << score << ' ';
		datafile << totaltime << ' ';
		datafile << createThreshold << ' ';
		datafile << cam_pos_x << ' ';
		datafile << cam_pos_y << ' ';
		datafile << player_pos_x << ' ';
		datafile << player_pos_y << ' ';
		datafile << player_atkgap << ' ';
		datafile << player_atktimer << ' ';
		datafile << player_blood << ' ';
		datafile << player_skill_level << ' ';
		datafile << player_skillgap << ' ';
		datafile << player_skilltimer << ' ';
		datafile << emynum << ' ';
		datafile << propnum << ' ';
		datafile << emy_bullet_num << ' ';
		datafile << player_bullet_num << ' ';
		for (int i = 0; i < emynum; i++) {
			datafile << emykid[i] << ' ';
			datafile << emyblood[i] << ' ';
			datafile << emypos_x[i] << ' ';
			datafile << emypos_y[i] << ' ';
		}
		for (int i = 0; i < propnum; i++) {
			datafile << propkid[i] << ' ';
			datafile << proppos_x[i] << ' ';
			datafile << proppos_y[i] << ' ';
		}
		for (int i = 0; i < emy_bullet_num; i++) {
			datafile << eb_hurt[i] << ' ';
			datafile << eb_timer[i] << ' ';
			datafile << eb_pos_x[i] << ' ';
			datafile << eb_pos_y[i] << ' ';
			datafile << eb_dir_x[i] << ' ';
			datafile << eb_dir_y[i] << ' ';
		}
		for (int i = 0; i < player_bullet_num; i++) {
			datafile << pb_kid[i] << ' ';
			datafile << eb_hurt[i] << ' ';
			datafile << eb_timer[i] << ' ';
			datafile << eb_pos_x[i] << ' ';
			datafile << eb_pos_y[i] << ' ';
			datafile << eb_dir_x[i] << ' ';
			datafile << eb_dir_y[i] << ' ';
		}
		datafile.close();
	}
};