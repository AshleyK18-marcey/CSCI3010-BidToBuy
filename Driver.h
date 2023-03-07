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
 private:
 	Driver();  // private constructor

  
};  // class Driver

#endif  // Driver_H
