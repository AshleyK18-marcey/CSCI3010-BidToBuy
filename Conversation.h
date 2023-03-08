#ifndef CONVERSATION_H
#define CONVERSATION_H
#include <string>
#include "Users.h"

struct Message{
    User sent_from_;
    std::string message_content_;
    
};

class Conversation{
    public: 
        Conversation(unsigned int buyerid_, unsigned int sellerid_);

        void DisplayMessages();

        unsigned int get_buyerid();

        unsigned int get_sellerid();

        void SendMessage(std::string message);



    private:
        unsigned int buyerid_;
        unsigned int sellerid_;
        std::vector<Message*> message_history_;
};

#endif // CONVERSATION_H header guard