/*
 * BIT_UTILS.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */



#ifndef SERIVICES_INCLUDE_BIT_UTILS_H_
#define SERIVICES_INCLUDE_BIT_UTILS_H_




#define SET_BIT(REG_ADDR, BIT_POSN)             ( (REG_ADDR) |= (1<< (BIT_POSN)))
#define CLEAR_BIT(REG_ADDR, BIT_POSN)           ( (REG_ADDR) &= ~ (1<< (BIT_POSN)))
#define TOGGLE_BIT(REG_ADDR, BIT_POSN)          ( (REG_ADDR) ^= (1<< (BIT_POSN)))
#define READ_BIT(REG_ADDR, BIT_POSN)            (( (REG_ADDR)>>(BIT_POSN) ) & (1))
#define WRITE_BIT(REG_ADDR, BIT_POSN, LOGIC)	((REG_ADDR) = ( (REG_ADDR)& (~(1<<BIT_POSN))) | ((LOGIC)<<(BIT_POSN)) )


#define SHIFT_RIGHT_REG(REG_ADDR,TIMES)   ( (REG_ADDR) >>= (TIMES)  )
#define SHIFT_LEFT_REG(REG_ADDR,TIMES)   ( (REG_ADDR) <<= (TIMES)  )


#define CRICULAR_SHIFT_RIGHT_REG(REG_ADDR,TIMES)   ( (REG_ADDR) = ((REG_ADDR)>>(TIMES)) |  ( (REG_ADDR)<<( ( sizeof((REG_ADDR))*8 ) - TIMES)   )   )
#define CIRCULAR_SHIFT_LEFT_REG(REG_ADDR,TIMES)   ( (REG_ADDR) = ((REG_ADDR)<<(TIMES)) |  ( (REG_ADDR)>>( ( sizeof((REG_ADDR))*8 ) - TIMES)   )   )



#define ASSIGN_REG(REG_ADDR,VALUE)   ( (REG_ADDR) = (VALUE)  )
#define SET_REG(REG_ADDR)   ( (REG_ADDR) |= (~0)  )
#define CLEAR_REG(REG_ADDR)   ( (REG_ADDR) &= (0)  )


#define TOGGLE_REG(REG_ADDR)   ( (REG_ADDR) ^= (~0)  )

#define SET_HIGHEST_NIBBLE(REG_ADDR)   ((REG_ADDR) |= (0x0F<<(sizeof((REG_ADDR))*8-4)))
#define SET_LOWEST_NIBBLE(REG_ADDR)   ((REG_ADDR) |= 0x0F)


#define CLEAR_HIGHEST_NIBBLE(REG_ADDR)   ((REG_ADDR) &=  ~(0x0F<<(sizeof((REG_ADDR))*8-4)))
#define CLEAR_LOWEST_NIBBLE(REG_ADDR)   ((REG_ADDR) &= ~0x0F)

#define GET_HIGHEST_NIBBLE(REG_ADDR)   ( (REG_ADDR) >> ( sizeof((REG_ADDR))*8-4))
#define GET_LOWEST_NIBBLE(REG_ADDR)   ((REG_ADDR) & 0x0F)


#define ASSIGN_HIGHEST_NIBBLE(REG_ADDR, VALUE)   ((REG_ADDR) =  ( (REG_ADDR) &  ~(0x0F<<(sizeof((REG_ADDR))*8-4)) )  | ((VALUE<<(sizeof((REG_ADDR))*8-4))  ) //Clear first then oring
#define ASSIGN_LOWEST_NIBBLE(REG_ADDR, VALUE)   ((REG_ADDR) = ((REG_ADDR) & ~0x0F) | (VALUE) ) // clear first then oring



#define TOGGLE_HIGHEST_NIBBLE(REG_ADDR)   ((REG_ADDR) ^= (0x0F<<(sizeof((REG_ADDR))*8-4)))
#define TOGGLE_LOWEST_NIBBLE(REG_ADDR)   ((REG_ADDR) ^= 0x0F)


// Clear Most and Leas,, then oring with lest shifting to be most ,, then oring most to be least
#define SWAP_NIBBLE(REG_ADDR)    ((REG_ADDR) =  (Reg & ~0x0F & ~(0x0F<<(sizeof((REG_ADDR))*8-4)) ) |\
                                ( ((REG_ADDR) &0x0f) << (sizeof((REG_ADDR))*8-4))  |\
                                              (( (REG_ADDR) >> ( sizeof((REG_ADDR))*8-4)))   )



#endif /* SERIVICES_INCLUDE_BIT_UTILS_H_ */
