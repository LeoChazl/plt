#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../client.h"
#include "../../shared/engine.h"
#include <SFML/Network.hpp>

using namespace std;
using namespace client;

ServerTest::ServerTest(){

}

void ServerTest::run(){
    cout<<"---- SERVER TEST ----"<<endl;

	string name;
	cout<<"Enter your username : ";
	cin>>name;

	sf::Http http("http://localhost/", 8080);
			
	sf::Http::Request request1;
	request1.setMethod(sf::Http::Request::Post);
	request1.setUri("/player");
	request1.setHttpVersion(1, 0);
	request1.setField("name","free");
	string body="{\"req\" : \"POST\", \"name\":\"" + name + "\", \"free\":true}"; 
	request1.setBody(body);
			
	sf::Http::Response response1 = http.sendRequest(request1);

	Json::Reader jsonReader;
	Json::Value rep1;
    if(jsonReader.parse(response1.getBody(),rep1)){
		int playerId=rep1["id"].asInt();
		cout<<"You joined the game successfully."<<endl;
		cout<<"Your ID is : "<<playerId<<endl << "\n";

		cout<< "List of players in the game : "<<endl;
		for(int j=1; j<=playerId; j++){
            sf::Http::Request request2;
            request2.setMethod(sf::Http::Request::Get);
            string uri="/player/"+ to_string(j);
                        
            request2.setUri(uri);
            request2.setHttpVersion(1, 0);
            request2.setField("name","free");

            sf::Http::Response response2 = http.sendRequest(request2);
            Json::Reader jsonReader2;
            Json::Value rep2;
                    
            if (jsonReader.parse(response2.getBody(), rep2)){	
                string name=rep2["name"].asString();
                cout<<"	-"<<name<<endl;		
            }
        }	

        cout<<"Press d and then enter to disconnect from the server.\n"<<endl;
        while(getchar()!='d'){
            int playerNbr=0;
            while(playerNbr!=2){
                sleep(1);
                for(int k=1; k<=15; k++){
                    sf::Http::Request request5;
                    request5.setMethod(sf::Http::Request::Get);
                    string uri="/player/"+ to_string(k);
                    request5.setUri(uri);
                    request5.setHttpVersion(1, 0);
                    request5.setField("name","free");
                                
                    sf::Http::Response response5 = http.sendRequest(request5);
                                
                    Json::Reader jsonReader5;
                    Json::Value rep5;
                                
                    if (jsonReader.parse(response5.getBody(), rep5)){
                        playerNbr++;
                                    
                    }
                }

            }
        }
				
	
        sf::Http::Request request3;
        request3.setMethod(sf::Http::Request::Post);
        string uri2="/player/"+ to_string(playerId);
        request3.setUri(uri2);
        request3.setHttpVersion(1, 0);
        request3.setField("name","free");
        string body3="D"; 
        request3.setBody(body3);
        http.sendRequest(request3);
        cout<<""<<endl;
        cout<<"Player "<< playerId << " has been deleted."<<endl;
        cout<<""<<endl;
                
        cout<< "List of remaining players : "<<endl;
        for(int k=1; k<=15; k++){	
            sf::Http::Request request4;
            request4.setMethod(sf::Http::Request::Get);
            string uri="/player/"+ to_string(k);
            request4.setUri(uri);
            request4.setHttpVersion(1, 0);
            request4.setField("name","free");
                        
            sf::Http::Response response4 = http.sendRequest(request4);
                        
            Json::Reader jsonReader4;
            Json::Value rep4;
                        
                        
            if (jsonReader.parse(response4.getBody(), rep4)){
                string nom4=rep4["name"].asString();
                cout<<"	-"<<nom4<<endl;
            }
        }
    }
	else{
	    cout<<"No more spot left. The maximum number of players is limited to 2."<<endl;
	}

}