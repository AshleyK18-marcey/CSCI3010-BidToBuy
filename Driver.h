#ifndef DRIVER_H
#define DRIVER_H


class Driver {
public:
	
	static Driver& GetInstance() {
		// gets instantiated the first time
		static Driver instance; // guaranteed to be destroyed

		return instance;
	}

	// Delete the methods we don't want
	Driver(Driver const&) = delete; // copy constructor
	void operator=(Driver const&) = delete; // assignment operator

    std::vector<Conversation*> get_users_conversations(unsigned int userid);



    
 private:
 	Driver();  // private constructor
    std::vector<Conversation*> conversations_;
    std::vector<Product*> unsold_products_;
    std::vector<Product*> sold_products_;
    std::vector<User*> users_;
    User active_user_;

  
};  // class Driver

#endif  // Driver_H
