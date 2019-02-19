#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include <iostream>
#include <algorithm>

std::string makeJsonObject(std::string bw, std::string sf, int sn,
						std::string rt, std::string st, float rssi,
						float p_rssi, float snr, float lat, float lng);

int sendNodeREDServer(std::string src);
