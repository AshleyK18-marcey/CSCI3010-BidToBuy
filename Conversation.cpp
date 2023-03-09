#include "Conversation.h"

Conversation::Conversation(User* buyer, User* seller) {
    this->buyerPtr_ = buyer;
    this->sellerPtr_ = seller;
}

void Conversation::SendMessage(std::string message, User* senderPtr) {
    if (message.length() == 0 || (senderPtr != this->buyerPtr_ && senderPtr != sellerPtr_))
    {
        return;
    }
    Message tempMesg;
    tempMesg.message_content_ = message;
    tempMesg.sent_from_ = senderPtr;

    this->message_history_.push_back(tempMesg);
}

void Conversation::DisplayMessages() {
    std::cout << "Buyer: " << buyerPtr_->get_name() << ", Seller: " << sellerPtr_->get_name() << std::endl;
    for (unsigned int i = 0; i < message_history_.size(); i++)
    {
        std::cout << message_history_.at(i).sent_from_->get_name() << ": " << message_history_.at(i).message_content_ << std::endl;
    }
    
}

bool Conversation::UserPresent(User* user) {
    if (user == this->buyerPtr_ || user == this->sellerPtr_)
    {
        return true;
    } else {
        return false;
    }
    
}