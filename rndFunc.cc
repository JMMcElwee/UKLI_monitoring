/* ---------------- rndFunc.cc ---------------- *    
 * Random code required for running the SK      * 
 * monitoring system. This can probably be used * 
 * for other purposes too, as currently it only * 
 * converts char arrays to strings.             * 
 * SOFTWARE REQUIRED:                           *  
 *                                              * 
 *                   jmmcelwee1@sheffield.ac.uk * 
 * ---------------------------- J. McElwee ---- */

#include <string>

std::string convertToString(char *arr){

  std::string str = "";
  int arr_size = sizeof(arr)/sizeof(char);

  for (int i=0; i < arr_size; i++){
    str += arr[i];
  }

  return str;

}
