/*********************************************************************
 *
 * $Id: pic24config.php 12323 2013-08-13 15:09:18Z mvuilleu $
 *
 * Declares yFindDigitalIO(), the high-level API for DigitalIO functions
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 *  Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 *  Yoctopuce Sarl (hereafter Licensor) grants to you a perpetual
 *  non-exclusive license to use, modify, copy and integrate this
 *  file into your software for the sole purpose of interfacing 
 *  with Yoctopuce products. 
 *
 *  You may reproduce and distribute copies of this file in 
 *  source or object form, as long as the sole purpose of this
 *  code is to interface with Yoctopuce products. You must retain 
 *  this notice in the distributed source file.
 *
 *  You should refer to Yoctopuce General Terms and Conditions
 *  for additional information regarding your rights and 
 *  obligations.
 *
 *  THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *  WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *  WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS 
 *  FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *  EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *  INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 *  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *  SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *  LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *  CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *  BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *  WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#include "yocto_api.h"
CF_EXTERN_C_BEGIN

//--- (YDigitalIO definitions)
typedef enum {
    Y_OUTPUTVOLTAGE_USB_5V = 0,
    Y_OUTPUTVOLTAGE_USB_3V3 = 1,
    Y_OUTPUTVOLTAGE_EXT_V = 2,
    Y_OUTPUTVOLTAGE_INVALID = -1
} Y_OUTPUTVOLTAGE_enum;

#define Y_LOGICALNAME_INVALID           [YAPI  INVALID_STRING]
#define Y_ADVERTISEDVALUE_INVALID       [YAPI  INVALID_STRING]
#define Y_PORTSTATE_INVALID             (-1)
#define Y_PORTDIRECTION_INVALID         (-1)
#define Y_PORTOPENDRAIN_INVALID         (-1)
#define Y_PORTSIZE_INVALID              (0xffffffff)
#define Y_COMMAND_INVALID               [YAPI  INVALID_STRING]
//--- (end of YDigitalIO definitions)

/**
 * YDigitalIO Class: Digital IO function interface
 * 
 * ....
 */
@interface YDigitalIO : YFunction
{
@protected

// Attributes (function value cache)
//--- (YDigitalIO attributes)
    NSString*       _logicalName;
    NSString*       _advertisedValue;
    int             _portState;
    int             _portDirection;
    int             _portOpenDrain;
    unsigned        _portSize;
    Y_OUTPUTVOLTAGE_enum _outputVoltage;
    NSString*       _command;
//--- (end of YDigitalIO attributes)
}
//--- (YDigitalIO declaration)
// Constructor is protected, use yFindDigitalIO factory function to instantiate
-(id)    initWithFunction:(NSString*) func;

// Function-specific method for parsing of JSON output and caching result
-(int)             _parse:(yJsonStateMachine*) j;

/**
 * Registers the callback function that is invoked on every change of advertised value.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a null pointer as argument.
 * 
 * @param callback : the callback function to call, or a null pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and the character string describing
 *         the new advertised value.
 * @noreturn
 */
-(void)     registerValueCallback:(YFunctionUpdateCallback) callback;   
/**
 * comment from .yc definition
 */
-(void)     set_objectCallback:(id) object :(SEL)selector;
-(void)     setObjectCallback:(id) object :(SEL)selector;
-(void)     setObjectCallback:(id) object withSelector:(SEL)selector;

//--- (end of YDigitalIO declaration)
//--- (YDigitalIO accessors declaration)

/**
 * Continues the enumeration of digital IO port started using yFirstDigitalIO().
 * 
 * @return a pointer to a YDigitalIO object, corresponding to
 *         a digital IO port currently online, or a null pointer
 *         if there are no more digital IO port to enumerate.
 */
-(YDigitalIO*) nextDigitalIO;
/**
 * Retrieves a digital IO port for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the digital IO port is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YDigitalIO.isOnline() to test if the digital IO port is
 * indeed online at a given time. In case of ambiguity when looking for
 * a digital IO port by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the digital IO port
 * 
 * @return a YDigitalIO object allowing you to drive the digital IO port.
 */
+(YDigitalIO*) FindDigitalIO:(NSString*) func;
/**
 * Starts the enumeration of digital IO port currently accessible.
 * Use the method YDigitalIO.nextDigitalIO() to iterate on
 * next digital IO port.
 * 
 * @return a pointer to a YDigitalIO object, corresponding to
 *         the first digital IO port currently online, or a null pointer
 *         if there are none.
 */
+(YDigitalIO*) FirstDigitalIO;

/**
 * Returns the logical name of the digital IO port.
 * 
 * @return a string corresponding to the logical name of the digital IO port
 * 
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
-(NSString*) get_logicalName;
-(NSString*) logicalName;

/**
 * Changes the logical name of the digital IO port. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the logical name of the digital IO port
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_logicalName:(NSString*) newval;
-(int)     setLogicalName:(NSString*) newval;

/**
 * Returns the current value of the digital IO port (no more than 6 characters).
 * 
 * @return a string corresponding to the current value of the digital IO port (no more than 6 characters)
 * 
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
-(NSString*) get_advertisedValue;
-(NSString*) advertisedValue;

/**
 * Returns the digital IO port state: bit 0 represents input 0, and so on.
 * 
 * @return an integer corresponding to the digital IO port state: bit 0 represents input 0, and so on
 * 
 * On failure, throws an exception or returns Y_PORTSTATE_INVALID.
 */
-(int) get_portState;
-(int) portState;

/**
 * Changes the digital IO port state: bit 0 represents input 0, and so on. This function has no effect
 * on bits configured as input in portDirection.
 * 
 * @param newval : an integer corresponding to the digital IO port state: bit 0 represents input 0, and so on
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_portState:(int) newval;
-(int)     setPortState:(int) newval;

/**
 * Returns the IO direction of all bits of the port: 0 makes a bit an input, 1 makes it an output.
 * 
 * @return an integer corresponding to the IO direction of all bits of the port: 0 makes a bit an
 * input, 1 makes it an output
 * 
 * On failure, throws an exception or returns Y_PORTDIRECTION_INVALID.
 */
-(int) get_portDirection;
-(int) portDirection;

/**
 * Changes the IO direction of all bits of the port: 0 makes a bit an input, 1 makes it an output.
 * Remember to call the saveToFlash() method  to make sure the setting will be kept after a reboot.
 * 
 * @param newval : an integer corresponding to the IO direction of all bits of the port: 0 makes a bit
 * an input, 1 makes it an output
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_portDirection:(int) newval;
-(int)     setPortDirection:(int) newval;

/**
 * Returns the electrical interface for each bit of the port. 0 makes a bit a regular input/output, 1 makes
 * it an open-drain (open-collector) input/output.
 * 
 * @return an integer corresponding to the electrical interface for each bit of the port
 * 
 * On failure, throws an exception or returns Y_PORTOPENDRAIN_INVALID.
 */
-(int) get_portOpenDrain;
-(int) portOpenDrain;

/**
 * Changes the electrical interface for each bit of the port. 0 makes a bit a regular input/output, 1 makes
 * it an open-drain (open-collector) input/output. Remember to call the
 * saveToFlash() method  to make sure the setting will be kept after a reboot.
 * 
 * @param newval : an integer corresponding to the electrical interface for each bit of the port
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_portOpenDrain:(int) newval;
-(int)     setPortOpenDrain:(int) newval;

/**
 * Returns the number of bits implemented in the I/O port.
 * 
 * @return an integer corresponding to the number of bits implemented in the I/O port
 * 
 * On failure, throws an exception or returns Y_PORTSIZE_INVALID.
 */
-(unsigned) get_portSize;
-(unsigned) portSize;

/**
 * Returns the voltage source used to drive output bits.
 * 
 * @return a value among Y_OUTPUTVOLTAGE_USB_5V, Y_OUTPUTVOLTAGE_USB_3V3 and Y_OUTPUTVOLTAGE_EXT_V
 * corresponding to the voltage source used to drive output bits
 * 
 * On failure, throws an exception or returns Y_OUTPUTVOLTAGE_INVALID.
 */
-(Y_OUTPUTVOLTAGE_enum) get_outputVoltage;
-(Y_OUTPUTVOLTAGE_enum) outputVoltage;

/**
 * Changes the voltage source used to drive output bits.
 * Remember to call the saveToFlash() method  to make sure the setting will be kept after a reboot.
 * 
 * @param newval : a value among Y_OUTPUTVOLTAGE_USB_5V, Y_OUTPUTVOLTAGE_USB_3V3 and
 * Y_OUTPUTVOLTAGE_EXT_V corresponding to the voltage source used to drive output bits
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_outputVoltage:(Y_OUTPUTVOLTAGE_enum) newval;
-(int)     setOutputVoltage:(Y_OUTPUTVOLTAGE_enum) newval;

-(NSString*) get_command;
-(NSString*) command;

-(int)     set_command:(NSString*) newval;
-(int)     setCommand:(NSString*) newval;

/**
 * Set a single bit of the I/O port.
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * @param bitval: the value of the bit (1 or 0)
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_bitState :(int)bitno :(int)bitval;

/**
 * Returns the value of a single bit of the I/O port.
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * 
 * @return the bit value (0 or 1)
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     get_bitState :(int)bitno;

/**
 * Revert a single bit of the I/O port.
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     toggle_bitState :(int)bitno;

/**
 * Change  the direction of a single bit from the I/O port.
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * @param bitdirection: direction to set, 0 makes the bit an input, 1 makes it an output.
 *         Remember to call the   saveToFlash() method to make sure the setting will be kept after a reboot.
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_bitDirection :(int)bitno :(int)bitdirection;

/**
 * Change  the direction of a single bit from the I/O port (0 means the bit is an input, 1  an output).
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     get_bitDirection :(int)bitno;

/**
 * Change  the electrical interface of a single bit from the I/O port.
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * @param opendrain: value to set, 0 makes a bit a regular input/output, 1 makes
 *         it an open-drain (open-collector) input/output. Remember to call the
 *         saveToFlash() method to make sure the setting will be kept after a reboot.
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_bitOpenDrain :(int)bitno :(int)opendrain;

/**
 * Returns the type of electrical interface of a single bit from the I/O port. (0 means the bit is an
 * input, 1  an output).
 * 
 * @param bitno: the bit number; lowest bit is index 0
 * 
 * @return   0 means the a bit is a regular input/output, 1means the b it an open-drain
 * (open-collector) input/output.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     get_bitOpenDrain :(int)bitno;


//--- (end of YDigitalIO accessors declaration)
@end

//--- (DigitalIO functions declaration)

/**
 * Retrieves a digital IO port for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the digital IO port is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YDigitalIO.isOnline() to test if the digital IO port is
 * indeed online at a given time. In case of ambiguity when looking for
 * a digital IO port by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the digital IO port
 * 
 * @return a YDigitalIO object allowing you to drive the digital IO port.
 */
YDigitalIO* yFindDigitalIO(NSString* func);
/**
 * Starts the enumeration of digital IO port currently accessible.
 * Use the method YDigitalIO.nextDigitalIO() to iterate on
 * next digital IO port.
 * 
 * @return a pointer to a YDigitalIO object, corresponding to
 *         the first digital IO port currently online, or a null pointer
 *         if there are none.
 */
YDigitalIO* yFirstDigitalIO(void);

//--- (end of DigitalIO functions declaration)
CF_EXTERN_C_END

