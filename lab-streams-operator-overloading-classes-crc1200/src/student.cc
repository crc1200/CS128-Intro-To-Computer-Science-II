#include "student.hpp"

#include <stdexcept>
#include "course.hpp"
#include <ostream>
#include <iostream>

std::string Student::GetName() const {
    return name_;
}
std::string Student::GetUIN() const {
    return uin_;
}
std::string Student::GetNetId() const {
    return net_id_;
}
std::string Student::GetMajor() const {
    return major_;
}
bool Student::HasGraduated() const {
    return graduated_;
}

int Student::GetCredits() const {
    int count = 0;
    for (unsigned int i = 0; i < courses_.size(); i++) {
        count+= courses_[i].credits;
    }
    return count;
}

const std::vector<Course>& Student::GetCourses() const {
    return courses_;
}

std::string Student::PrintCourses() const{
    std::string result;
    for (unsigned int i = 0; i < courses_.size(); i++) {
        result += courses_.at(i).name + ", ";
    }
    if (result.size() > 3) {
        result.erase(result.size() - 2); 
    }
    return result;
}

std::string Student::PrintGrad() const{
    if (graduated_) {
        return "True";
    }
    return "False";
}

void Student::SetName(std::string name) {
    name_ = name;
}

void Student::SetMajor(std::string major) {
    major_ = major;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Name: " << s.GetName() << '\n';
    os << "UIN: " << s.GetUIN() << '\n';
    os << "Net Id: " << s.GetNetId() << '\n';
    os << "Major: " << s.GetMajor() << '\n';
    os << "Credits: " << s.GetCredits() << '\n';
    os << "Courses: " << s.PrintCourses() << '\n';
    os << "Graduated: " << s.PrintGrad();
    return os;
}

bool Student::AddCourse(Course c) {
    for (unsigned int i = 0; i < courses_.size(); i++) {
        if (courses_[i].name == c.name) {
            return false;
        }
    }
    courses_.push_back(c);
    return true;
}

void Student::Graduate() {
    int count = 0;
    for (unsigned int i = 0; i < courses_.size(); i++) {
        count+= courses_[i].credits;
    }
    if (count >= min_credits_grad_) {
        graduated_ = true;
    }
}

Student::Student(std::string name, std::string uin, std::string net_id) : name_{name}, uin_{uin}, net_id_{net_id} {
    major_ = "Undeclared";
    std::vector<Course> course;
    courses_ = course;
    graduated_ = false;
}

Student::Student(std::string name, std::string uin, std::string net_id, std::string major, std::vector<Course> course, bool graduated) : name_{name}, uin_{uin}, net_id_{net_id}, major_{major}, courses_{course}, graduated_{graduated} {}


