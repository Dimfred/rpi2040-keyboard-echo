#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// defined by compiler flags for flexibility
#ifndef CFG_TUSB_MCU
#define CFG_TUSB_MCU OPT_MCU_RP2040
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS OPT_OS_PICO
#endif

#define CFG_TUSB_DEBUG 0

// Device mode with full speed on rhport 0
#define CFG_TUSB_RHPORT0_MODE (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)

// Enable Device mode
#define CFG_TUD_ENABLED 1

// CFG_TUSB_DEBUG is defined by compiler in DEBUG build
#define CFG_TUSB_DEBUG_PRINTF printf

// RHPort number used for device
#define BOARD_TUD_RHPORT 0

// RHPort max operational speed
#define BOARD_TUD_MAX_SPEED OPT_MODE_FULL_SPEED

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE 64
#endif

//------------- CLASS -------------//
#define CFG_TUD_HID 1
#define CFG_TUD_CDC 1
#define CFG_TUD_MSC 0
#define CFG_TUD_MIDI 0
#define CFG_TUD_VENDOR 0

// HID buffer size Should be sufficient to hold ID (if any) + Data
#define CFG_TUD_HID_EP_BUFSIZE 16

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE 64
#define CFG_TUD_CDC_TX_BUFSIZE 64

// CDC Endpoint transfer buffer size, more is faster
#define CFG_TUD_CDC_EP_BUFSIZE 64

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */
