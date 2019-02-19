#include "utils.h"

std::string makeJsonObject(std::string bw, std::string sf, int sn,
							std::string rt, std::string st, float rssi,
							float p_rssi, float snr, float lat, float lng) {
	Json::Value root;
	Json::Value attr;
	Json::Value attrs;
	Json::FastWriter fastWriter;

	// Make Json Object
	root["bw"] = bw;
	root["sf"] = sf;

	attr["sn"] = sn;
	attr["rt"] = rt;
	attr["st"] = st;
	attr["rssi"] = rssi;
	attr["p_rssi"] = p_rssi;
	attr["snr"] = snr;
	attr["lat"] = lat;
	attr["lng"] = lng;
	
	attrs.append(attr);
	root["attrs"] = attrs;

	std::cout << root << std::endl;
	std::string result = fastWriter.write(root);
	
	result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());

	return result;

}


int sendNodeREDServer(std::string src) {
    CURL *curl;
	CURLcode res;

	std::string strTargetURL;
	std::string strResourceJSON;
				     
	struct curl_slist *headerlist = nullptr;
	headerlist = curl_slist_append(headerlist, "Content-Type: application/json");

	strTargetURL = "http://164.125.34.167:1880/lora";
	strResourceJSON = src;
								     
	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, strTargetURL.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strResourceJSON.c_str());

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		curl_slist_free_all(headerlist);
	
		return true;
	}
	return false;
}
	
