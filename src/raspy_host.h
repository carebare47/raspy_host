#ifndef RASPY_HOST_H
#define RASPY_HOST_H
 
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <ctime>
#include <chrono>


#include "OLEDType_SSD1306.h"
#include "OLED_GFX.h"
#include "OLED_SSD1306.h"

OLED_SSD1306 display; 

const unsigned char guitar [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3E,
0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x01, 0xE0,
0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x1E, 0x00,
0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1C, 0x70, 0x00, 0x00, 0x25, 0xE0, 0x00,
0x00, 0x63, 0xC0, 0x00, 0x01, 0xE7, 0x80, 0x00, 0x0F, 0x9F, 0x00, 0x00, 0x1C, 0x3F, 0x00, 0x00,
0x30, 0x1F, 0xE0, 0x00, 0x20, 0x4C, 0x60, 0x00, 0x21, 0x61, 0xC0, 0x00, 0x31, 0xB3, 0x00, 0x00,
0x30, 0xC2, 0x00, 0x00, 0x18, 0x46, 0x00, 0x00, 0x08, 0x16, 0x00, 0x00, 0x0E, 0x54, 0x00, 0x00,
0x07, 0x0C, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


std::chrono::high_resolution_clock::time_point last_time_guitar;
std::chrono::high_resolution_clock::time_point last_time_midi;
std::chrono::high_resolution_clock::time_point last_time_connecting;
std::chrono::high_resolution_clock::time_point connection_time;

const char* ACONNECT_GUITAR_SEARCH_TERM_ = "TriplePlay";
const char* ACONNECT_MIDI_SEARCH_TERM_ = "USB Midi";
const char* ACONNECT_CONNECTED_SEARCH_TERM_ = "Connecting";
std::string MIDI_TEXT_ = "MIDI";
int dot_animation_timer_ms = 600;

void init_timers(void);
void show_guitar(int x, int y);
void show_text(int x, int y, char* text_string);
std::string exec(const char* cmd);
void wait_for_connecting(void);
void waiting_for_midi(void);
void waiting_for_guitar(void);
int get_device_number(std::string search_term);
void connect(int sender, int reciever);
bool connection_timer(int timer_ms);
void update_display(void);




bool state_1 = false;
bool state_2 = false;
int loop_guitar = 1;
int loop_midi = 1;
int loop_connecting = 1;
bool last_aconnected = false;


#endif