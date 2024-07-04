#ifndef __ASSIGNMENT_A_H_
#define __ASSIGNMENT_A_H_

#include <omnetpp.h>
#include<vector>
using namespace std;
#include <iostream>
#include <chrono>
#include <ctime>
#include <set>

using namespace omnetpp;

/**
 * TODO - Generated class
 */


class ClientMessage:public cMessage
{
     public:
         vector<int> arr;
         int arr_len;
         int ID;
         time_t time;

};

class gossipMessage:public cMessage
{
     public:
         string s;

};


class Client : public cSimpleModule
{

    public:
    int server_mutex = 0;
    set<string>ML;
    vector<int> res;
    void send_message(std::vector<int> arr, time_t time, int ID, int arr_len, int server_id) {
        ClientMessage *newm = new ClientMessage();
        newm->arr = arr;
        newm->arr_len = arr_len;
        newm->time=time;
        newm->ID=ID;
        send(newm,  "out", server_id);
    }

    void gossip_message(string s, int server_id) {
        gossipMessage *newm = new gossipMessage();
            newm->s = s;

            send(newm,  "out", server_id);
        }

   protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

#endif
