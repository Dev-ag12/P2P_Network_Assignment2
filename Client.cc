#include "Client.h"
using namespace std;
using namespace omnetpp;
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <queue>
#include <iostream>
#include <ctime>
#include <algorithm>
Define_Module(Client);
//
//void Client::initialize()
//{
//    cMessage *msg = new cMessage("deepanshu");
//
//    // Iterate over all gates and send the message to each server
//    for (int i = 0; i < gateSize("out"); i++) {
//        send(msg->dup(), "out", i); // Duplicate the message to send a copy to each server
//    }
//
//    delete msg; // Delete the original message to prevent memory leaks
//}
//

bool first=true;
int counter=0;

int part=0;
int k=0;
vector<int>clientNo;
vector<int> Gateidx;
std::map<int, int> Clientid;
int task=1;


void Client::initialize()
{
    int n = par("totalServers").intValue();
    int m = par("totalClients").intValue();

    int gateCount = n;
    std::vector<cMessage *> msgVector;

    cMessage *msg = new cMessage("deeepanshu");


    int partSize = strlen(msg->getName()) / gateCount; // Calculate the size of each part


    // Divide the message into parts and store them in the vector
    for (int i = 0; i < gateCount; i++) {
        // Calculate the start and end index for the current part
        int startIdx = i * partSize;
        int endIdx = (i == gateCount - 1) ? strlen(msg->getName()) : (i + 1) * partSize;

        // Extract the substring for the current part
        std::string partName = std::string(msg->getName()).substr(startIdx, endIdx - startIdx);

        cout<<endl<<partName<<endl;

        // Create a new message with the substring as the name
        cMessage *partMsg = new cMessage(partName.c_str());

        // Store the part message in the vector
        msgVector.push_back(partMsg);
    }
    first=0;


    // Iterate over the vector and send each part to the corresponding gate
    for (int i = 0; i < gateCount; i++) {
        int lowerBound = 0;
           int upperBound = n-1;
           int numNumbers = n/2+1; // Number of unique random numbers to generate

           // Seed the random number generator
           std::random_device rd;
           std::mt19937 gen(rd());

           // Define the distribution
           std::uniform_int_distribution<> distribution(lowerBound, upperBound);

           // Set to store unique random numbers
           std::set<int> uniqueNumbers;

           // Generate unique random numbers
           while (uniqueNumbers.size() < numNumbers) {
               int randomNumber = distribution(gen);
               uniqueNumbers.insert(randomNumber);
           }

           // Print the unique random numbers
           vector<int> randomNo;
           for (int number : uniqueNumbers) {
               randomNo.push_back(number);
           }

        for(auto j : randomNo){



        send(msgVector[i]->dup(), "out", j%n);



    }
}
}

vector<int> findIndexesOfHighestK(const std::vector<int>& nums, int k) {
    // Create a vector of pairs to store the value-index pairs
    vector<pair<int, int>> valueIndexPairs(nums.size());

    // Populate the vector with value-index pairs
    for (int i = 0; i < nums.size(); ++i) {
        valueIndexPairs[i] = std::make_pair(nums[i], i);
    }

    // Sort the vector of pairs based on values in descending order
    std::sort(valueIndexPairs.begin(), valueIndexPairs.end(), std::greater<std::pair<int, int>>());

    // Extract the indexes of the highest k values
    std::vector<int> indexes;
    for (int i = 0; i < k; ++i) {
        indexes.push_back(valueIndexPairs[i].second);
    }

    return indexes;
}

void Client::handleMessage(cMessage *msg)
{
    int n = par("totalServers").intValue();
    int m = par("totalClients").intValue();
    ClientMessage *clientMsg = dynamic_cast<ClientMessage *>(msg);
    gossipMessage *gossipMsg = dynamic_cast<gossipMessage *>(msg);
    if (clientMsg && task==1){
        task+=1;
        vector<int> NEW=clientMsg->arr;
        int id=clientMsg->ID;
        time_t t=clientMsg->time;

        std::stringstream ss;
        char buffer[80]; // Buffer to store the formatted time
        struct tm* timeinfo = localtime(&t); // Convert time_t to tm structure

        // Format the time using strftime
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Store the formatted time in the stringstream
        ss << buffer;

        // Get the string representation of the time
        std::string strTime = ss.str();

        string gosipString=strTime+" "+to_string(id);



//        gossip when message not in ML
//        if(ML.find()!=ML.end())
//        {
//            for(int i=n;i<n+m;i++)
//            {
//                gossip_message(s,i);
//            }
//        }

        vector<int> score(n,0);
        for(int i=0;i<n;i++)
        {
            score[i]+=NEW[i];
        }
        for(int i=0;i<n;i++)
        {
            score[i]+=res[i];
        }
        for(int i=0;i<n;i++)
        {
            score[i]/=m;
        }
        for(auto i : NEW){
            gosipString+=" ";
            gosipString+=to_string(i);}

        cout<<"Gossiped Message is "<<gosipString<<endl;


        cMessage *msg = new cMessage("MynameisLiXiao");
        vector<int>topserver=findIndexesOfHighestK(score,n/2+1);




            int gateCount = n;
            std::vector<cMessage *> msgVector;




            int partSize = strlen(msg->getName()) / gateCount; // Calculate the size of each part


            // Divide the message into parts and store them in the vector
            for (int i = 0; i < gateCount; i++) {
                // Calculate the start and end index for the current part
                int startIdx = i * partSize;
                int endIdx = (i == gateCount - 1) ? strlen(msg->getName()) : (i + 1) * partSize;

                // Extract the substring for the current part
                std::string partName = std::string(msg->getName()).substr(startIdx, endIdx - startIdx);

                cout<<endl<<partName<<endl;

                // Create a new message with the substring as the name
                cMessage *partMsg = new cMessage(partName.c_str());

                // Store the part message in the vector
                msgVector.push_back(partMsg);
            }
            first=0;


            // Iterate over the vector and send each part to the corresponding gate
            for (int i = 0; i < gateCount; i++) {
                for(auto j : topserver){
                send(msgVector[i]->dup(), "out", j%n);
                }
            }

        //        std::this_thread::sleep_for(std::chrono::seconds(50));
        }

//    else if(gossipMessage)
//    {
//        string s=gossipMessage->s;
//        int n = par("totalServers").intValue();
//        int m = par("totalClients").intValue();
//
//        if(ML.find(s)!=ML.end())
//        {
//            for(int i=n;i<n+m;i++)
//            {
//                gossip_message(s,i);
//            }
//            ML.insert(s);
//        }
//    }
    else{



    vector<vector<int>> scores;
    int n = par("totalServers").intValue();
    int m = par("totalClients").intValue();

    cGate *arrivalGate = msg->getArrivalGate();
    int gateIndex = arrivalGate->getIndex();

    vector<pair<string,int>> maj;

    maj.push_back({msg->getName(),gateIndex});
    priority_queue<string> pq;
    pq.push(msg->getName());
    string s=pq.top();

    vector<int>sco(n,0);
    for(auto i : maj)
    {

        if(i.first==s)
        {
            sco[i.second]+=1;
        }
    }

    if(res.size()==0){
        res=sco;
    }
    else{
        for(int i=0;i<n;i++){
            res[i]+=sco[i];
        }
    }

    string ress=" ";
    for(auto i : res){ress+=to_string(i);ress+=" ";}

    cout<<"Client "<< getId()<<" Receives "<<msg->getName()<<" from server "<<to_string(msg->getSenderModule()->getId())<<ress<<"\n";

    string output="Client"+to_string(getId())+".txt";
     std::ofstream outFile(output, std::ios_base::app);
     if (outFile.is_open()) {
             // Append a new line to the file
             string s="Client "+ to_string(getId())+"Receives "+msg->getName()+" from server " +to_string(msg->getSenderModule()->getId())+ress;
             outFile << s << std::endl;

             // Close the file
             outFile.close();

             std::cout << "New Output logged to file successfully." << std::endl;
         }


    server_mutex++;
    if(server_mutex == 2*n *(n/2 + 1)){
        server_mutex = 0;
        for(int j=0;j<n;j++){
           EV<<res[j]<<" ";
        }
       int ID = getId(); // Example value
       time_t currentTime = time(nullptr); // Get current time♀  gateSize("out"

       for(int i=n;i<n+m;i++)
       {
           time_t now = time(nullptr);
           int id=getId();
           send_message(res,currentTime,ID,res.size(),i);
       }
        EV<<"\n";
        EV<<getId();
        EV<<"\n";
    }
//    ClientMessage *ms = new ClientMessage();




    delete msg;
    }
}
