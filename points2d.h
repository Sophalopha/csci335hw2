// --> Sophie Ong
// Implementation of the Big Five
// 

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
// Place comments that provide a brief explanation of this class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation for it.

  // Zero-parameter constructor. 
  // Set size to 0.
  Points2D()
  {
    this->sequence_ = nullptr;
    this->size_ = 0;
  }

  // Copy-constructor.
  Points2D(const Points2D &rhs)
  {
    /*
      Allocate enough so, rhs can reside and then keep copying each point
    */
    this->size_ = rhs.size_;
    this->sequence_ = new std::array<Object, 2>[this->size_];
    for (size_t i = 0; i < this->size_; i++)
    {
      this->sequence_[i][0] = rhs.sequence_[i][0];
      this->sequence_[i][1] = rhs.sequence_[i][1];
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D& operator=(const Points2D &rhs)
  {
    Points2D copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  Points2D(Points2D &&rhs)
  {
    this->size_ = rhs.size_;
    this->sequence_ = rhs.sequence_;

    rhs.sequence_ = nullptr;
    rhs.size_ = 0;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=(Points2D &&rhs)
  {
    std::swap(this->size_, rhs.size_);
    std::swap(this->sequence_, rhs.sequence_);
    return *this;
  }

  ~Points2D()
  {
    delete[] this->sequence_;
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item)
  {
    /*
      Allocate for 1 point and set it
    */
    this->size_ = 1;
    this->sequence_ = new std::array<Object, 2>[1];
    this->sequence_[0][0] = item[0];
    this->sequence_[0][1] = item[1];
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.

    /* If already have sequence, delete it */
    if (this->sequence_ != nullptr) delete[] this->sequence_;

    // Allocate new sequence in memory
    this->size_ = size_of_sequence;
    this->sequence_ = new std::array<Object, 2>[this->size_];
    
    /* Just keep going until we have two tokens to read at a time */
    Object token, token2;
    for (int i = 0; input_stream >> token && input_stream >> token2; ++i)
    {
      /* Read Coordinates & Fill Tokens */
      this->sequence_[i][0] = token;
      this->sequence_[i][1] = token2;
    }

    std::cout << std::endl;
  }

  size_t size() const {
    return this->size_;
  }

  // @location: an index to a location in the given sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
    if (location >= this->size_)
    {
      abort();
    }

    return this->sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2) {

   /*
    Make a new point, allocate enough sequence so the bigger of two, c1 and c2, can reside
   */
   Points2D result;
   result.size_ = c1.size() > c2.size() ? c1.size() : c2.size();
   result.sequence_ = new std::array<Object, 2>[result.size_];

   /*
    Keep going for the smaller sequence, i < c1.size() && i < c2.size()
   */
   size_t i;
   for (i = 0; i < c1.size() && i < c2.size(); i++)
   {
     result.sequence_[i][0] = c1[i][0] + c2[i][0];
     result.sequence_[i][1] = c1[i][1] + c2[i][1];
   }

   /*
    If c1.size() was bigger, this will run
   */
   for (; i < c1.size(); i++)
   {
     result.sequence_[i][0] = c1[i][0];
     result.sequence_[i][1] = c1[i][1];
   }

   /*
    If c2.size() was bigger, this will run
   */
   for (; i < c2.size(); i++)
   {
     result.sequence_[i][0] = c2[i][0];
     result.sequence_[i][1] = c2[i][1];
   }

   return result;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2d) {
   /*
    For empty sequence, just print () and exit
   */
   if (some_points2d.size() == 0)
   {
     out << "()" << std::endl;
     return out;
   }

   /*
    Keep going till last point
   */
   for (size_t i = 0; i < some_points2d.size(); i++)
   {
     out << "(" << some_points2d[i][0] << ", " << some_points2d[i][1] << ") ";
   }

   out << std::endl;
   return out;
 }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of the sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_
