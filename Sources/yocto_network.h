/*********************************************************************
 *
 * $Id: yocto_network.h 12337 2013-08-14 15:22:22Z mvuilleu $
 *
 * Declares yFindNetwork(), the high-level API for Network functions
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

//--- (YNetwork definitions)
typedef enum {
    Y_READINESS_DOWN = 0,
    Y_READINESS_EXISTS = 1,
    Y_READINESS_LINKED = 2,
    Y_READINESS_LAN_OK = 3,
    Y_READINESS_WWW_OK = 4,
    Y_READINESS_INVALID = -1
} Y_READINESS_enum;

typedef enum {
    Y_DISCOVERABLE_FALSE = 0,
    Y_DISCOVERABLE_TRUE = 1,
    Y_DISCOVERABLE_INVALID = -1
} Y_DISCOVERABLE_enum;

typedef enum {
    Y_CALLBACKMETHOD_POST = 0,
    Y_CALLBACKMETHOD_GET = 1,
    Y_CALLBACKMETHOD_PUT = 2,
    Y_CALLBACKMETHOD_INVALID = -1
} Y_CALLBACKMETHOD_enum;

typedef enum {
    Y_CALLBACKENCODING_FORM = 0,
    Y_CALLBACKENCODING_JSON = 1,
    Y_CALLBACKENCODING_JSON_ARRAY = 2,
    Y_CALLBACKENCODING_CSV = 3,
    Y_CALLBACKENCODING_YOCTO_API = 4,
    Y_CALLBACKENCODING_INVALID = -1
} Y_CALLBACKENCODING_enum;

#define Y_LOGICALNAME_INVALID           [YAPI  INVALID_STRING]
#define Y_ADVERTISEDVALUE_INVALID       [YAPI  INVALID_STRING]
#define Y_MACADDRESS_INVALID            [YAPI  INVALID_STRING]
#define Y_IPADDRESS_INVALID             [YAPI  INVALID_STRING]
#define Y_SUBNETMASK_INVALID            [YAPI  INVALID_STRING]
#define Y_ROUTER_INVALID                [YAPI  INVALID_STRING]
#define Y_IPCONFIG_INVALID              [YAPI  INVALID_STRING]
#define Y_PRIMARYDNS_INVALID            [YAPI  INVALID_STRING]
#define Y_SECONDARYDNS_INVALID          [YAPI  INVALID_STRING]
#define Y_USERPASSWORD_INVALID          [YAPI  INVALID_STRING]
#define Y_ADMINPASSWORD_INVALID         [YAPI  INVALID_STRING]
#define Y_WWWWATCHDOGDELAY_INVALID      (0xffffffff)
#define Y_CALLBACKURL_INVALID           [YAPI  INVALID_STRING]
#define Y_CALLBACKCREDENTIALS_INVALID   [YAPI  INVALID_STRING]
#define Y_CALLBACKMINDELAY_INVALID      (0xffffffff)
#define Y_CALLBACKMAXDELAY_INVALID      (0xffffffff)
#define Y_POECURRENT_INVALID            (0xffffffff)
//--- (end of YNetwork definitions)

/**
 * YNetwork Class: Network function interface
 * 
 * YNetwork objects provide access to TCP/IP parameters of Yoctopuce
 * modules that include a built-in network interface.
 */
@interface YNetwork : YFunction
{
@protected

// Attributes (function value cache)
//--- (YNetwork attributes)
    NSString*       _logicalName;
    NSString*       _advertisedValue;
    Y_READINESS_enum _readiness;
    NSString*       _macAddress;
    NSString*       _ipAddress;
    NSString*       _subnetMask;
    NSString*       _router;
    NSString*       _ipConfig;
    NSString*       _primaryDNS;
    NSString*       _secondaryDNS;
    NSString*       _userPassword;
    NSString*       _adminPassword;
    Y_DISCOVERABLE_enum _discoverable;
    unsigned        _wwwWatchdogDelay;
    NSString*       _callbackUrl;
    Y_CALLBACKMETHOD_enum _callbackMethod;
    Y_CALLBACKENCODING_enum _callbackEncoding;
    NSString*       _callbackCredentials;
    unsigned        _callbackMinDelay;
    unsigned        _callbackMaxDelay;
    unsigned        _poeCurrent;
//--- (end of YNetwork attributes)
}
//--- (YNetwork declaration)
// Constructor is protected, use yFindNetwork factory function to instantiate
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

//--- (end of YNetwork declaration)
//--- (YNetwork accessors declaration)

/**
 * Continues the enumeration of network interfaces started using yFirstNetwork().
 * 
 * @return a pointer to a YNetwork object, corresponding to
 *         a network interface currently online, or a null pointer
 *         if there are no more network interfaces to enumerate.
 */
-(YNetwork*) nextNetwork;
/**
 * Retrieves a network interface for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the network interface is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YNetwork.isOnline() to test if the network interface is
 * indeed online at a given time. In case of ambiguity when looking for
 * a network interface by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the network interface
 * 
 * @return a YNetwork object allowing you to drive the network interface.
 */
+(YNetwork*) FindNetwork:(NSString*) func;
/**
 * Starts the enumeration of network interfaces currently accessible.
 * Use the method YNetwork.nextNetwork() to iterate on
 * next network interfaces.
 * 
 * @return a pointer to a YNetwork object, corresponding to
 *         the first network interface currently online, or a null pointer
 *         if there are none.
 */
+(YNetwork*) FirstNetwork;

/**
 * Returns the logical name of the network interface, corresponding to the network name of the module.
 * 
 * @return a string corresponding to the logical name of the network interface, corresponding to the
 * network name of the module
 * 
 * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
 */
-(NSString*) get_logicalName;
-(NSString*) logicalName;

/**
 * Changes the logical name of the network interface, corresponding to the network name of the module.
 * You can use yCheckLogicalName()
 * prior to this call to make sure that your parameter is valid.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the logical name of the network interface, corresponding
 * to the network name of the module
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_logicalName:(NSString*) newval;
-(int)     setLogicalName:(NSString*) newval;

/**
 * Returns the current value of the network interface (no more than 6 characters).
 * 
 * @return a string corresponding to the current value of the network interface (no more than 6 characters)
 * 
 * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
 */
-(NSString*) get_advertisedValue;
-(NSString*) advertisedValue;

/**
 * Returns the current established working mode of the network interface.
 * Level zero (DOWN_0) means that no hardware link has been detected. Either there is no signal
 * on the network cable, or the selected wireless access point cannot be detected.
 * Level 1 (LIVE_1) is reached when the network is detected, but is not yet connected,
 * For a wireless network, this shows that the requested SSID is present.
 * Level 2 (LINK_2) is reached when the hardware connection is established.
 * For a wired network connection, level 2 means that the cable is attached at both ends.
 * For a connection to a wireless access point, it shows that the security parameters
 * are properly configured. For an ad-hoc wireless connection, it means that there is
 * at least one other device connected on the ad-hoc network.
 * Level 3 (DHCP_3) is reached when an IP address has been obtained using DHCP.
 * Level 4 (DNS_4) is reached when the DNS server is reachable on the network.
 * Level 5 (WWW_5) is reached when global connectivity is demonstrated by properly loading the
 * current time from an NTP server.
 * 
 * @return a value among Y_READINESS_DOWN, Y_READINESS_EXISTS, Y_READINESS_LINKED, Y_READINESS_LAN_OK
 * and Y_READINESS_WWW_OK corresponding to the current established working mode of the network interface
 * 
 * On failure, throws an exception or returns Y_READINESS_INVALID.
 */
-(Y_READINESS_enum) get_readiness;
-(Y_READINESS_enum) readiness;

/**
 * Returns the MAC address of the network interface. The MAC address is also available on a sticker
 * on the module, in both numeric and barcode forms.
 * 
 * @return a string corresponding to the MAC address of the network interface
 * 
 * On failure, throws an exception or returns Y_MACADDRESS_INVALID.
 */
-(NSString*) get_macAddress;
-(NSString*) macAddress;

/**
 * Returns the IP address currently in use by the device. The adress may have been configured
 * statically, or provided by a DHCP server.
 * 
 * @return a string corresponding to the IP address currently in use by the device
 * 
 * On failure, throws an exception or returns Y_IPADDRESS_INVALID.
 */
-(NSString*) get_ipAddress;
-(NSString*) ipAddress;

/**
 * Returns the subnet mask currently used by the device.
 * 
 * @return a string corresponding to the subnet mask currently used by the device
 * 
 * On failure, throws an exception or returns Y_SUBNETMASK_INVALID.
 */
-(NSString*) get_subnetMask;
-(NSString*) subnetMask;

/**
 * Returns the IP address of the router on the device subnet (default gateway).
 * 
 * @return a string corresponding to the IP address of the router on the device subnet (default gateway)
 * 
 * On failure, throws an exception or returns Y_ROUTER_INVALID.
 */
-(NSString*) get_router;
-(NSString*) router;

-(NSString*) get_ipConfig;
-(NSString*) ipConfig;

-(int)     set_ipConfig:(NSString*) newval;
-(int)     setIpConfig:(NSString*) newval;

/**
 * Changes the configuration of the network interface to enable the use of an
 * IP address received from a DHCP server. Until an address is received from a DHCP
 * server, the module uses the IP parameters specified to this function.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 * 
 * @param fallbackIpAddr : fallback IP address, to be used when no DHCP reply is received
 * @param fallbackSubnetMaskLen : fallback subnet mask length when no DHCP reply is received, as an
 *         integer (eg. 24 means 255.255.255.0)
 * @param fallbackRouter : fallback router IP address, to be used when no DHCP reply is received
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     useDHCP :(NSString*)fallbackIpAddr :(int)fallbackSubnetMaskLen :(NSString*)fallbackRouter;

/**
 * Changes the configuration of the network interface to use a static IP address.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 * 
 * @param ipAddress : device IP address
 * @param subnetMaskLen : subnet mask length, as an integer (eg. 24 means 255.255.255.0)
 * @param router : router IP address (default gateway)
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     useStaticIP :(NSString*)ipAddress :(int)subnetMaskLen :(NSString*)router;

/**
 * Returns the IP address of the primary name server to be used by the module.
 * 
 * @return a string corresponding to the IP address of the primary name server to be used by the module
 * 
 * On failure, throws an exception or returns Y_PRIMARYDNS_INVALID.
 */
-(NSString*) get_primaryDNS;
-(NSString*) primaryDNS;

/**
 * Changes the IP address of the primary name server to be used by the module.
 * When using DHCP, if a value is specified, it overrides the value received from the DHCP server.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 * 
 * @param newval : a string corresponding to the IP address of the primary name server to be used by the module
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_primaryDNS:(NSString*) newval;
-(int)     setPrimaryDNS:(NSString*) newval;

/**
 * Returns the IP address of the secondary name server to be used by the module.
 * 
 * @return a string corresponding to the IP address of the secondary name server to be used by the module
 * 
 * On failure, throws an exception or returns Y_SECONDARYDNS_INVALID.
 */
-(NSString*) get_secondaryDNS;
-(NSString*) secondaryDNS;

/**
 * Changes the IP address of the secondarz name server to be used by the module.
 * When using DHCP, if a value is specified, it overrides the value received from the DHCP server.
 * Remember to call the saveToFlash() method and then to reboot the module to apply this setting.
 * 
 * @param newval : a string corresponding to the IP address of the secondarz name server to be used by the module
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_secondaryDNS:(NSString*) newval;
-(int)     setSecondaryDNS:(NSString*) newval;

/**
 * Returns a hash string if a password has been set for "user" user,
 * or an empty string otherwise.
 * 
 * @return a string corresponding to a hash string if a password has been set for "user" user,
 *         or an empty string otherwise
 * 
 * On failure, throws an exception or returns Y_USERPASSWORD_INVALID.
 */
-(NSString*) get_userPassword;
-(NSString*) userPassword;

/**
 * Changes the password for the "user" user. This password becomes instantly required
 * to perform any use of the module. If the specified value is an
 * empty string, a password is not required anymore.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the password for the "user" user
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_userPassword:(NSString*) newval;
-(int)     setUserPassword:(NSString*) newval;

/**
 * Returns a hash string if a password has been set for user "admin",
 * or an empty string otherwise.
 * 
 * @return a string corresponding to a hash string if a password has been set for user "admin",
 *         or an empty string otherwise
 * 
 * On failure, throws an exception or returns Y_ADMINPASSWORD_INVALID.
 */
-(NSString*) get_adminPassword;
-(NSString*) adminPassword;

/**
 * Changes the password for the "admin" user. This password becomes instantly required
 * to perform any change of the module state. If the specified value is an
 * empty string, a password is not required anymore.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the password for the "admin" user
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_adminPassword:(NSString*) newval;
-(int)     setAdminPassword:(NSString*) newval;

/**
 * Returns the activation state of the multicast announce protocols to allow easy
 * discovery of the module in the network neighborhood (uPnP/Bonjour protocol).
 * 
 * @return either Y_DISCOVERABLE_FALSE or Y_DISCOVERABLE_TRUE, according to the activation state of
 * the multicast announce protocols to allow easy
 *         discovery of the module in the network neighborhood (uPnP/Bonjour protocol)
 * 
 * On failure, throws an exception or returns Y_DISCOVERABLE_INVALID.
 */
-(Y_DISCOVERABLE_enum) get_discoverable;
-(Y_DISCOVERABLE_enum) discoverable;

/**
 * Changes the activation state of the multicast announce protocols to allow easy
 * discovery of the module in the network neighborhood (uPnP/Bonjour protocol).
 * 
 * @param newval : either Y_DISCOVERABLE_FALSE or Y_DISCOVERABLE_TRUE, according to the activation
 * state of the multicast announce protocols to allow easy
 *         discovery of the module in the network neighborhood (uPnP/Bonjour protocol)
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_discoverable:(Y_DISCOVERABLE_enum) newval;
-(int)     setDiscoverable:(Y_DISCOVERABLE_enum) newval;

/**
 * Returns the allowed downtime of the WWW link (in seconds) before triggering an automated
 * reboot to try to recover Internet connectivity. A zero value disables automated reboot
 * in case of Internet connectivity loss.
 * 
 * @return an integer corresponding to the allowed downtime of the WWW link (in seconds) before
 * triggering an automated
 *         reboot to try to recover Internet connectivity
 * 
 * On failure, throws an exception or returns Y_WWWWATCHDOGDELAY_INVALID.
 */
-(unsigned) get_wwwWatchdogDelay;
-(unsigned) wwwWatchdogDelay;

/**
 * Changes the allowed downtime of the WWW link (in seconds) before triggering an automated
 * reboot to try to recover Internet connectivity. A zero value disable automated reboot
 * in case of Internet connectivity loss. The smallest valid non-zero timeout is
 * 90 seconds.
 * 
 * @param newval : an integer corresponding to the allowed downtime of the WWW link (in seconds)
 * before triggering an automated
 *         reboot to try to recover Internet connectivity
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_wwwWatchdogDelay:(unsigned) newval;
-(int)     setWwwWatchdogDelay:(unsigned) newval;

/**
 * Returns the callback URL to notify of significant state changes.
 * 
 * @return a string corresponding to the callback URL to notify of significant state changes
 * 
 * On failure, throws an exception or returns Y_CALLBACKURL_INVALID.
 */
-(NSString*) get_callbackUrl;
-(NSString*) callbackUrl;

/**
 * Changes the callback URL to notify significant state changes. Remember to call the
 * saveToFlash() method of the module if the modification must be kept.
 * 
 * @param newval : a string corresponding to the callback URL to notify significant state changes
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackUrl:(NSString*) newval;
-(int)     setCallbackUrl:(NSString*) newval;

/**
 * Returns the HTTP method used to notify callbacks for significant state changes.
 * 
 * @return a value among Y_CALLBACKMETHOD_POST, Y_CALLBACKMETHOD_GET and Y_CALLBACKMETHOD_PUT
 * corresponding to the HTTP method used to notify callbacks for significant state changes
 * 
 * On failure, throws an exception or returns Y_CALLBACKMETHOD_INVALID.
 */
-(Y_CALLBACKMETHOD_enum) get_callbackMethod;
-(Y_CALLBACKMETHOD_enum) callbackMethod;

/**
 * Changes the HTTP method used to notify callbacks for significant state changes.
 * 
 * @param newval : a value among Y_CALLBACKMETHOD_POST, Y_CALLBACKMETHOD_GET and Y_CALLBACKMETHOD_PUT
 * corresponding to the HTTP method used to notify callbacks for significant state changes
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackMethod:(Y_CALLBACKMETHOD_enum) newval;
-(int)     setCallbackMethod:(Y_CALLBACKMETHOD_enum) newval;

/**
 * Returns the encoding standard to use for representing notification values.
 * 
 * @return a value among Y_CALLBACKENCODING_FORM, Y_CALLBACKENCODING_JSON,
 * Y_CALLBACKENCODING_JSON_ARRAY, Y_CALLBACKENCODING_CSV and Y_CALLBACKENCODING_YOCTO_API
 * corresponding to the encoding standard to use for representing notification values
 * 
 * On failure, throws an exception or returns Y_CALLBACKENCODING_INVALID.
 */
-(Y_CALLBACKENCODING_enum) get_callbackEncoding;
-(Y_CALLBACKENCODING_enum) callbackEncoding;

/**
 * Changes the encoding standard to use for representing notification values.
 * 
 * @param newval : a value among Y_CALLBACKENCODING_FORM, Y_CALLBACKENCODING_JSON,
 * Y_CALLBACKENCODING_JSON_ARRAY, Y_CALLBACKENCODING_CSV and Y_CALLBACKENCODING_YOCTO_API
 * corresponding to the encoding standard to use for representing notification values
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackEncoding:(Y_CALLBACKENCODING_enum) newval;
-(int)     setCallbackEncoding:(Y_CALLBACKENCODING_enum) newval;

/**
 * Returns a hashed version of the notification callback credentials if set,
 * or an empty string otherwise.
 * 
 * @return a string corresponding to a hashed version of the notification callback credentials if set,
 *         or an empty string otherwise
 * 
 * On failure, throws an exception or returns Y_CALLBACKCREDENTIALS_INVALID.
 */
-(NSString*) get_callbackCredentials;
-(NSString*) callbackCredentials;

/**
 * Changes the credentials required to connect to the callback address. The credentials
 * must be provided as returned by function get_callbackCredentials,
 * in the form username:hash. The method used to compute the hash varies according
 * to the the authentication scheme implemented by the callback, For Basic authentication,
 * the hash is the MD5 of the string username:password. For Digest authentication,
 * the hash is the MD5 of the string username:realm:password. For a simpler
 * way to configure callback credentials, use function callbackLogin instead.
 * Remember to call the saveToFlash() method of the module if the
 * modification must be kept.
 * 
 * @param newval : a string corresponding to the credentials required to connect to the callback address
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackCredentials:(NSString*) newval;
-(int)     setCallbackCredentials:(NSString*) newval;

/**
 * Connects to the notification callback and saves the credentials required to
 * log into it. The password is not stored into the module, only a hashed
 * copy of the credentials are saved. Remember to call the
 * saveToFlash() method of the module if the modification must be kept.
 * 
 * @param username : username required to log to the callback
 * @param password : password required to log to the callback
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     callbackLogin :(NSString*)username :(NSString*)password;

/**
 * Returns the minimum waiting time between two callback notifications, in seconds.
 * 
 * @return an integer corresponding to the minimum waiting time between two callback notifications, in seconds
 * 
 * On failure, throws an exception or returns Y_CALLBACKMINDELAY_INVALID.
 */
-(unsigned) get_callbackMinDelay;
-(unsigned) callbackMinDelay;

/**
 * Changes the minimum waiting time between two callback notifications, in seconds.
 * 
 * @param newval : an integer corresponding to the minimum waiting time between two callback
 * notifications, in seconds
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackMinDelay:(unsigned) newval;
-(int)     setCallbackMinDelay:(unsigned) newval;

/**
 * Returns the maximum waiting time between two callback notifications, in seconds.
 * 
 * @return an integer corresponding to the maximum waiting time between two callback notifications, in seconds
 * 
 * On failure, throws an exception or returns Y_CALLBACKMAXDELAY_INVALID.
 */
-(unsigned) get_callbackMaxDelay;
-(unsigned) callbackMaxDelay;

/**
 * Changes the maximum waiting time between two callback notifications, in seconds.
 * 
 * @param newval : an integer corresponding to the maximum waiting time between two callback
 * notifications, in seconds
 * 
 * @return YAPI_SUCCESS if the call succeeds.
 * 
 * On failure, throws an exception or returns a negative error code.
 */
-(int)     set_callbackMaxDelay:(unsigned) newval;
-(int)     setCallbackMaxDelay:(unsigned) newval;

/**
 * Returns the current consumed by the module from Power-over-Ethernet (PoE), in milli-amps.
 * The current consumption is measured after converting PoE source to 5 Volt, and should
 * never exceed 1800 mA.
 * 
 * @return an integer corresponding to the current consumed by the module from Power-over-Ethernet
 * (PoE), in milli-amps
 * 
 * On failure, throws an exception or returns Y_POECURRENT_INVALID.
 */
-(unsigned) get_poeCurrent;
-(unsigned) poeCurrent;

/**
 * Pings str_host to test the network connectivity. Sends four requests ICMP ECHO_REQUEST from the
 * module to the target str_host. This method returns a string with the result of the
 * 4 ICMP ECHO_REQUEST result.
 * 
 * @param host : the hostname or the IP address of the target
 * 
 * @return a string with the result of the ping.
 */
-(NSString*)     ping :(NSString*)host;


//--- (end of YNetwork accessors declaration)
@end

//--- (Network functions declaration)

/**
 * Retrieves a network interface for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the network interface is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YNetwork.isOnline() to test if the network interface is
 * indeed online at a given time. In case of ambiguity when looking for
 * a network interface by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the network interface
 * 
 * @return a YNetwork object allowing you to drive the network interface.
 */
YNetwork* yFindNetwork(NSString* func);
/**
 * Starts the enumeration of network interfaces currently accessible.
 * Use the method YNetwork.nextNetwork() to iterate on
 * next network interfaces.
 * 
 * @return a pointer to a YNetwork object, corresponding to
 *         the first network interface currently online, or a null pointer
 *         if there are none.
 */
YNetwork* yFirstNetwork(void);

//--- (end of Network functions declaration)
CF_EXTERN_C_END

