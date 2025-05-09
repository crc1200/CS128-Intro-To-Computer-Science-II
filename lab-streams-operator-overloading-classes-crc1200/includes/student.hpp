#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include "course.hpp"

class Student {
  public:
    Student(std::string name, std::string uin, std::string net_id);
    Student(std::string name, std::string uin, std::string net_id, std::string major, std::vector<Course> course, bool graduated);
    std::string GetName() const;
    std::string GetUIN() const;
    std::string GetNetId() const;
    std::string GetMajor() const;
    std::string PrintCourses() const;
    std::string PrintGrad() const;
    int GetCredits() const;
    bool HasGraduated() const;
    const std::vector<Course> & GetCourses() const;
    void SetName(std::string name);
    void SetMajor(std::string major);
    bool AddCourse (Course c);
    void Graduate();
    void Hue(int h);
  private:
    std::string name_;
    std::string uin_;
    std::string net_id_;
    std::string major_;
    
    std::vector<Course> courses_;
    bool graduated_;
    static const int min_credits_grad_ = 120;
};

std::ostream& operator<<(std::ostream& os, const Student& s);

#endif
