/* -------------- position.cc -------------- *
 * Contains the position calculation for the *
 * monitoring system. Could be used for other*
 * codes requiring injector positions.       *
 *                                           *
 * SOFTWARE REQUIRED:                        *
 * ---> ROOT                                 *
 *                                           *
 *                jmmcelwee1@sheffield.ac.uk *
 * ------------------------- J. McElwee ---- */

#include <string>
#include <iostream>

float injector(std::string inj){
  
  float position = 0.0;
  if (inj == "B1") position = 1232.5;
  else if (inj == "B2") position = 595.95;
  else if (inj == "B3") position = -40.35;
  else if (inj == "B4") position = -605.95;
  else if (inj == "B5") position = -1242.25;
  else {
    std::cout << "[ERROR] Incorrect injector. Please enter B1-5." << std::endl;
  } 
  return position;
}


float distance(float pmt, float injector){
  
  float dist;
  dist = pmt - injector;
  return dist;
}
