/*********************************************************************
 *
 * $Id: yocto_temperature.h 12324 2013-08-13 15:10:31Z mvuilleu $
 *
 * Declares yFindTemperature(), the high-level API for Temperature functions
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

//--- (YTemperature definitions)
typedef enum {
    Y_SENSORTYPE_DIGITAL = 0,
    Y_SENSORTYPE_TYPE_K = 1,
    Y_SENSORTYPE_TYPE_E = 2,
    Y_SENSORTYPE_TYPE_J = 3,
    Y_SENSORTYPE_TYPE_N = 4,
    Y_SENSORTYPE_TYPE_R = 5,
    Y_SENSORTYPE_TYPE_S = 6,
    Y_SENSORTYPE_TYPE_T = 7,
    Y_SENSORTYPE_PT100_4WIRES = 8,
    Y_SENSORTYPE_PT100_3WIRES = 9,
    Y_SENSORTYPE_PT100_2WIRES = 10,
    Y_SENSORTYPE_INVALID = -1
} Y_SENSORTYPE_enum;

#define Y_LOGICALNAME_INVALID           [YAPI  INVALID_STRING]
#define Y_ADVERTISEDVALUE_INVALID       [YAPI  INVALID_STRING]
#define Y_UNIT_INVALID                  [YAPI  INVALID_STRING]
#define Y_CURRENTVALUE_INVALID          (-DBL_MAX)
#define Y_LOWESTVALUE_INVALID           (-DBL_MAX)
#define Y_HIGHESTVALUE_INVALID          (-DBL_MAX)
#define Y_CURRENTRAWVALUE_INVALID       (-DBL_MAX)
#define Y_CALIBRATIONPARAM_INVALID      [YAPI  INVALID_STRING]
#define Y_RESOLUTION_INVALID            (-DBL_MAX)
//--- (end of YTemperature definitions)

/**
 * YTemperature Class: Temperature function interface
 * 
 * The Yoctopuce application programming interface allows you to read an instant
 * measure of the sensor, as well as the minimal and maximal values observed.
 */
@interface YTemperature : YFunction
{
@protected

// Attributes (function value cache)
//--- (YTemperature attributes)
    NSString*       _logicalName;
    NSString*       _advertisedValue;
    NSString*       _unit;
    double          _currentValue;
    double          _lowestValue;
    double          _highestValue;
    double          _currentRawValue;
    NSString*       _calibrationParam;
    double          _resolution;
    Y_SENSORTYPE_enum _sensorType;
    int             _calibrationOffset;
//--- (end of YTemperature attributes)
}
//--- (YTemperature declaration)
// Constructor is protected, use yFindTemperature factory function to instantiate
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

//--- (end of YTemperature declaration)
//--- (YTemperature accessors declaration)

/**
 * Continues the enumeration of temperature sensors started using yFirstTemperature().
 * 
 * @return a pointer to a YTemperature object, corresponding to
 *         a temperature sensor currently online, or a null pointer
 *         if there are no more temperature sensors to enumerate.
 */
-(YTemperature*) nextTemperature;
/**
 * Retrieves a temperature sensor for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the temperature sensor is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YTemperature.isOnline() to test if the temperature sensor is
 * indeed online at a given time. In case of ambiguity when looking for
 * a temperature sensor by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the temperature sensor
 * 
 * @return a YTemperature object allowing you to drive the temperature sensor.
 */
+(YTemperature*) FindTemperature:(NSString*) func;
/**
 * Starts the enumeration of temperature sensors currently accessible.
 * Use the method YTemperature.nextTemperature() to iterate on
 * next temperature sensors.
 * 
 * @return a pointer to a YTemperature object, corresponding to
 *         the first temperature sensor currently online, or a null pointer
 *         if there are none.
 */
+(YTemperature*) FirstTemperature;

/**
 * Returns the logical name of the temperature sensor.
 * 
 * @return a string corresponding to the logical name of the temperature sensor
 * 
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
-(NSString*) get_logicalName;
-(NSString*) logicalName;

/**
 * Changes the logical name of the temperature sensor. You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the logical name of the temperature sensor
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_logicalName:(NSString*) newval;
-(int)     setLogicalName:(NSString*) newval;

/**
 * Returns the current value of the temperature sensor (no more than 6 characters).
 * 
 * @return a string corresponding to the current value of the temperature sensor (no more than 6 characters)
 * 
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
-(NSString*) get_advertisedValue;
-(NSString*) advertisedValue;

/**
 * Returns the measuring unit for the measured value.
 * 
 * @return a string corresponding to the measuring unit for the measured value
 * 
 * On failure, throws an exception or returns Y_UNIT_INVALID.
 */
-(NSString*) get_unit;
-(NSString*) unit;

/**
 * Returns the current measured value.
 * 
 * @return a floating point number corresponding to the current measured value
 * 
 * On failure, throws an exception or returns Y_CURRENTVALUE_INVALID.
 */
-(double) get_currentValue;
-(double) currentValue;

/**
 * Changes the recorded minimal value observed.
 * 
 * @param newval : a floating point number corresponding to the recorded minimal value observed
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_lowestValue:(double) newval;
-(int)     setLowestValue:(double) newval;

/**
 * Returns the minimal value observed.
 * 
 * @return a floating point number corresponding to the minimal value observed
 * 
 * On failure, throws an exception or returns Y_LOWESTVALUE_INVALID.
 */
-(double) get_lowestValue;
-(double) lowestValue;

/**
 * Changes the recorded maximal value observed.
 * 
 * @param newval : a floating point number corresponding to the recorded maximal value observed
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_highestValue:(double) newval;
-(int)     setHighestValue:(double) newval;

/**
 * Returns the maximal value observed.
 * 
 * @return a floating point number corresponding to the maximal value observed
 * 
 * On failure, throws an exception or returns Y_HIGHESTVALUE_INVALID.
 */
-(double) get_highestValue;
-(double) highestValue;

/**
 * Returns the uncalibrated, unrounded raw value returned by the sensor.
 * 
 * @return a floating point number corresponding to the uncalibrated, unrounded raw value returned by the sensor
 * 
 * On failure, throws an exception or returns Y_CURRENTRAWVALUE_INVALID.
 */
-(double) get_currentRawValue;
-(double) currentRawValue;

-(NSString*) get_calibrationParam;
-(NSString*) calibrationParam;

-(int)     set_calibrationParam:(NSString*) newval;
-(int)     setCalibrationParam:(NSString*) newval;

/**
 * Configures error correction data points, in particular to compensate for
 * a possible perturbation of the measure caused by an enclosure. It is possible
 * to configure up to five correction points. Correction points must be provided
 * in ascending order, and be in the range of the sensor. The device will automatically
 * perform a linear interpolation of the error correction between specified
 * points. Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * For more information on advanced capabilities to refine the calibration of
 * sensors, please contact support@yoctopuce.com.
 * 
 * @param rawValues : array of floating point numbers, corresponding to the raw
 *         values returned by the sensor for the correction points.
 * @param refValues : array of floating point numbers, corresponding to the corrected
 *         values for the correction points.
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     calibrateFromPoints :(NSMutableArray*)rawValues :(NSMutableArray*)refValues;

-(int)     loadCalibrationPoints :(NSMutableArray*)rawValues :(NSMutableArray*)refValues;

/**
 * Returns the resolution of the measured values. The resolution corresponds to the numerical precision
 * of the values, which is not always the same as the actual precision of the sensor.
 * 
 * @return a floating point number corresponding to the resolution of the measured values
 * 
 * On failure, throws an exception or returns Y_RESOLUTION_INVALID.
 */
-(double) get_resolution;
-(double) resolution;

/**
 * Returns the temperature sensor type.
 * 
 * @return a value among Y_SENSORTYPE_DIGITAL, Y_SENSORTYPE_TYPE_K, Y_SENSORTYPE_TYPE_E,
 * Y_SENSORTYPE_TYPE_J, Y_SENSORTYPE_TYPE_N, Y_SENSORTYPE_TYPE_R, Y_SENSORTYPE_TYPE_S,
 * Y_SENSORTYPE_TYPE_T, Y_SENSORTYPE_PT100_4WIRES, Y_SENSORTYPE_PT100_3WIRES and
 * Y_SENSORTYPE_PT100_2WIRES corresponding to the temperature sensor type
 * 
 * On failure, throws an exception or returns Y_SENSORTYPE_INVALID.
 */
-(Y_SENSORTYPE_enum) get_sensorType;
-(Y_SENSORTYPE_enum) sensorType;

/**
 * Modify the temperature sensor type.  This function is used to
 * to define the type of thermocouple (K,E...) used with the device.
 * This will have no effect if module is using a digital sensor.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a value among Y_SENSORTYPE_DIGITAL, Y_SENSORTYPE_TYPE_K, Y_SENSORTYPE_TYPE_E,
 * Y_SENSORTYPE_TYPE_J, Y_SENSORTYPE_TYPE_N, Y_SENSORTYPE_TYPE_R, Y_SENSORTYPE_TYPE_S,
 * Y_SENSORTYPE_TYPE_T, Y_SENSORTYPE_PT100_4WIRES, Y_SENSORTYPE_PT100_3WIRES and Y_SENSORTYPE_PT100_2WIRES
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_sensorType:(Y_SENSORTYPE_enum) newval;
-(int)     setSensorType:(Y_SENSORTYPE_enum) newval;


//--- (end of YTemperature accessors declaration)
@end

//--- (Temperature functions declaration)

/**
 * Retrieves a temperature sensor for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the temperature sensor is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YTemperature.isOnline() to test if the temperature sensor is
 * indeed online at a given time. In case of ambiguity when looking for
 * a temperature sensor by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the temperature sensor
 * 
 * @return a YTemperature object allowing you to drive the temperature sensor.
 */
YTemperature* yFindTemperature(NSString* func);
/**
 * Starts the enumeration of temperature sensors currently accessible.
 * Use the method YTemperature.nextTemperature() to iterate on
 * next temperature sensors.
 * 
 * @return a pointer to a YTemperature object, corresponding to
 *         the first temperature sensor currently online, or a null pointer
 *         if there are none.
 */
YTemperature* yFirstTemperature(void);

//--- (end of Temperature functions declaration)
CF_EXTERN_C_END

