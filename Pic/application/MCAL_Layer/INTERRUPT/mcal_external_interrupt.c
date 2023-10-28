/* 
 * File:   mcal_external_interrupt.c
 * Author: Muhammad Ammar
 *
 * Created on 07 ????, 2023, 04:57 ?
 */


#include "mcal_external_interrupt.h"



#if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*Call back Functions */
static void (* Int0_InterruptHandler)(void) = NULL;
static void (* Int1_InterruptHandler)(void) = NULL;
static void (* Int2_InterruptHandler)(void) = NULL;

/* helpers functions  prototype */
static Std_ReturnType Intx_Enable(const Intx_ConfigPinType* _intx_obj);
static Std_ReturnType Intx_Disable(const Intx_ConfigPinType* _intx_obj);
static Std_ReturnType Intx_InitEdge(const Intx_ConfigPinType* _intx_obj);
static Std_ReturnType Intx_InitIntxPin(const Intx_ConfigPinType* _intx_obj);
static Std_ReturnType Intx_ClearFlag(const Intx_ConfigPinType* _intx_obj);
static Std_ReturnType Intx_InitCallBack(const Intx_ConfigPinType* _intx_obj);

static Std_ReturnType Int0_SetCallBack(void (*_InterruptHandler)(void));
static Std_ReturnType Int1_SetCallBack(void (*_InterruptHandler)(void));
static Std_ReturnType Int2_SetCallBack(void (*_InterruptHandler)(void));


#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType Intx_SetPrioirty(const Intx_ConfigPinType* _intx_obj);
#endif


/* public functions  implementation */
Std_ReturnType Intx_Init(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        
       /* Disable External Interrupt*/
        ret &= Intx_Disable(_intx_obj);
        /* Clear flag */
        ret &=Intx_ClearFlag(_intx_obj);
        /* Set Edge of External Interrupt */
        ret &= Intx_InitEdge(_intx_obj);
        
        /* setting prioirty if feature enabled*/
        #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret &= Intx_SetPrioirty(_intx_obj);
        #endif

        /* configure i/o pin */
        ret &= Intx_InitIntxPin(_intx_obj);
        
        /* Init CallBack Funciton */
        ret &= Intx_InitCallBack(_intx_obj);
        
        /* Enable External Interrupt*/
        ret &= Intx_Enable(_intx_obj);

    }
    
    return ret;
}
Std_ReturnType Intx_DeInit(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        ret &= Intx_Disable(_intx_obj);
    }
    
    return ret;
}

void INT0_ISR(void){
    
    Int0_ClearFlag();
    if(NULL != Int0_InterruptHandler){
        Int0_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
void INT1_ISR(void){
    Int1_ClearFlag();
    if(NULL != Int1_InterruptHandler){
        Int1_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
void INT2_ISR(void){
    Int2_ClearFlag();
    if(NULL != Int2_InterruptHandler){
        Int2_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}



/* helpers implementation  */
static Std_ReturnType Intx_Enable(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                Int0_EnableInterrupt();
                
                #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Interrupt_EnablePrioirtyOfTheSystem();   
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
                #else
                Interrupt_EnableGlobalInterrupt();
                Interrupt_EnablePeripheralInterrupt();
                #endif

                break;
                
            case INTx_INT1 :
                Int1_EnableInterrupt();
                #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
                #else
                Interrupt_EnableGlobalInterrupt();
                Interrupt_EnablePeripheralInterrupt();
                #endif

                break;
                
                
            case INTx_INT2 :
                Int2_EnableInterrupt();
                #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
                #else
                Interrupt_EnableGlobalInterrupt();
                Interrupt_EnablePeripheralInterrupt();
                #endif
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
        }
        
            
    }
    
    return ret;
}
static Std_ReturnType Intx_Disable(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                Int0_DisableInterrupt();
                break;
                
            case INTx_INT1 :
                Int1_DisableInterrupt();
                break;
                
                
            case INTx_INT2 :
                Int2_DisableInterrupt();
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}
static Std_ReturnType Intx_InitEdge(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                Int0_SetInterruptEdge(_intx_obj->edge);
                break;
                
            case INTx_INT1 :
                Int1_SetInterruptEdge(_intx_obj->edge);
                break;
                
                
            case INTx_INT2 :
                Int2_SetInterruptEdge(_intx_obj->edge);
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}
static Std_ReturnType Intx_InitIntxPin(const Intx_ConfigPinType* _intx_obj){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Dio_InitChannelDirection(&(_intx_obj->pin));
    }
    
    return ret;
    
}
static Std_ReturnType Intx_ClearFlag(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else{
            switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                Int0_ClearFlag();
                break;
                
            case INTx_INT1 :
                Int1_ClearFlag();
                break;
                
                
            case INTx_INT2 :
                Int2_ClearFlag();
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
            }
    }
    return ret;
    
}
static Std_ReturnType Intx_InitCallBack(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                ret = Int0_SetCallBack(_intx_obj->Intx_InterruptHandler);
                break;
                
            case INTx_INT1 :
                
                ret = Int1_SetCallBack(_intx_obj->Intx_InterruptHandler);
                break;
                
                
            case INTx_INT2 :
                ret = Int2_SetCallBack(_intx_obj->Intx_InterruptHandler);
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}

static Std_ReturnType Int0_SetCallBack(void (*_InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        Int0_InterruptHandler = _InterruptHandler;
    }
    
    return ret;
}
static Std_ReturnType Int1_SetCallBack(void (*_InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        Int1_InterruptHandler = _InterruptHandler;
    }
    
    return ret;
}
static Std_ReturnType Int2_SetCallBack(void (*_InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _InterruptHandler){
        ret = E_NOT_OK;
    }
    else {
        Int2_InterruptHandler = _InterruptHandler;
    }
    
    return ret;
}


#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
   static Std_ReturnType Intx_SetPrioirty(const Intx_ConfigPinType* _intx_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _intx_obj){
        ret = E_NOT_OK;
    }
    else {
        switch(_intx_obj->intx_number){
            
            case INTx_INT0 :
                /* empty because it's always high*/
                break;
                
            case INTx_INT1 :
                Int1_SetPrioirty(_intx_obj->priority);
                break;
                
                
            case INTx_INT2 :
                Int2_SetPrioirty(_intx_obj->priority);
                break;
                
            default: 
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}
#endif 



#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

   
static Dio_LogicPinType g_ioc0_previous_flag = DIO_LOW;
static Dio_LogicPinType g_ioc0_current_flag = DIO_LOW;   

static Dio_LogicPinType g_ioc1_previous_flag = DIO_LOW;
static Dio_LogicPinType g_ioc1_current_flag = DIO_LOW;   

static Dio_LogicPinType g_ioc2_previous_flag = DIO_LOW;
static Dio_LogicPinType g_ioc2_current_flag = DIO_LOW;   

static Dio_LogicPinType g_ioc3_previous_flag = DIO_LOW;
static Dio_LogicPinType g_ioc3_current_flag = DIO_LOW;   

/*Call back Functions */
   
   /* general one*/

static void (* Ioc0_InterruptHandler)(void) = NULL;
static void (* Ioc1_InterruptHandler)(void) = NULL;
static void (* Ioc2_InterruptHandler)(void) = NULL;
static void (* Ioc3_InterruptHandler)(void) = NULL;
/* helpers functions  prototype */

static Std_ReturnType Ioc_InitIocPin(const Ioc_ConfigPinType* _ioc_obj);
static Std_ReturnType Ioc_InitCallBack(const Ioc_ConfigPinType* _ioc_obj);
static Std_ReturnType Ioc_ClearFlag();

static Std_ReturnType Ioc_SetCallBack(void (*_InterruptHandler)(void));

static Std_ReturnType Ioc_ReadPinState(const Ioc_NumberType _ioc_number, Dio_LogicPinType* _logic);


Std_ReturnType Ioc_Init(const Ioc_ConfigPinType* _ioc_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _ioc_obj){
        ret = E_NOT_OK;
    }
    else {
        /* Disable Interrupt On Change */
        Ioc_DisableInterrupt();
        /* Clear flag */
       ret &= Ioc_ClearFlag();

        
        /* setting prioirty if feature enabled*/ 
#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        Ioc_SetPrioirty(_ioc_obj->priority);
        Interrupt_EnablePrioirtyOfTheSystem();
        Interrupt_EnableHighGlobalInterrupt();
        Interrupt_EnableLowGlobalInterrupt();
        
        
#else
        Interrupt_EnableGlobalInterrupt();
        Interrupt_EnablePeripheralInterrupt();
        
#endif
        
        /* configure i/o pin */
        ret &= Ioc_InitIocPin(_ioc_obj);
        
        /* Init CallBack Funciton */
        ret &= Ioc_InitCallBack(_ioc_obj);
        
        /* Enable External Interrupt*/
        Ioc_EnableInterrupt() ;
        
    }
    
    return ret;
}
Std_ReturnType Ioc_DeInit(const Ioc_ConfigPinType* _ioc_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _ioc_obj){
        ret = E_NOT_OK;
    }
    else {
        Ioc_DisableInterrupt();
    }
    
    return ret;
}

static Std_ReturnType Ioc_InitIocPin(const Ioc_ConfigPinType* _ioc_obj){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _ioc_obj){
        ret = E_NOT_OK;
    }
    else {
        ret = Dio_InitChannelDirection(&(_ioc_obj->pin));
    }
    
    return ret;
}

static Std_ReturnType Ioc_ClearFlag(){
    Std_ReturnType ret = E_OK;
    uint8 l_mismatch_end;

    
     ret = Dio_ReadPort(DIO_PORTB_INDEX,&l_mismatch_end);
     IOC_ClearFlag();
    
    
    return ret;
    
}


static Std_ReturnType Ioc_InitCallBack(const Ioc_ConfigPinType* _ioc_obj){
    
    Std_ReturnType ret = E_OK;
    Dio_LogicPinType l_logic = DIO_LOW;
    if(NULL == _ioc_obj){
        ret = E_NOT_OK;
    }
    else {
        
        ret &= Dio_ReadChannel(&(_ioc_obj->pin), &l_logic);
        switch(_ioc_obj->number){
            
            case IOC_KBI0:
                Ioc0_InterruptHandler = _ioc_obj->Ioc_UserInterruptHandler;
                
                g_ioc0_previous_flag = l_logic;
                g_ioc0_current_flag = l_logic;
                break;
                
            case IOC_KBI1:
                Ioc1_InterruptHandler = _ioc_obj->Ioc_UserInterruptHandler;
                g_ioc1_previous_flag = l_logic;
                g_ioc1_current_flag = l_logic;
                break;
                
            case IOC_KBI2:
                Ioc2_InterruptHandler = _ioc_obj->Ioc_UserInterruptHandler;
                g_ioc2_previous_flag = l_logic;
                g_ioc2_current_flag = l_logic;
                break;
                
            case IOC_KBI3:
                Ioc3_InterruptHandler = _ioc_obj->Ioc_UserInterruptHandler;
                g_ioc3_previous_flag = l_logic;
                g_ioc3_current_flag = l_logic;
                break;
                
            default : 
                ret = E_NOT_OK;
                
        }
       
    }
    
    return ret;
}

static Std_ReturnType Ioc_ReadPinState(const Ioc_NumberType _ioc_number, Dio_LogicPinType* _logic){
    Std_ReturnType ret = E_OK;
    
     if( NULL== _logic){
        ret = E_NOT_OK;
    }
     else {
         switch(_ioc_number){
         
             case IOC_KBI0:
                 (*_logic) = (PORTB>>4) &DIO_BIT0_MASK;
                 break;
                 
                 
             case IOC_KBI1:
                 (*_logic) = (PORTB>>5) &DIO_BIT0_MASK;
                 break;
                 
                 
                 
             case IOC_KBI2:
                 (*_logic) = (PORTB>>6) &DIO_BIT0_MASK;
                 break;
                 
                 
                 
             case IOC_KBI3:
                 (*_logic) = (PORTB>>7) &DIO_BIT0_MASK;
                 break;
                 
             default :
                 ret = E_NOT_OK;
         }
             
         
     }
    
    return ret;
}


/* general function */
void IOC_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Ioc_ClearFlag();
    
    ret &= Ioc_ReadPinState(IOC_KBI0,&g_ioc0_current_flag);
    ret &= Ioc_ReadPinState(IOC_KBI1,&g_ioc1_current_flag);
    ret &= Ioc_ReadPinState(IOC_KBI2,&g_ioc2_current_flag);
    ret &= Ioc_ReadPinState(IOC_KBI3,&g_ioc3_current_flag);

    
    if(NULL != Ioc0_InterruptHandler && g_ioc0_current_flag != g_ioc0_previous_flag){
        Ioc0_InterruptHandler();
        g_ioc0_previous_flag = g_ioc0_current_flag;
    }
    
    else if(NULL != Ioc1_InterruptHandler && g_ioc1_current_flag != g_ioc1_previous_flag){
        Ioc1_InterruptHandler();
        g_ioc1_previous_flag = g_ioc1_current_flag;
    }
    
    else if(NULL != Ioc2_InterruptHandler && g_ioc2_current_flag != g_ioc2_previous_flag){
        Ioc2_InterruptHandler();
        g_ioc2_previous_flag = g_ioc2_current_flag;
    }
    
    else if(NULL != Ioc3_InterruptHandler && g_ioc3_current_flag != g_ioc3_previous_flag){
        Ioc3_InterruptHandler();
        g_ioc3_previous_flag = g_ioc3_current_flag;
    }
    
    else {
        ret = E_NOT_OK;

    }
    
}


#endif


