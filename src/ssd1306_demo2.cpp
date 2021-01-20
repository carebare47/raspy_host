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

void show_guitar(int x, int y){
	/*
	usleep(20000);
	  display.clearDisplay();
 usleep(20000);
*/
	 display.drawBitmap(x,y,guitar,32,32,1);
 
}

void show_text(bool clear, int x, int y, char* text_string){
	if (clear){
		usleep(20000);
		display.clearDisplay();
	}
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(x, y);
	display.print(text_string);
}


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
int loop_guitar = 1;
int loop_midi = 1;
int loop_connecting = 1;

void wait_for_connecting(void){
	std::string waiting_ = "connecting\n";
	std::chrono::duration<double, std::milli> time_span = std::chrono::high_resolution_clock::now() - last_time_connecting;
	if (time_span.count() > 600){
		last_time_connecting = std::chrono::high_resolution_clock::now();
		loop_connecting++;
	}
	if (loop_connecting == 5)
		loop_connecting = 1;
	for (int i=1; i<(loop_connecting+1); i++){
		waiting_ = waiting_ + ".";
	}
	waiting_ = waiting_ + "\n";
	show_text(false, 64, 8, &waiting_[0]);
}
void waiting_for_midi(void){
	std::string waiting_ = "waiting\n";
	std::string for_ = "for\n";
	std::string midi_ = "midi\n";
	show_text(false, 64, 0, &waiting_[0]);
	show_text(false, 64, 8, &for_[0]);
	show_text(false, 64, 16, &midi_[0]);
	std::chrono::duration<double, std::milli> time_span = std::chrono::high_resolution_clock::now() - last_time_midi;
	if (time_span.count() > 600){
		last_time_midi = std::chrono::high_resolution_clock::now();
		loop_midi++;
	}
	if (loop_midi == 5)
		loop_midi = 1;
	waiting_ = "";
	for (int i=1; i<(loop_midi+1); i++){
		waiting_ = waiting_ + ".";
	}
	waiting_ = waiting_ + "\n";
	show_text(false, 64, 24, &waiting_[0]);
}

void waiting_for_guitar(void){
	std::string waiting = "waiting\nfor\nguitar\n";
	show_text(false, 0, 0, &waiting[0]);
	std::chrono::duration<double, std::milli> time_span = std::chrono::high_resolution_clock::now() - last_time_guitar;
	if (time_span.count() > 600){
		last_time_guitar = std::chrono::high_resolution_clock::now();
		loop_guitar++;
	}
	if (loop_guitar == 5)
		loop_guitar = 1;
	waiting = "";
	for (int i=1; i<(loop_guitar+1); i++){
		waiting = waiting + ".";
	}
	waiting = waiting + "\n";
	show_text(false, 0, 24, &waiting[0]);
}

bool state_1 = false;
bool state_2 = false;

int get_device_number(std::string search_term){
	std::string::size_type sz;   // alias of size_t
	std::string search_string = "aconnect -l | grep \"" + search_term + "\" | grep \"client\" | awk '{print $2}' | sed -r 's/://g'";
	std::string resp = exec(&search_string[0]);
	std::cout << resp << "\n";
	int midi_port_number = 99999;
	try{
		midi_port_number = std::stoi(resp, &sz);
	}
	catch (const std::exception& e){
		        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
	}
	return midi_port_number;
}
void connect(int sender, int reciever){
	
	std::string acon = "aconnect ";
	std::stringstream command_ss;
	command_ss.clear();
	command_ss.str("");
	std::string cmd = std::string("aconnect ") + std::to_string(sender) + std::string(" ") + std::to_string(reciever) + "\n";
	std::cout << cmd;
	std::string output = exec(&cmd[0]);
	std::cout << output << "\n";
}
//aconnect -l | grep "TriplePlay" | grep "client" | awk '{print $2}' | sed -r 's/://g'

bool connection_timer(int timer_ms){
	std::chrono::duration<double, std::milli> time_span = std::chrono::high_resolution_clock::now() - connection_time;

	if (time_span.count() > timer_ms){
		connection_time = std::chrono::high_resolution_clock::now();
		return true;
	} else {
		return false;
	}
}
bool last_aconnected = false;
void update_display(void){
	std::string CONST_MIDI_TEXT_ = "MIDI";
	bool aconnected;
	std::string midi_devices = exec("aconnect -l");
	//std::cout << midi_devices << "\n";
	display.clearDisplay();
	bool bWaitMidi = false;
	if (midi_devices.find("USB Midi") == std::string::npos){
		//show_text(false, 42, 24, &CONST_NO_MIDI_SAD_[0]);
		waiting_for_midi();
		bWaitMidi = true;
	} else {
		show_text(false, 76, 24, &CONST_MIDI_TEXT_[0]);
	}

	if (midi_devices.find("TriplePlay") == std::string::npos){
		//show_text(false, 0, 24, &CONST_ANGER_[0]);
		waiting_for_guitar();
	} else {
		show_guitar(0,0);
	}
	//display.display();
	
	if (midi_devices.find("Connecting") == std::string::npos){
		aconnected = false;
		if (!bWaitMidi){
			wait_for_connecting();
		}
	} else {
		aconnected = true;
		std::string T2 = "CONNECTED!";		
		show_text(false, 64, 8, &T2[0]);
	}
	

	if (!aconnected && connection_timer(6000)){
		usleep(2*1000*1000);
		int iGuitar = get_device_number("TriplePlay");
		int iMidi = get_device_number("USB Midi");
		if ((iGuitar > 99) || (iMidi > 99)){
			connection_time = std::chrono::system_clock::from_time_t(0);
		} else {
			connect(iGuitar, iMidi);
		}
	}
	
		
		display.display();


}


int main(int argc, char **argv)
{

	if ( !display.init(OLED_I2C_RESET,OLED_OLED_I2C_128x32) )
		exit(EXIT_FAILURE);
	
	last_time_guitar = std::chrono::high_resolution_clock::now();
	last_time_connecting = std::chrono::high_resolution_clock::now();
	last_time_midi = std::chrono::high_resolution_clock::now();
	connection_time = std::chrono::high_resolution_clock::now();
	display.begin();
	
	while (true) {		
		update_display();
		display.display();
		usleep(100*1000);
	}
	display.close();

}