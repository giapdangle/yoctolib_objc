/*********************************************************************
 *
 * $Id: yocto_bluetoothlink.h 20325 2015-05-12 15:34:50Z seb $
 *
 * Declares yFindBluetoothLink(), the high-level API for BluetoothLink functions
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

@class YBluetoothLink;

//--- (YBluetoothLink globals)
typedef void (*YBluetoothLinkValueCallback)(YBluetoothLink *func, NSString *functionValue);
#define Y_OWNADDRESS_INVALID            YAPI_INVALID_STRING
#define Y_PAIRINGPIN_INVALID            YAPI_INVALID_STRING
#define Y_REMOTEADDRESS_INVALID         YAPI_INVALID_STRING
#define Y_MESSAGE_INVALID               YAPI_INVALID_STRING
#define Y_COMMAND_INVALID               YAPI_INVALID_STRING
//--- (end of YBluetoothLink globals)

//--- (YBluetoothLink class start)
/**
 * YBluetoothLink Class: BluetoothLink function interface
 *
 * BluetoothLink function provides control over bluetooth link
 * and status for devices that are bluetooth-enabled.
 */
@interface YBluetoothLink : YFunction
//--- (end of YBluetoothLink class start)
{
@protected
//--- (YBluetoothLink attributes declaration)
    NSString*       _ownAddress;
    NSString*       _pairingPin;
    NSString*       _remoteAddress;
    NSString*       _message;
    NSString*       _command;
    YBluetoothLinkValueCallback _valueCallbackBluetoothLink;
//--- (end of YBluetoothLink attributes declaration)
}
// Constructor is protected, use yFindBluetoothLink factory function to instantiate
-(id)    initWith:(NSString*) func;

//--- (YBluetoothLink private methods declaration)
// Function-specific method for parsing of JSON output and caching result
-(int)             _parseAttr:(yJsonStateMachine*) j;

//--- (end of YBluetoothLink private methods declaration)
//--- (YBluetoothLink public methods declaration)
/**
 * Returns the MAC-48 address of the bluetooth interface, which is unique on the bluetooth network.
 *
 * @return a string corresponding to the MAC-48 address of the bluetooth interface, which is unique on
 * the bluetooth network
 *
 * On failure, throws an exception or returns Y_OWNADDRESS_INVALID.
 */
-(NSString*)     get_ownAddress;


-(NSString*) ownAddress;
/**
 * Returns an opaque string if a PIN code has been configured in the device to access
 * the SIM card, or an empty string if none has been configured or if the code provided
 * was rejected by the SIM card.
 *
 * @return a string corresponding to an opaque string if a PIN code has been configured in the device to access
 *         the SIM card, or an empty string if none has been configured or if the code provided
 *         was rejected by the SIM card
 *
 * On failure, throws an exception or returns Y_PAIRINGPIN_INVALID.
 */
-(NSString*)     get_pairingPin;


-(NSString*) pairingPin;
/**
 * Changes the PIN code used by the module for bluetooth pairing.
 * Remember to call the saveToFlash() method of the module to save the
 * new value in the device flash.
 *
 * @param newval : a string corresponding to the PIN code used by the module for bluetooth pairing
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_pairingPin:(NSString*) newval;
-(int)     setPairingPin:(NSString*) newval;

/**
 * Returns the MAC-48 address of the remote device to connect to.
 *
 * @return a string corresponding to the MAC-48 address of the remote device to connect to
 *
 * On failure, throws an exception or returns Y_REMOTEADDRESS_INVALID.
 */
-(NSString*)     get_remoteAddress;


-(NSString*) remoteAddress;
/**
 * Changes the MAC-48 address defining which remote device to connect to.
 *
 * @param newval : a string corresponding to the MAC-48 address defining which remote device to connect to
 *
 * @return YAPI_SUCCESS if the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_remoteAddress:(NSString*) newval;
-(int)     setRemoteAddress:(NSString*) newval;

/**
 * Returns the latest status message from the bluetooth interface.
 *
 * @return a string corresponding to the latest status message from the bluetooth interface
 *
 * On failure, throws an exception or returns Y_MESSAGE_INVALID.
 */
-(NSString*)     get_message;


-(NSString*) message;
-(NSString*)     get_command;


-(NSString*) command;
-(int)     set_command:(NSString*) newval;
-(int)     setCommand:(NSString*) newval;

/**
 * Retrieves a cellular interface for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the cellular interface is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YBluetoothLink.isOnline() to test if the cellular interface is
 * indeed online at a given time. In case of ambiguity when looking for
 * a cellular interface by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * @param func : a string that uniquely characterizes the cellular interface
 *
 * @return a YBluetoothLink object allowing you to drive the cellular interface.
 */
+(YBluetoothLink*)     FindBluetoothLink:(NSString*)func;

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
-(int)     registerValueCallback:(YBluetoothLinkValueCallback)callback;

-(int)     _invokeValueCallback:(NSString*)value;

/**
 * Attempt to connect to the previously selected remote device.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     connect;

/**
 * Disconnect from the previously selected remote device.
 *
 * @return YAPI_SUCCESS when the call succeeds.
 *
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     disconnect;


/**
 * Continues the enumeration of cellular interfaces started using yFirstBluetoothLink().
 *
 * @return a pointer to a YBluetoothLink object, corresponding to
 *         a cellular interface currently online, or a null pointer
 *         if there are no more cellular interfaces to enumerate.
 */
-(YBluetoothLink*) nextBluetoothLink;
/**
 * Starts the enumeration of cellular interfaces currently accessible.
 * Use the method YBluetoothLink.nextBluetoothLink() to iterate on
 * next cellular interfaces.
 *
 * @return a pointer to a YBluetoothLink object, corresponding to
 *         the first cellular interface currently online, or a null pointer
 *         if there are none.
 */
+(YBluetoothLink*) FirstBluetoothLink;
//--- (end of YBluetoothLink public methods declaration)

@end

//--- (BluetoothLink functions declaration)
/**
 * Retrieves a cellular interface for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 *
 * This function does not require that the cellular interface is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YBluetoothLink.isOnline() to test if the cellular interface is
 * indeed online at a given time. In case of ambiguity when looking for
 * a cellular interface by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 *
 * @param func : a string that uniquely characterizes the cellular interface
 *
 * @return a YBluetoothLink object allowing you to drive the cellular interface.
 */
YBluetoothLink* yFindBluetoothLink(NSString* func);
/**
 * Starts the enumeration of cellular interfaces currently accessible.
 * Use the method YBluetoothLink.nextBluetoothLink() to iterate on
 * next cellular interfaces.
 *
 * @return a pointer to a YBluetoothLink object, corresponding to
 *         the first cellular interface currently online, or a null pointer
 *         if there are none.
 */
YBluetoothLink* yFirstBluetoothLink(void);

//--- (end of BluetoothLink functions declaration)
CF_EXTERN_C_END

