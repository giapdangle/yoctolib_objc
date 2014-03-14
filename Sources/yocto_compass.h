/*********************************************************************
 *
 * $Id: yocto_compass.h 15256 2014-03-06 10:19:01Z seb $
 *
 * Declares yFindCompass(), the high-level API for Compass functions
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

@class YCompass;

//--- (YCompass globals)
typedef void (*YCompassValueCallback)(YCompass *func, NSString *functionValue);
typedef void (*YCompassTimedReportCallback)(YCompass *func, YMeasure *measure);
#ifndef _Y_AXIS_ENUM
#define _Y_AXIS_ENUM
typedef enum {
    Y_AXIS_X = 0,
    Y_AXIS_Y = 1,
    Y_AXIS_Z = 2,
    Y_AXIS_INVALID = -1,
} Y_AXIS_enum;
#endif

#define Y_MAGNETICHEADING_INVALID       YAPI_INVALID_DOUBLE
//--- (end of YCompass globals)

//--- (YCompass class start)
/**
 * YCompass Class: Compass function interface
 * 
 * The Yoctopuce application programming interface allows you to read an instant
 * measure of the sensor, as well as the minimal and maximal values observed.
 */
@interface YCompass : YSensor
//--- (end of YCompass class start)
{
@protected
//--- (YCompass attributes declaration)
    Y_AXIS_enum     _axis;
    double          _magneticHeading;
    YCompassValueCallback _valueCallbackCompass;
    YCompassTimedReportCallback _timedReportCallbackCompass;
//--- (end of YCompass attributes declaration)
}
// Constructor is protected, use yFindCompass factory function to instantiate
-(id)    initWith:(NSString*) func;

//--- (YCompass private methods declaration)
// Function-specific method for parsing of JSON output and caching result
-(int)             _parseAttr:(yJsonStateMachine*) j;

//--- (end of YCompass private methods declaration)
//--- (YCompass public methods declaration)
-(Y_AXIS_enum)     get_axis;


-(Y_AXIS_enum) axis;
/**
 * Returns the magnetic heading, regardless of the configured bearing.
 * 
 * @return a floating point number corresponding to the magnetic heading, regardless of the configured bearing
 * 
 * On failure, throws an exception or returns Y_MAGNETICHEADING_INVALID.
 */
-(double)     get_magneticHeading;


-(double) magneticHeading;
/**
 * Retrieves a compass for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the compass is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YCompass.isOnline() to test if the compass is
 * indeed online at a given time. In case of ambiguity when looking for
 * a compass by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the compass
 * 
 * @return a YCompass object allowing you to drive the compass.
 */
+(YCompass*)     FindCompass:(NSString*)func;

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
-(int)     registerValueCallback:(YCompassValueCallback)callback;

-(int)     _invokeValueCallback:(NSString*)value;

/**
 * Registers the callback function that is invoked on every periodic timed notification.
 * The callback is invoked only during the execution of ySleep or yHandleEvents.
 * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
 * one of these two functions periodically. To unregister a callback, pass a null pointer as argument.
 * 
 * @param callback : the callback function to call, or a null pointer. The callback function should take two
 *         arguments: the function object of which the value has changed, and an YMeasure object describing
 *         the new advertised value.
 * @noreturn
 */
-(int)     registerTimedReportCallback:(YCompassTimedReportCallback)callback;

-(int)     _invokeTimedReportCallback:(YMeasure*)value;


/**
 * Continues the enumeration of compasses started using yFirstCompass().
 * 
 * @return a pointer to a YCompass object, corresponding to
 *         a compass currently online, or a null pointer
 *         if there are no more compasses to enumerate.
 */
-(YCompass*) nextCompass;
/**
 * Starts the enumeration of compasses currently accessible.
 * Use the method YCompass.nextCompass() to iterate on
 * next compasses.
 * 
 * @return a pointer to a YCompass object, corresponding to
 *         the first compass currently online, or a null pointer
 *         if there are none.
 */
+(YCompass*) FirstCompass;
//--- (end of YCompass public methods declaration)

@end

//--- (Compass functions declaration)
/**
 * Retrieves a compass for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the compass is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YCompass.isOnline() to test if the compass is
 * indeed online at a given time. In case of ambiguity when looking for
 * a compass by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the compass
 * 
 * @return a YCompass object allowing you to drive the compass.
 */
YCompass* yFindCompass(NSString* func);
/**
 * Starts the enumeration of compasses currently accessible.
 * Use the method YCompass.nextCompass() to iterate on
 * next compasses.
 * 
 * @return a pointer to a YCompass object, corresponding to
 *         the first compass currently online, or a null pointer
 *         if there are none.
 */
YCompass* yFirstCompass(void);

//--- (end of Compass functions declaration)
CF_EXTERN_C_END

