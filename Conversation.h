#ifndef CONVERSATION_H
#define CONVERSATION_H
#include <string>
#include "Users.h"

struct Message{
    User* sent_from_;
    std::string message_content_;
};

class Conversation{
    public: 
        Conversation(User* buyer, User* seller);

        void DisplayMessages();

        unsigned int get_buyerid(){ return buyerPtr_->get_userid();  };

        unsigned int get_sellerid(){ return sellerPtr_->get_userid(); };

        User* get_buyer_ptr(){ return buyerPtr_; };

        User* get_seller_ptr(){ return sellerPtr_; };

        void SendMessage(std::string message, User* senderPtr);

        bool UserPresent(User* user);

    private:
        User* buyerPtr_;
        User* sellerPtr_;
        unsigned int sellerid_;
        std::vector<Message> message_history_;
};

#endif // CONVERSATION_H header guard