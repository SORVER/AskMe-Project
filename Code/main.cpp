#include <iostream>
#include <bits/stdc++.h>
#include <cstdint>
#include <cstring>
#define ll long long


using namespace std;

class User;
class Que;
vector <User> users;
vector <Que> questions;
int maxUsers, maxQuestions;
void Start();
int validate(string ich);
void updateQuestions();
void updateUsers();
class Que
{
private :
    int id;
    int from;
    int to;
    string q;
    string ans;
public:
    Que(int id,int from,int to,string q)
    {
        this->id = id;
        this->from =from;
        this->to = to;
        this->q =q;


    }
    int getId()
    {
        return id;
    }
    string getQ()
    {
        return q;
    }
    string getAns()
    {
        return ans;
    }
    string setAns(string ans){
         this->ans =ans;
    }
    int getTo()
    {
        return to;
    }
    int getFrom()
    {
        return from;
    }
    void setId(int id){
         this-> id = id;
    }
    void setFrom(int from){
         this->from = from;
    }
    void setTo(int to){
        this->to = to;
    }

};
class User
{
private :
    int id;
    string username;
    string password;
    string email;

public:
    User(int id, string username,string password, string email)
    {
        this->id = id;
        this-> username = username;
        this->password = password;
        this->email = email;
    }
    int getId()
    {
        return id;
    }
    string getUsername()
    {

        return username;
    }
    string getPassword()
    {
        return password;
    }

    void ask() const
    {

        cout << "Enter the user id to send the question: ";
        string iuserId ;
        getline(cin, iuserId);
        int userId = validate(iuserId);
        if(userId == -1){
            cout << "Wrong input, try again\n";
            ask();
            return;
        }
        bool flag = false;
        for(int i =0 ; i< users.size(); i++)
        {
            if(users[i].getId() == userId) flag = true;
        }
        if(flag)
        {
            cout << "Enter your Question : ";
            string question ;
            getline(cin, question);
            cout << "\n";

            maxQuestions++;
            Que yourQ(maxQuestions,id,userId,question);
            questions.push_back(yourQ);
            updateQuestions();

        }
        else
        {

            cout << "No user with this id to ask\n";


        }

    }
    void answer() const
    {
        cout << "Enter the question id to answer: ";
        string iqueId ;
        getline(cin, iqueId);
        int queId = validate(iqueId);
        if(queId == -1)
        {
            cout << "Wrong input,try again\n";
            answer();
            return;
        }


        int queInd = -1;
        for(int i =0 ; i< questions.size(); i++)
        {
            if(questions[i].getId() == -1)
            {
                continue;
            }
            if(questions[i].getTo() == id && questions[i].getId() == queId)
            {
                queInd =i;
            }
        }
        if(queInd != -1)
        {
            cout << "question: " << questions[queInd].getQ() << "\n";
            cout << "Enter your answer : ";
            string answer ;
            getline(cin, answer);
            cout << "\n";

            questions[queInd].setAns(answer);
            updateQuestions();

        }
        else
        {

            cout << "No question with this id to answer\n";


        }
    }
    void printTo() const
    {
        int counter = 0;
        for(int i = 0 ; i< questions.size(); i++)
        {
            if(questions[i].getTo() == id)
            {

                if(questions[i].getId() == -1)continue;
                cout << "question -id " <<  questions[i].getId() <<": " << questions[i].getQ() << "   Ans: " << questions[i].getAns() << "\n";
                counter++;
            }
        }
        if(counter == 0)cout << "No such Questions\n";

    }
    void printFrom() const
    {
        int counter = 0;
        for(int i = 0 ; i< questions.size(); i++)
        {
            if(questions[i].getFrom() == id)
            {

                if(questions[i].getId() == -1)continue;
                cout << "question -id " <<  questions[i].getId() <<": " << questions[i].getQ() << "   Ans: " << questions[i].getAns() << "\n";
                counter++;
            }
        }
        if(counter == 0)cout << "No such Questions\n";

    }
    void deleteQinbox() const
    {

        cout << "Enter the question id to be deleted: ";
        string iqId; getline(cin ,iqId);
         int qId = validate(iqId);
          if(qId == -1){
            cout << "Wrong input, try again\n";
            return;
          }

         bool flag = false;
        for(int i =0 ; i<questions.size();i++){
            if(questions[i].getTo() == id && qId == questions[i].getId()){
                questions[i].setId(-1), questions[i].setFrom(-1), questions[i].setTo(-1);
                flag = true;
            }
        }
       if(!flag) cout << "No such a question with that id you have recived \n";
        else cout << "Question with id " << qId << " deleted\n";

      updateQuestions();

    }
};


int validate(string ich)
{
    int ch;
    try
    {
        ch = stoi(ich); // Throw an exception when a problem arise
    }
    catch(const std::exception& e)
    {
        cout << "try again\n";
        return -1;
    }
    return ch;
}

void printUsers(){

   for(int i = 0; i < users.size();i++){

    cout << "username : "<<users[i].getUsername() << " id : " << users[i].getId() << "\n";
   }


}
void printQues(){
    bool flag =false;
   for(int i = 0; i < questions.size();i++){
    flag= true;
    cout <<"Question-id  " <<questions[i].getId()  << ": "<< questions[i].getQ() << " Ans : " << questions[i].getAns() << "\n";
   }

  if(!flag) cout << "No such questions\n";

}
void menu(const User & theUser)
{
    cout << "1- Print questions from me\n"
         << "2- Print questions to me\n"
         << "3- Answer a question\n"
         << "4- Delete question\n"
         << "5- Ask question\n"
         << "6- List of Users\n"
         << "7- Feed\n"
         << "8- Logout\n";
    string ich ;
    getline(cin,ich);

    int ch =validate(ich);
    switch(ch)
    {
    case 1:
        theUser.printFrom();
        menu(theUser);
        break;
    case 2:
        theUser.printTo();
        menu(theUser);
        break;
    case 3:
        theUser.answer();
        menu(theUser);
        break;
    case 4:
        theUser.deleteQinbox();
        menu(theUser);
        break;
    case 5:
         theUser.ask();
         menu(theUser);
        break;
    case 6:
           printUsers();
           menu(theUser);
        break;
    case 7:
          printQues();
          menu(theUser);
        break;
    case 8:
        Start();
        break;
    default:
        cout << "Wrong input, try again\n";
        menu(theUser);
        ;
    }

}
void login()
{
    cout <<  "Enter username: ";

    string username;
    getline(cin,username);
    cout << "Enter password: ";
    string password;
    getline(cin,password);


    for(int i =0 ; i<users.size(); i++)
    {

        if( users[i].getUsername() == username && users[i].getPassword() == password)
        {
            menu(users[i]);
            return;
        }
    }
    cout << "No such Username or Password, try again\n";
    Start();

}

void signUp()
{
    cout << "Enter a new username: ";
    string username;
    getline(cin,username);
    cout << "Enter a new password: ";
    string password;
    getline(cin, password);
    cout << "Enter your email: ";
    string email;
    getline(cin,email);

    for(int i =0; i < users.size(); i++)
    {
        if(username == users[i].getUsername())
        {
            cout << "Enter another username\n";
            signUp();
            return;
        }
    }
    User newUser(++maxUsers,username,password,email);
    users.push_back(newUser);
    updateUsers();
    cout << "Done\n";
    Start();

}
void Start()
{
    cout << "     1-Login   2-SignUp\n";
    string ich;
    getline(cin, ich);
    if(ich == "1")
    {
        login();
    }
    else if(ich == "2")
    {
        signUp();
    }
    else
    {

        cout << "Wrong input, try again :\n";
        Start();
    }
}
void readUsers(){
    ifstream reader("users.txt");
     if(reader.fail()){
        cout << "Error in the files\n";
        return;
     }

    string imaxUsers ;getline(reader,imaxUsers);
    maxUsers = validate(imaxUsers);
    if(maxUsers == 0){
    reader.close(); return;
    }
    string line;
    while(getline(reader,line)){
        string f = "";
        int counter =0;
        int id;
        string username;
        string password;
        for(int i =0;i < line.size();i++){
            if(line[i] == '|'){
                if(counter == 0){
                    id = validate(f);
                    f.clear();
                    counter++;
                }else{
                    username = f;
                    f.clear();
                    counter++;
                }
            }else{
            f.append(1,line[i]);
            }

        }
        password = f;

        User newUser(id,username,password, " ");
        users.push_back(newUser);

    }
    reader.close();

}
void readQuestions(){
    ifstream reader("questions.txt");
     if(reader.fail()){
        cout << "Error in the files\n";
        return;
     }
    string imaxQuestions;getline(reader,imaxQuestions);
    maxQuestions = validate(imaxQuestions);
    if(maxQuestions == 0){
    reader.close(); return;
    }
    string line;
    while(getline(reader,line)){
        string f = "";
        int counter =0;
        int id;
        string q;
        string ans;
        int to;
        int from;
        for(int i =0;i < line.size();i++){
            if(line[i] == '|'){
                if(counter == 0){
                    id = validate(f);
                    f.clear();
                    counter++;
                }else if (counter== 1){
                    from = validate(f);
                    f.clear();
                    counter++;
                } else if (counter == 2){
                     to = validate(f);
                     f.clear();
                     counter++;

                } else if (counter == 3){
                     q = f;
                     f.clear();
                     counter++;
                }
            }else{
            f.append(1,line[i]);
            }

        }
        ans = f;

        Que newQue(id,from,to,q);
        newQue.setAns(ans);
        questions.push_back(newQue);

    }
    reader.close();

}
void updateQuestions(){
    ofstream writer("questions.txt" , ios::trunc);

    writer << maxQuestions << "\n";

    for(int i = 0; i< questions.size();i++){
        writer << questions[i].getId() << "|" << questions[i].getFrom() << "|" <<questions[i].getTo() <<  "|"<<questions[i].getQ()<< "|" << questions[i].getAns() <<"\n";
    }
    writer.close();

}
void updateUsers(){
    ofstream writer("users.txt" , ios::trunc);

    writer << maxUsers << "\n";

    for(int i = 0; i< users.size();i++){
        writer << users[i].getId() << "|" << users[i].getUsername() << "|" << users[i].getPassword() << "\n";
    }
    writer.close();
}
void readFiles(){
  readQuestions();
  readUsers();
}
int main()
{
    readFiles();
    cout << " Welcome to AskMe app !!\n";
    Start();

}



