# McGoogles
A restaurant called McGoogles, where there are cooks and customers, making and ordering food, respectively.

## Description
Threading code is  used to run the main file that uses McGoogles interface. The main file does not have any synchronization/locking code. The users of McGoogles implementation should not have to worry about locking/unlocking anything. They can just use the interface, and it’s the restaurant’s job to worry about safely accessing/modifying the restaurant. The McGoogles implementation will have all the locking and synchronization (and no threading!). It ensures that all variables are modified correctly and safely, and that the restaurant is never above capacity. It also ensures that all orders were fulfilled (number of orders == number of expected orders).
