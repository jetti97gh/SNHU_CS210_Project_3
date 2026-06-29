# SNHU CS210 Project Three Reflection

## Summarize the project and what problem it was solving.
Project three involved the Corner Grocer Item Tracking program. The program solved the problem of determining how an item was sold during the day. Sales data was evaluated by analyzing a daily sales file. 
The program allowed the user to search for a specific item, display frequency of all items sold, and display a histogram of all item frequencies. A backup file is created with all menu actions except when exiting.

## What did you do particularly well?
One thing I did particularly well was organizing the program using a GroceryItem class and a map data structure. The GroceryItem class stored each object’s name and quantity. The map allowed object names to be connected with their sales frequency. I also added menu validation, file open checks, formatted output, and memory cleanup for dynamically allocated objects.

## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
One area where I could enhance the code would be to move menu items into thier own functions. This would make the program easier to maintain and test. 

## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
The most challenging aspect of this project was working with maps and pointers. I had to understand how to insert new GroceryItem objects, update existing quantities, and properly release memory when rebuilding inventories. I overcame this by reviewing course resources, testing small sections of code independent of the project, and using compiler warnings and errors. Going forward, my support network includes course resources, C++ documentation, instructor instruction (instructional videos), and tutoring resources.

## What skills from this project will be particularly transferable to other projects or course work?
The skills from this project that will transfer to other coursework include reading and writing files, using maps, designing classes, validating input, and organizing code into reusable functions.

## How did you make this program maintainable, readable, and adaptable?
I made the program maintainable, readable, and adaptable by using descriptive function and variable names, constants for menu choices, and separate files for the class definition and implementation. The use of GroceryItem class also makes the program easier to expand if more program features need to be added.
