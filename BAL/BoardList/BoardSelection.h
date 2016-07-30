/**
  ******************************************************************************
  * @file    BoardSelection.h
  * @brief   This file indicates which board is used.
  *******************************************************************************
  */

#ifndef BOARDSELECTION_H_
#define BOARDSELECTION_H_

#ifdef KRAKOSKI_BOARD
#include "Krakoski.h"
#endif

#ifdef NOODLE_BOARD
#include "Noodle.h"
#endif

#endif /* BOARDSELECTION_H_ */
