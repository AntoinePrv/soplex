/*
 * validation.cpp
 *
 *  Created on: 15.08.2017
 *      Author: bzfviern
 */

#include "validation.h"

namespace soplex {



bool Validation::updateExternalSolution(char* solution)
{
   validatesolution = solution;
   validate = true;
   return true;
}



bool Validation::updateValidationTolerance(Real tolerance)
{
   validatetolerance = tolerance;
   return true;
}



/// validates solution using external primal and dual reference values
bool Validation::validateSolveReal(SoPlex* soplex)
{
   bool passedValidation = true;
   std::string reason = "";
   Real objViolation = 0.0;
   Real maxBoundViolation = 0.0;
   Real maxRowViolation = 0.0;
   Real maxRedCostViolation = 0.0;
   Real maxDualViolation = 0.0;
   Real sumBoundViolation = 0.0;
   Real sumRowViolation = 0.0;
   Real sumRedCostViolation = 0.0;
   Real sumDualViolation = 0.0;

   char* solstr = validatesolution;
   Real sol;
   std::ostream& os = soplex->spxout.getStream(SPxOut::INFO1);

   if( strncmp(solstr, "+infinity", 9 ) == 0 )
      sol = DEFAULT_INFINITY;
   else if ( strncmp(solstr, "-infinity", 9) == 0 )
      sol = -DEFAULT_INFINITY;
   else
   {
      char* tailptr;
      sol = strtod(solstr, &tailptr);
      if (*tailptr) {
         //conversion failed because the input wasn't a number
      }
   }

   objViolation = spxAbs(sol - soplex->objValueReal());
   if( ! EQ(objViolation, 0.0, validatetolerance) )
   {
      passedValidation = false;
      reason += "Objective Violation; ";
   }
   if( SPxSolver::OPTIMAL == soplex->status() )
   {
      soplex->getBoundViolationReal(maxBoundViolation, sumBoundViolation);
      soplex->getRowViolationReal(maxRowViolation, sumRowViolation);
      soplex->getRedCostViolationReal(maxRedCostViolation, sumRedCostViolation);
      soplex->getDualViolationReal(maxDualViolation, sumDualViolation);
      if( ! LE(maxBoundViolation, validatetolerance) )
      {
         passedValidation = false;
         reason += "Bound Violation; ";
      }
      if( ! LE(maxRowViolation, validatetolerance) )
      {
         passedValidation = false;
         reason += "Row Violation; ";
      }
      if( ! LE(maxRedCostViolation, validatetolerance) )
      {
         passedValidation = false;
         reason += "Reduced Cost Violation; ";
      }
      if( ! LE(maxDualViolation, validatetolerance) )
      {
         passedValidation = false;
         reason += "Dual Violation; ";
      }
   }

   os << "\n";
   os << "Validation          :";
   if(passedValidation)
      os << " Success\n";
   else
   {
      reason[reason.length()-2] = ']';
      os << " Fail [" + reason + "\n";
   }
   os << "   Objective        : " << std::scientific << std::setprecision(8) << objViolation << std::fixed << "\n";
   os << "   Bound            : " << std::scientific << std::setprecision(8) << maxBoundViolation << std::fixed << "\n";
   os << "   Row              : " << std::scientific << std::setprecision(8) << maxRowViolation << std::fixed << "\n";
   os << "   Reduced Cost     : " << std::scientific << std::setprecision(8) << maxRedCostViolation << std::fixed << "\n";
   os << "   Dual             : " << std::scientific << std::setprecision(8) << maxDualViolation << std::fixed << "\n";

   return passedValidation;
}



} /* namespace soplex */
