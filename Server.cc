
#include "Server.h"
#include<string>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
using namespace omnetpp;

Define_Module(Server);


void Server::initialize()
{
    // TODO - Generated method body
}

void Server::handleMessage(cMessage *msg)
{


        int n = par("totalServers").intValue();

        int gateCount = n;

        int lowerBound = 0;
        int upperBound = n;

        // Seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define the distribution
        std::uniform_int_distribution<> distribution(lowerBound, upperBound);

        // Generate and print a random number
        int randomNumber = distribution(gen);


        std::string s="";
        bool sent = false;

        // Iterate through each character in the message
        for (size_t i = 0; i < strlen(msg->getName()); ++i)
        {
            char ch = msg->getName()[i];
            // Check if the character is a vowel
            if (ch == 'A' || ch == 'a' || ch == 'E' || ch == 'e' || ch == 'I' || ch == 'i' || ch == 'O' || ch == 'o' || ch == 'U' || ch == 'u')
            {
                s += ch;
            }
        }
        long treeId = msg->getTreeId();
        int serverId = getId();
        string blank=" ";
        cMessage *blankMsg = new cMessage(blank.c_str());
        if(treeId%4==serverId%4){
            cMessage *vowelMsg = new cMessage(s.c_str());

            for (int i = 0; i < gateSize("out"); i++) {
                if(vowelMsg->getName()!=msg->getName()){
                    std::ofstream outFile("serverOutput.txt", std::ios_base::app);
                    if (outFile.is_open()) {
                        // Append a new line to the file
                        string s="Malicious Node Server "+to_string(getId())+" Output "+msg->getName()+" on subtask "+msg->getName();
                        outFile << s << std::endl;

                        // Close the file
                        outFile.close();

                        std::cout << "New Output logged to file successfully." << std::endl;
                    }
                    cout<<"Malicious Node "<<"Server "<<getId()<< " Output "<<msg->getName()<<"on subtask "<<msg->getName()<<"\n";
                    send(msg->dup(), "out", i);
                }
                else{
                    std::ofstream outFile("serverOutput.txt", std::ios_base::app);
                        if (outFile.is_open()) {
                            // Append a new line to the file
                            string s="Malicious Node Server "+to_string(getId())+" Output "+blankMsg->getName()+" on subtask "+msg->getName();
                            outFile << s << std::endl;

                            // Close the file
                            outFile.close();

                            std::cout << "New Output logged to file successfully." << std::endl;
                        }
                        cout<<"Malicious Node "<<"Server "<<getId()<< " Output "<<blankMsg->getName()<<"on subtask "<<msg->getName()<<"\n";
                        send(blankMsg->dup(), "out", i);
                }
            }
        }
        else{
            cMessage *vowelMsg = new cMessage(s.c_str());
            for (int i = 0; i < gateSize("out"); i++) {
//                EV<<"Honest Node "<<"Server "<<getId()<< "Output "<<msg->getName()<<"\n";
                std::ofstream outFile("serverOutput.txt", std::ios_base::app);
                                if (outFile.is_open()) {
                                        // Append a new line to the file
                                        string s="Honest Node Server "+to_string(getId())+" Output "+vowelMsg->getName()+" on subtask "+msg->getName();
                                        outFile << s << std::endl;

                                        // Close the file
                                        outFile.close();

                                        std::cout << "New Output logged to file successfully." << std::endl;
                                    }
                cout<<"Honest Node "<<"Server "<<getId()<< " Output "<<vowelMsg->getName()<<"on subtask "<<msg->getName()<<"\n";
                send(vowelMsg->dup(), "out", i);
            }
        }



        delete msg;


}


