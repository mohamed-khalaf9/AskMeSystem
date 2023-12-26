# AskME_System
AskMe System is a file based system that manage users questions and interactions .
I have applied OOP concepts and MVC Pattern , As well as my focus to make the source code clean , The source code will be updated as I learn more advanced topics .

## Features
- AskMe is a file-based-system so all informations about the users and questions are stored in the permanent storage .
- Parallel sessions : this is a powerful feature and it was challenging for me ,it allow user to engage in concurrent sessions and every user can see all updates of all users once they are shared without waiting .
- Simple start menu : the user can do Signup by enter its (username,password,name,email and if he allow for anonymous questions or not ) ,the system will do athentication on these entered data And user can do Login by enter its (username and password) also the system will do athentication on all entered data and then the user can access the features of the system :
  - List system users : the user can see the  ID  (the system provide auto ID for each user and question)  and name of all users.
  - Ask Question : the user can ask any user by enter his ID and the system do athentication for the ID ,the question can be anonymous if the the receiver user allowed that .
  - Print questions from me : the user can see the questions that he has sent and check if the question has been answered from the receiver user or not .
  - Print questions to me : the user can see its received questions
     and if those questions are in a thread or not .
  - Answer Question : the user can answer to its received questions
     by enter the ID of the question and also the system do athentication for the ID.
  - Delete question : the user can delete any question from its recieved questions by enter its ID and the system do athentication for the ID then the question will be deleted and if this question is a parent question so the all thread will be deleted .
  - Feed : this feature display all threads , answered questions and its answers in the system and provide information about the sender user and the receiver also(in case the questions are not anonymous ).
  - logout: the user can log out from his account and back for the start menu.

## UML (Class Diagram)
You can open the picture and zoom in to see all deatials of the diagram  :)

![AskMeSystemClassDiagram](https://github.com/mohamed-khalaf9/AskMeSystem/assets/149758845/10eb2cb8-feb1-46ed-8b48-83866184b315)


