#ifndef DRIVER_H
#define DRIVER_H
#include "Product.h"
#include "Conversation.h"
//#include "Users.h"
#include "ProductFactory.h"


class Driver
{
public:
	static Driver *GetInstance()
	{
		if (DriverPtr == NULL) // no instance created yet
		{
			DriverPtr = new Driver();
			return DriverPtr;
		}
		else
		{
			return DriverPtr;
		}
	}


	// Delete the methods we don't want
	Driver(Driver const &) = delete;		 // copy constructor
	void operator=(Driver const &) = delete; // assignment operator
	
	~Driver();

	// void PostProductForSale(Product *newProduct);

	// void OpenBid(Product *product);

	// void CloseBid(Product *product);

	// void DisplaySimilarProductsSold(const unsigned int product_id);

	void CreateConversation(User *buyer, User *seller);

	void handleConversing(User *userPtr);

	void DisplayActiveProducts(bool specific_to_user, User* seller);

	void DisplayInactiveProducts(User* seller);

	void HandleProductCreation();

	void HandlePlaceBid();

	void HandleOpenCloseBid();

	// void DisplayBoughtProducts(User* buyer);

	void DisplayCurrentBids(User* Buyer);

	void DisplayUsers();

	std::vector<User*> get_users(){ return users_;};

	void DisplaySoldProducts(bool specific_to_user, User *Seller);

	bool UserExists(std::string name);

	void MainLoop();

	void signIn();

	void OverviewSeller(User* Seller);

	void OverviewBuyer(User* Buyer);
	
	bool IsRunning() { return running_; };

	void UpdateUserCsv();

	void UpdateProductsCsv();

private:
	static Driver *DriverPtr;
	Driver(); // private constructor
	std::vector<Conversation *> conversations_;
	std::vector<Product *> unsold_products_;
	std::vector<Product *> sold_products_;
	std::vector<User*> users_;
	User *active_user_;

	bool running_ = true;
}; // class Driver

#endif // Driver_H
