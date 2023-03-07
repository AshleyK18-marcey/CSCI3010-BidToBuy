#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
struct Message{
    unsigned int sent_from_id_;
    std::string message_content_;
}
class Conversation{
    public: 
        Conversation(unsigned int buyerid_, unsigned int sellerid_);

        void DisplayMessages();

        unsigned int get_buyerid();

        unsigned int get_sellerid();

        void SendMessage(Message* message);


    private:
        unsigned int buyerid_;
        unsigned int sellerid_;
        std::vector<Message*> message_history_;
}

#endif 