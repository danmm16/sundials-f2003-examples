/*
 * -----------------------------------------------------------------
 * Programmer(s): Daniel Reynolds @ SMU
 * -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2023, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * This file (companion of fsunlinsol_spbcgs.h) contains the
 * implementation needed for the Fortran initialization of SPBCGS
 * linear solver operations.
 * -----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include "fsunlinsol_spbcgs.h"

/* Define global linsol variables */

SUNLinearSolver F2C_CVODE_linsol;
SUNLinearSolver F2C_IDA_linsol;
SUNLinearSolver F2C_KINSOL_linsol;
SUNLinearSolver F2C_ARKODE_linsol;
SUNLinearSolver F2C_ARKODE_mass_sol;

/* Declarations of external global variables */

extern SUNMatrix F2C_CVODE_matrix;
extern SUNMatrix F2C_IDA_matrix;
extern SUNMatrix F2C_KINSOL_matrix;
extern SUNMatrix F2C_ARKODE_matrix;
extern SUNMatrix F2C_ARKODE_mass_matrix;

extern N_Vector F2C_CVODE_vec;
extern N_Vector F2C_IDA_vec;
extern N_Vector F2C_KINSOL_vec;
extern N_Vector F2C_ARKODE_vec;

/* Fortran callable interfaces */

void FSUNSPBCGS_INIT(int *code, int *pretype, int *maxl, int *ier)
{
  *ier = 0;

  switch(*code) {
  case FCMIX_CVODE:
    if (F2C_CVODE_linsol)  SUNLinSolFree(F2C_CVODE_linsol);
    F2C_CVODE_linsol = NULL;
    F2C_CVODE_linsol = SUNLinSol_SPBCGS(F2C_CVODE_vec, *pretype, *maxl);
    if (F2C_CVODE_linsol == NULL) *ier = -1;
    break;
  case FCMIX_IDA:
    if (F2C_IDA_linsol)  SUNLinSolFree(F2C_IDA_linsol);
    F2C_IDA_linsol = NULL;
    F2C_IDA_linsol = SUNLinSol_SPBCGS(F2C_IDA_vec, *pretype, *maxl);
    if (F2C_IDA_linsol == NULL) *ier = -1;
    break;
  case FCMIX_KINSOL:
    if (F2C_KINSOL_linsol)  SUNLinSolFree(F2C_KINSOL_linsol);
    F2C_KINSOL_linsol = NULL;
    F2C_KINSOL_linsol = SUNLinSol_SPBCGS(F2C_KINSOL_vec, *pretype, *maxl);
    if (F2C_KINSOL_linsol == NULL) *ier = -1;
    break;
  case FCMIX_ARKODE:
    if (F2C_ARKODE_linsol)  SUNLinSolFree(F2C_ARKODE_linsol);
    F2C_ARKODE_linsol = NULL;
    F2C_ARKODE_linsol = SUNLinSol_SPBCGS(F2C_ARKODE_vec, *pretype, *maxl);
    if (F2C_ARKODE_linsol == NULL) *ier = -1;
    break;
  default:
    *ier = -1;
  }
}


void FSUNSPBCGS_SETPRECTYPE(int *code, int *pretype, int *ier)
{
  *ier = 0;

  switch(*code) {
  case FCMIX_CVODE:
    if (!F2C_CVODE_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetPrecType(F2C_CVODE_linsol, *pretype);
    break;
  case FCMIX_IDA:
    if (!F2C_IDA_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetPrecType(F2C_IDA_linsol, *pretype);
    break;
  case FCMIX_KINSOL:
    if (!F2C_KINSOL_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetPrecType(F2C_KINSOL_linsol, *pretype);
    break;
  case FCMIX_ARKODE:
    if (!F2C_ARKODE_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetPrecType(F2C_ARKODE_linsol, *pretype);
    break;
  default:
    *ier = -1;
  }
}


void FSUNSPBCGS_SETMAXL(int *code, int *maxl, int *ier)
{
  *ier = 0;

  switch(*code) {
  case FCMIX_CVODE:
    if (!F2C_CVODE_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetMaxl(F2C_CVODE_linsol, *maxl);
    break;
  case FCMIX_IDA:
    if (!F2C_IDA_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetMaxl(F2C_IDA_linsol, *maxl);
    break;
  case FCMIX_KINSOL:
    if (!F2C_KINSOL_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetMaxl(F2C_KINSOL_linsol, *maxl);
    break;
  case FCMIX_ARKODE:
    if (!F2C_ARKODE_linsol) {
      *ier = -1;
      return;
    }
    *ier = SUNLinSol_SPBCGSSetMaxl(F2C_ARKODE_linsol, *maxl);
    break;
  default:
    *ier = -1;
  }
}


void FSUNMASSSPBCGS_INIT(int *pretype, int *maxl, int *ier)
{
  *ier = 0;
  if (F2C_ARKODE_mass_sol)  SUNLinSolFree(F2C_ARKODE_mass_sol);
  F2C_ARKODE_mass_sol = NULL;
  F2C_ARKODE_mass_sol = SUNLinSol_SPBCGS(F2C_ARKODE_vec, *pretype, *maxl);
  if (F2C_ARKODE_mass_sol == NULL) *ier = -1;
}


void FSUNMASSSPBCGS_SETPRECTYPE(int *pretype, int *ier)
{
  *ier = 0;
  if (!F2C_ARKODE_mass_sol) {
      *ier = -1;
      return;
  }
  *ier = SUNLinSol_SPBCGSSetPrecType(F2C_ARKODE_mass_sol, *pretype);
}


void FSUNMASSSPBCGS_SETMAXL(int *maxl, int *ier)
{
  *ier = 0;
  if (!F2C_ARKODE_mass_sol) {
      *ier = -1;
      return;
  }
  *ier = SUNLinSol_SPBCGSSetMaxl(F2C_ARKODE_mass_sol, *maxl);
}
