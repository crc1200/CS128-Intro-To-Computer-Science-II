#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <set>
#include <string>
#include <vector>
#include "timeslot.hpp"
#include "doctor.hpp"
#include "appointment.hpp"

class Hospital {
  public:
    Hospital() = default;
    void AddDoctor(Doctor& d);
    void RemoveAppointment(TimeSlot time, std::string patient);
    void AddAppointment(TimeSlot time, std::string patient);
    Doctor* GetAvailableDoctor(TimeSlot time);





  private:
    std::vector<Doctor*> doctors_;
    std::vector<Appointment> appointments_;


};

#endif