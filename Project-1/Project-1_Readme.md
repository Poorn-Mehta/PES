**Project_1_R-P**

This is the public repository owned by Rushi James Macwan and Poorn Mehta for the ECEN 5813 (Fall-2018) Project 1. Currently working on Sprint 1. Access from linux.

Some information regarding Sprint 1:

In this Github repository, we have tried to incorporate the basic features for the user as were discussed in the class. On executing the Project_1 file in the command window on Linux, we are able to provide the user with a welcome statement followed by a prompt to seek help. If the user puts a valid keyword (at this stage the user is only expected to type "help" or "help.exit" as valid keywords) then the executable program returns more information on the keyword which can be an executable instruction or a piece of necessary information depending upon the type of the application. If the user enters an invalid keyword then the system will return a response stating the entered keyword as invalid. Furthermore, if the user enters "help.exit" as the keyword then the system responds with a message on further steps to end the execution of the make file. To end this execution, the user can simply enter "exit" as the keyword which brings the user back to the command window operations considering that the while loop is exited.

Thanks.

Sincerely,

Team (Rushi and Poorn)

Update - 1PM - 10/4/2018

Everything is working perfectly on terminal as well as windows IDE. Only patternverify function is yet to deploy. Time was consumed in developing a smooth User Interface.

Update on Project as of 10/4/2018

2 things are yet to implement - pattern verify and bound checking. Raw functions are ready.

Every other functions works perfectly in Windows Dev C (gcc) however, in linux, it throws an error - segmentation fault (core dumped) - we have no idea about this. Currently, we are trying to resolve this error. Once it is solved, we will integrate bound checking and pattern verify.

It tooks us this much of time because the user interface is pretty decent.

It accepts only valid arguments in all input cases (rejecting non decimal, non hex values, commands with extra or less parameters, misspellings etc.)

Also, it accepts arguments and commands in two formats: (1) If you just type command which accepts arguments, and then press enter, it will keep on prompting until it has received all valid parameters (2) You can even call the function with parameters, by simply putting space in between - such as memwrite

Before 11.59 PM as on 10/4/2018:

We have overcome all the previous limitations and have implemented extended UI functionalities which are not limited to but are inclusive of the following:

    Memory allocation
    Memory freeing
    Memory read
    Memory write
    Memory inversion
    Pattern generation
    Pattern verification
    (Internal function) Time measurement in all major executions
    (Internal function) Boundary check
    (Internal function) Null-pointer check
    (Internal function) Pre-clearing of pointer after memory allocation
    (Internal function) Error-checks for user-specified data entry

(Extended functionalities that we may include as soon as possible:)

    Memory clear operation
    Memory Swap Function
    Memory Reallocation (Memory free + Memory allocation + Memory clear operation)
    Memory Copy Function
    Memory Math Operations
    Memory Math Lighthouse Function (provides results for all the math operations for two data points and stores at two user-specified addresses within the allocated spectrum)
    Memory Statistical Operations in real-time (performs various statistical measurements upon successful operation of either Memory Math Operations or Memory Math Lighthouse Function)

This is the brief and concise report on our existing status.

Thanks.

Sincerely,

Team (Rushi & Poorn)
