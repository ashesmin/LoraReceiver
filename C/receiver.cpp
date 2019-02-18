#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include <iostream>

int main(int argc, char *argv[]) {
	Json::Value root;
	Json::Value attr;
	Json::Value attrs;
	Json::FastWriter fastWriter;

	if (argc != 3) {
		std::cout << "Usage : receiver [bandwidth] [spreading factor]" << std::endl;
		return -1;
	}

	// Make Json Object
	root["bw"] = argv[1];
	root["sf"] = argv[2];

	attr["sn"] = 1;
	attr["rt"] = "123456";
	attr["st"] = "987654";
	attr["rssi"] = -90;
	attr["p_rssi"] = -91;
	attr["snr"] = 30;
	attr["lat"] = 35.236222;
	attr["lng"] = 129.074821;

	attrs.append(attr);
	root["attrs"] = attrs;

	std::cout << root << std::endl;
	std::string strResourceJSON = fastWriter.write(root);

	CURL *curl;
	CURLcode res;

	std::string strTargetURL;

	struct curl_slist *headerlist = nullptr;
	headerlist = curl_slist_append(headerlist, "Content-Type: application/json");

	strTargetURL = "http://127.0.0.1:1880/lora/";

	// Send Json Object MongoDB using cURL
	curl = curl_easy_init();
	if (curl) {
	    // example.com is redirected, so we tell libcurl to follow redirection
		curl_easy_setopt(curl, CURLOPT_URL, strTargetURL.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strResourceJSON.c_str());

	    // Perform the request, res will get the return code
	    res = curl_easy_perform(curl);
	    // Check for errors
	    if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

		// always cleanup
		curl_easy_cleanup(curl);
	}

	return 0;
}
