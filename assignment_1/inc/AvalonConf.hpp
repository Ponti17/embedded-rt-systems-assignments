/*
 * AvalonConf.hpp
 * Date Created: 08/09/24
*/

#ifndef AVALON_CONF_HPP
#define AVALON_CONF_HPP

/**
 * Avalon Channel Configuration
*/
#define CHANNEL_BITS    4   /* Number of channel wires      */
#define ERROR_BITS      2   /* Number of error wires        */
#define DATA_BITS       16  /* Number of data wires         */
#define MAX_CHANNEL     2   /* Maxinum number of channels   */
#define CLK_PERIO       20  /* Clock period in ns           */

#if DATA_BITS == 16
typedef uint16_t binMessageType;
#elif DATA_BITS == 32
typedef uint32_t binMessageType;
#elif DATA_BITS == 64
typedef uint64_t binMessageType;
#endif

#endif // AVALON_CONF_HPP