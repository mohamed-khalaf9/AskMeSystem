#include "UserModelView.h"
#include<iostream>


UserModelView::UserModelView() {
}
void UserModelView::Print(UserModel& user)const {
    std::cout << "User " << user.get_user_id() << ", " << user.get_user_name() << " " << user.get_password() << ", " << user.get_name() << ", " << user.get_email() << "\n";
}
void UserModelView::listUserNameId(const UserModel& user)const {
    std::cout << "ID: " << user.get_user_id() << "\t\tName: " << user.get_name() << "\n";
}