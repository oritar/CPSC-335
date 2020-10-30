///////////////////////////////////////////////////////////////////////////////
// pipes_algs.hpp
//
// Algorithms that solve the ecomomical pipes problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on pipes_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>

#include "pipes_types.hpp"

using std::vector;
using std::cout;
using std::endl;

namespace pipes {

// Solve the economical pipes problem for the given grid, using an exhaustive
// search algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path econ_pipes_exhaustive(const grid& setting) {
  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  
  // Compute the path length, and check that it is legal.
  const size_t total_steps = setting.rows() + setting.columns() - 2;
  assert(total_steps < 64);

  path best(setting);

  for(int bits = 0; bits < (pow(2, total_steps) - 1); bits++){
    // initialize candidate path empty
    path candidate(setting);
    for(int k = 0; k <= total_steps - 1; k++){
      int bit = (bits >> k) & 1;
      
      if(bit == 1 && candidate.is_step_valid(STEP_DIRECTION_RIGHT)){
        candidate.add_step(STEP_DIRECTION_RIGHT);
      }
      else if(candidate.is_step_valid(STEP_DIRECTION_DOWN)){
        candidate.add_step(STEP_DIRECTION_DOWN);
      }
    }

    // compare candidate with the current best path
    if(candidate.total_open() > best.total_open()){
      best = candidate;
    }
  }
  
  return best;
}
  
// Solve the economical pipes problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
path econ_pipes_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.

  using cell_type = std::optional<path>;

  //std::vector<std::vector<cell_type>> A(setting.rows(),
    //                           std::vector<cell_type>(setting.columns()));

  vector<vector<cell_type>> A(setting.rows(), vector<cell_type>(setting.columns()));

  A[0][0] = path(setting);
  assert(A[0][0].has_value());

  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {
      if (setting.get(r, c) != CELL_ROCK) {
        auto best = A[r][c];
        auto from_above = path(setting); // empty path
        auto from_left = path(setting);  // empty path

	      // complete lines for computing from_above and from_left
        if(r > 0 && !(A[r-1][c]->steps().empty())){
/*            if(setting.get(r, c - 1) != CELL_ROCK){            
            //best = *(A[r][c-1]);
            if(best->is_step_valid(STEP_DIRECTION_DOWN)){
              best->add_step(STEP_DIRECTION_DOWN);
            } */

          if(setting.get(r-1, c) != CELL_ROCK){
            from_above = *(A[r-1][c]);
            if(from_above.is_step_valid(STEP_DIRECTION_DOWN)){
              from_above.add_step(STEP_DIRECTION_DOWN);
            }
            else if(from_above.is_step_valid(STEP_DIRECTION_RIGHT)){
              from_above.add_step(STEP_DIRECTION_RIGHT);
            }
          }
        }       
        
        if(c > 0 && !(A[r][c - 1]->steps().empty())){
/*           if(setting.get(r, c - 1) != CELL_ROCK){            
            //best = *(A[r][c-1]);
            if(best->is_step_valid(STEP_DIRECTION_RIGHT)){
              best->add_step(STEP_DIRECTION_RIGHT);
            } */

          if(setting.get(r, c - 1) != CELL_ROCK){            
            from_left = *(A[r][c-1]);

            if(from_left.is_step_valid(STEP_DIRECTION_RIGHT)){
              from_left.add_step(STEP_DIRECTION_RIGHT);
            }

            else if(from_left.is_step_valid(STEP_DIRECTION_DOWN)){
              from_left.add_step(STEP_DIRECTION_DOWN);
            }
          }
        }

        if(from_above.total_open() >= from_left.total_open()){
          best = from_above;
        }
        else{
          best = from_left;
        }

/*      if(!(from_above.steps().empty()) && (from_above.total_open() >= from_left.total_open())){
          best = from_above;
        }
        else if(!(from_left.steps().empty()) && (from_left.total_open() >= from_above.total_open())){
          best = from_left;
        } */

        printf("\nBest Candidate, r:%d, c:%d :\n", r, c);
        best->print();
        printf("\n");

        A[r][c] = best;
      }
      //else{
        //A[r][c] = path(setting);
      //}
    }
  }
  
  coordinate r = setting.rows()-1;
  coordinate c = setting.columns()-1;
  cell_type * best = &(A[r][c]);

  printf("\nReturning Candidate: \n");
  A[r][c]->print();
  printf("\n");

  assert(best->has_value());
  return **best;
}

}
