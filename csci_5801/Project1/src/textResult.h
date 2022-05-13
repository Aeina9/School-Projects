#ifndef TEXT_RESULT_H
#define TEXT_RESULT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
* @brief class that generates the output files
*/
class TextResult{
  public:

     /**
     * @brief default constructor
     */
    TextResult(){}

     /**
     * @brief file output stream
     */
    std::ofstream fileout;

    /**
     * @brief media file stream
     */
    std::stringstream mediaStream;

    /**
     * @brief audit file stream
     */
    std::stringstream auditStream;

     /**
     * @brief generates media file
     */
    void print();

    /**
     * @brief generates audit file
     */
    void printAudit();
};


#endif