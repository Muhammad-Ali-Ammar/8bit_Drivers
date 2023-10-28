/*
 * HELPERS.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */

#ifndef SERIVICES_INCLUDE_HELPERS_H_
#define SERIVICES_INCLUDE_HELPERS_H_


#define CONCAT(_X7_,_X6_,_X5_,_X4_,_X3_,_X2_,_X1_,_X0_)  (concat_helper(_X7_,_X6_,_X5_,_X4_,_X3_,_X2_,_X1_,_X0_))

#define concat_helper(_X7_,_X6_,_X5_,_X4_,_X3_,_X2_,_X1_,_X0_)  (0b##_X7_##_X6_##_X5_##_X4_##_X3_##_X2_##_X1_##_X0_)


#endif /* SERIVICES_INCLUDE_HELPERS_H_ */
