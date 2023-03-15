#include "Conversation.h"
/**
    Constructor for a conversation that assigns the buyer and seller 
*/
Conversation::Conversation(User *buyer, User *seller)
{
    this->buyerPtr_ = buyer;
    this->sellerPtr_ = seller;
}

/**
    Adds the new message and adds it to the conversation 

    @param message The message that the user wants to add
    @param senderPtr pointer to the user who is sending the message
    
*/
void Conversation::SendMessage(std::string message, User *senderPtr)
{
    if (message.length() == 0 || (senderPtr != this->buyerPtr_ && senderPtr != sellerPtr_))
    {
        return;
    }
    Message tempMesg;
    tempMesg.message_content_ = message;
    tempMesg.sent_from_ = senderPtr;

    this->message_history_.push_back(tempMesg);
}

/**
   Displays the messages within the conversation between the buyer and seller
*/
void Conversation::DisplayMessages()
{
    std::cout << "Buyer: " << buyerPtr_->get_name() << ", Seller: " << sellerPtr_->get_name() << std::endl;
    for (unsigned int i = 0; i < message_history_.size(); i++)
    {
        std::cout << message_history_.at(i).sent_from_->get_name() << ": " << message_history_.at(i).message_content_ << std::endl;
    }
}

/**
    Checks that the user sending the message is involved in the conversation 

    @param user the user sending the message
*/
bool Conversation::UserPresent(User *user)
{
    if (user->get_name() == this->buyerPtr_->get_name() || user->get_name() == this->sellerPtr_->get_name())
    {
        return true;
    }
    else
    {
        return false;
    }
}